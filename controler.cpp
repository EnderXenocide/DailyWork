#include "controler.h"

Controler::Controler()
{
    dwparser.Parse();
    currentDates.Clear();
    dwparser.GetExcludedDays(excludedDays);
  //  MainFrame* sameframe  = frame;
    dwparser.StatusBarMessageCallback([sameframe](wxString msg) { sameframe->OnStatusBarMessage(msg); });
    dwparser.DialogMessageCallback([sameframe](wxString msg) { sameframe->OnDialogMessage(msg); });
}

Controler::~Controler()
{
}

void Controler::LoadFavoritesInComboBox()
{
    frame->m_comboBoxFavorite->Clear();
    for(SizeType i = 0; i < dwparser.CountFavorites(); i++) { //todo faire des appels de dwparser
        wxString text = dwparser.GetFavorite(i);
        if ( ! text.IsEmpty()) {
            frame->m_comboBoxFavorite->Append(text);
            //frame->m_comboBoxFavorite->SetString(1,"1");
        }
    }  
}

void Controler::LoadDailyWorkInTree()
{
    wxStopWatch stopwatch;
    LOG(INFO) << "Loading Tree with json 0data...";
    frame->DisconnectSelectionEvents();
    wxTreeCtrl* tree = frame->m_treeDates;
    tree->Freeze(); //prevent drawing
    tree->DeleteAllItems();
    tree->SetWindowStyle(wxTR_HIDE_ROOT);
    wxTreeItemId rootId = tree->AddRoot(wxT("Dates")); //hidden
    wxTreeItemId (MainApp::*LoadBranch)(wxTreeItemId rootId, wxDateTime date); // pointeur de fonction
    if (hierarchicalTree) {
        LoadBranch = &AddBranchHierarchy;
        LOG(INFO) << "Loading Tree Hierarchy... ";
    }
    else {
        LoadBranch = &AddBranchSimple;
        LOG(INFO) << "Loading Tree Simple... ";
    }
    wxTreeItemId itemId;
    for(SizeType i = 0; i < dwparser.CountItems(); i++) { //todo faire des appels de dwparser
        wxDateTime date = dwparser.GetDateFromItem(i);
        if (date.IsValid()) {
            itemId = (this->*LoadBranch)(rootId, date);
        }
        else {
            wxString errmsg = wxString::Format(_("Error loading date <%s>"), date.Format());
            frame->OnStatusBarMessage(errmsg);
            LOG(ERROR) << errmsg;
        }
    }
    frame->OnStatusBarMessage(_("Dates loaded"));
    tree->ExpandAll();
    tree->Thaw(); // Re-enables window before selection
    frame->ConnectSelectionEvents();    
    SelectFirstTreeDatesItem();
    long t = stopwatch.Time();
    LOG(INFO) << wxString::Format("Tree Loaded in %ldms", t);
}

wxTreeItemId Controler::AddBranchHierarchy(wxTreeItemId rootId, wxDateTime date)
{
    wxDateTime tempDate = date;
    
    tempDate.SetMonth(wxDateTime::Jan).SetDay(1); //début d'année de date
    wxTreeItemId itemId = AddItem(rootId, date.Format("%Y"), tempDate, true);
    
    tempDate.SetMonth(date.GetMonth()); //début de mois de date
    itemId = AddItem(itemId, date.Format("%m [%b]"), tempDate, true); //"%B (%m)"
    
    return AddItem(itemId, date.Format("%d %A"), date, false);  //%e ne marche pas //"%A %d"
}

wxTreeItemId Controler::AddBranchSimple(wxTreeItemId rootId, wxDateTime date)
{
    return AddItem(rootId, date.Format("%Y-%m-%d %a"), date, false);   //% F ne marche pas = Short YYYY-MM-DD date, equivalent to %Y-%m-%d
}

int Controler::AddDateToTree(const wxDateTime& date, bool selectItem)
{
    wxTreeCtrl* tree = frame->m_treeDates;

    wxTreeItemId itemId;
    if(hierarchicalTree) {
        wxString sdate;
        itemId = AddBranchHierarchy(tree->GetRootItem(), date);
    } else {
        itemId = AddBranchSimple(tree->GetRootItem(), date);
    }
    dwparser.AddItem(date);
    tree->ExpandAll(); //Expand(itemId);
    if(selectItem)
        tree->SelectItem(itemId);
    return 0;
}

/*
 * Cherche l'item avec date comme data ou ajout un nouveau dans l'ordre alphabéthique inverse
 */
wxTreeItemId Controler::AddItem(wxTreeItemId parent, wxString text, wxDateTime date, bool setDataEmpty)
{
    wxTreeCtrl* tree = frame->m_treeDates;
    wxTreeItemIdValue cookie;
    wxTreeItemId itemId = tree->GetFirstChild(parent, cookie);
    wxDateTime itemDate;
    wxTreeItemId newItemId;
    while(itemId.IsOk()) {
        DWItemData *itemData = (DWItemData *) tree->GetItemData(itemId);
        if (itemData != NULL)
            itemDate = itemData->GetDate();
        else    
            itemDate = (time_t)-1;
            
        if(itemDate == date)
            return itemId;                         // pas besoin d'ajouter l'item
        else if(date > itemDate) {                 // item voulu doit se trouver après
            itemId = tree->GetPrevSibling(itemId); // on prend l'item precedent pour pouvoir inserer celui qu'on veux
            if(itemId.IsOk())
                newItemId = tree->InsertItem(parent, itemId, text);
            else                                          // pas d'item avant
                newItemId =  tree->InsertItem(parent, 0, text); // insert item en premier
            return AddItemData(newItemId, date, setDataEmpty);
        }
        itemId  = tree->GetNextChild(parent, cookie);
    }
    newItemId =  tree->AppendItem(parent, text); // item voulu non trouver
    return AddItemData(newItemId, date, setDataEmpty);
}
    
wxTreeItemId Controler::AddItemData(wxTreeItemId itemId, wxDateTime date, bool setDataEmpty)
{
    if ( ! setDataEmpty)
        currentDates.dates.insert(date);  // on ne stocke que les date valide
    DWItemData *itemData = new DWItemData(date, setDataEmpty);
    frame->m_treeDates->SetItemData(itemId, itemData);  
    return itemId; 
}