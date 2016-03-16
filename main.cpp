/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include "main.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation 
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit()
{
    START_EASYLOGGINGPP(wxGetApp().argc, wxGetApp().argv);
    LOG(INFO ) << "START";
	
    if ( !wxApp::OnInit() )
        return false;

    InitLanguageSupport();
#if wxUSE_HELP
    wxHelpProvider::Set(new wxSimpleHelpProvider);
#endif   
#if USE_RICH_EDIT 
    InitRichText();
#endif   

    SetHierarchicalTree(true); // avant creation de la frame pour le menu ShowHierarchicalTree
    
    // create the main application window
    wxSize size = wxGetDisplaySize();
    size.Scale(0.65, 0.75); // (largeur, hauteur)
    frame = new MainFrame(wxT("DailyWork"), wxID_ANY, wxDefaultPosition, size);


    MainFrame* sameframe  = frame;    
    
    dwparser.StatusBarMessageCallback([sameframe](wxString msg) { sameframe->OnStatusBarMessage(msg); });
    dwparser.DialogMessageCallback([sameframe](wxString msg) { sameframe->OnDialogMessage(msg); });
    InitDailyWorkParser();
    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    SetTopWindow(frame);
    frame->Show(true);
    
    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

int MainApp::OnExit()
{    
#if USE_RICH_EDIT
    delete m_styleSheet;
#endif
    return 0;
}

#if USE_RICH_EDIT
void MainApp::InitRichText()
{
    m_styleSheet = new wxRichTextStyleSheet;

    CreateStyles();
//
//    MyRichTextCtrl::SetEnhancedDrawingHandler();
//
//    // Add extra handlers (plain text is automatically added)
//    wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);
//    wxRichTextBuffer::AddHandler(new wxRichTextHTMLHandler);
//
//    // Add field types
//
//    wxRichTextBuffer::AddFieldType(new wxRichTextFieldTypePropertiesTest(wxT("rectangle"), wxT("RECTANGLE"), wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_RECTANGLE));
//
//    wxRichTextFieldTypeStandard* s1 = new wxRichTextFieldTypeStandard(wxT("begin-section"), wxT("SECTION"), wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_START_TAG);
//    s1->SetBackgroundColour(*wxBLUE);
//
//    wxRichTextFieldTypeStandard* s2 = new wxRichTextFieldTypeStandard(wxT("end-section"), wxT("SECTION"), wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_END_TAG);
//    s2->SetBackgroundColour(*wxBLUE);
//
//    wxRichTextFieldTypeStandard* s3 = new wxRichTextFieldTypeStandard(wxT("bitmap"), wxBitmap(paste_xpm), wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_NO_BORDER);
//
//    wxRichTextBuffer::AddFieldType(s1);
//    wxRichTextBuffer::AddFieldType(s2);
//    wxRichTextBuffer::AddFieldType(s3);
//
//    wxRichTextFieldTypeCompositeTest* s4 = new wxRichTextFieldTypeCompositeTest(wxT("composite"), wxT("This is a field value"));
//    wxRichTextBuffer::AddFieldType(s4);
//

//    // Add image handlers
//#if wxUSE_LIBPNG
//    wxImage::AddHandler( new wxPNGHandler );
//#endif
//
//#if wxUSE_LIBJPEG
//    wxImage::AddHandler( new wxJPEGHandler );
//#endif
//
//#if wxUSE_GIF
//    wxImage::AddHandler( new wxGIFHandler );
//#endif
//
//#if wxUSE_FILESYSTEM
//    wxFileSystem::AddHandler( new wxMemoryFSHandler );
//#endif
}

void MainApp::CreateStyles()
{
    // Paragraph styles

    wxFont romanFont(12, wxROMAN, wxNORMAL, wxNORMAL);
    wxFont swissFont(12, wxSWISS, wxNORMAL, wxNORMAL);

    wxRichTextParagraphStyleDefinition* normalPara = new wxRichTextParagraphStyleDefinition(wxT("Normal"));
    wxRichTextAttr normalAttr;
    normalAttr.SetFontFaceName(romanFont.GetFaceName());
    normalAttr.SetFontSize(12);
    // Let's set all attributes for this style
    normalAttr.SetFlags(wxTEXT_ATTR_FONT | wxTEXT_ATTR_BACKGROUND_COLOUR | wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT|wxTEXT_ATTR_TABS|
                            wxTEXT_ATTR_PARA_SPACING_BEFORE|wxTEXT_ATTR_PARA_SPACING_AFTER|wxTEXT_ATTR_LINE_SPACING|
                            wxTEXT_ATTR_BULLET_STYLE|wxTEXT_ATTR_BULLET_NUMBER);
    normalPara->SetStyle(normalAttr);

    m_styleSheet->AddParagraphStyle(normalPara);

    wxRichTextParagraphStyleDefinition* indentedPara = new wxRichTextParagraphStyleDefinition(wxT("Indented"));
    wxRichTextAttr indentedAttr;
    indentedAttr.SetFontFaceName(romanFont.GetFaceName());
    indentedAttr.SetFontSize(12);
    indentedAttr.SetLeftIndent(100, 0);
    // We only want to affect indentation
    indentedAttr.SetFlags(wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT);
    indentedPara->SetStyle(indentedAttr);

    m_styleSheet->AddParagraphStyle(indentedPara);

    wxRichTextParagraphStyleDefinition* indentedPara2 = new wxRichTextParagraphStyleDefinition(wxT("Red Bold Indented"));
    wxRichTextAttr indentedAttr2;
    indentedAttr2.SetFontFaceName(romanFont.GetFaceName());
    indentedAttr2.SetFontSize(12);
    indentedAttr2.SetFontWeight(wxFONTWEIGHT_BOLD);
    indentedAttr2.SetTextColour(*wxRED);
    indentedAttr2.SetFontSize(12);
    indentedAttr2.SetLeftIndent(100, 0);
    // We want to affect indentation, font and text colour
    indentedAttr2.SetFlags(wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT|wxTEXT_ATTR_FONT|wxTEXT_ATTR_TEXT_COLOUR);
    indentedPara2->SetStyle(indentedAttr2);

    m_styleSheet->AddParagraphStyle(indentedPara2);

    wxRichTextParagraphStyleDefinition* flIndentedPara = new wxRichTextParagraphStyleDefinition(wxT("First Line Indented"));
    wxRichTextAttr flIndentedAttr;
    flIndentedAttr.SetFontFaceName(swissFont.GetFaceName());
    flIndentedAttr.SetFontSize(12);
    flIndentedAttr.SetLeftIndent(100, -100);
    // We only want to affect indentation
    flIndentedAttr.SetFlags(wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT);
    flIndentedPara->SetStyle(flIndentedAttr);

    m_styleSheet->AddParagraphStyle(flIndentedPara);

    // Character styles

    wxRichTextCharacterStyleDefinition* boldDef = new wxRichTextCharacterStyleDefinition(wxT("Bold"));
    wxRichTextAttr boldAttr;
    boldAttr.SetFontFaceName(romanFont.GetFaceName());
    boldAttr.SetFontSize(12);
    boldAttr.SetFontWeight(wxFONTWEIGHT_BOLD);
    // We only want to affect boldness
    boldAttr.SetFlags(wxTEXT_ATTR_FONT_WEIGHT);
    boldDef->SetStyle(boldAttr);

    m_styleSheet->AddCharacterStyle(boldDef);

    wxRichTextCharacterStyleDefinition* italicDef = new wxRichTextCharacterStyleDefinition(wxT("Italic"));
    wxRichTextAttr italicAttr;
    italicAttr.SetFontFaceName(romanFont.GetFaceName());
    italicAttr.SetFontSize(12);
    italicAttr.SetFontStyle(wxFONTSTYLE_ITALIC);
    // We only want to affect italics
    italicAttr.SetFlags(wxTEXT_ATTR_FONT_ITALIC);
    italicDef->SetStyle(italicAttr);

    m_styleSheet->AddCharacterStyle(italicDef);

    wxRichTextCharacterStyleDefinition* redDef = new wxRichTextCharacterStyleDefinition(wxT("Red Bold"));
    wxRichTextAttr redAttr;
    redAttr.SetFontFaceName(romanFont.GetFaceName());
    redAttr.SetFontSize(12);
    redAttr.SetFontWeight(wxFONTWEIGHT_BOLD);
    redAttr.SetTextColour(*wxRED);
    // We only want to affect colour, weight and face
    redAttr.SetFlags(wxTEXT_ATTR_FONT_FACE|wxTEXT_ATTR_FONT_WEIGHT|wxTEXT_ATTR_TEXT_COLOUR);
    redDef->SetStyle(redAttr);

    m_styleSheet->AddCharacterStyle(redDef);

    wxRichTextListStyleDefinition* bulletList = new wxRichTextListStyleDefinition(wxT("Bullet List 1"));
    int i;
    for (i = 0; i < 10; i++)
    {
        wxString bulletText;
        if (i == 0)
            bulletText = wxT("standard/circle");
        else if (i == 1)
            bulletText = wxT("standard/square");
        else if (i == 2)
            bulletText = wxT("standard/circle");
        else if (i == 3)
            bulletText = wxT("standard/square");
        else
            bulletText = wxT("standard/circle");

        bulletList->SetAttributes(i, (i+1)*60, 60, wxTEXT_ATTR_BULLET_STYLE_STANDARD, bulletText);
    }

    m_styleSheet->AddListStyle(bulletList);

    wxRichTextListStyleDefinition* numberedList = new wxRichTextListStyleDefinition(wxT("Numbered List 1"));
    for (i = 0; i < 10; i++)
    {
        long numberStyle;
        if (i == 0)
            numberStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD;
        else if (i == 1)
            numberStyle = wxTEXT_ATTR_BULLET_STYLE_LETTERS_LOWER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES;
        else if (i == 2)
            numberStyle = wxTEXT_ATTR_BULLET_STYLE_ROMAN_LOWER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES;
        else if (i == 3)
            numberStyle = wxTEXT_ATTR_BULLET_STYLE_ROMAN_UPPER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES;
        else
            numberStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD;

        numberStyle |= wxTEXT_ATTR_BULLET_STYLE_ALIGN_RIGHT;

        numberedList->SetAttributes(i, (i+1)*60, 60, numberStyle);
    }

    m_styleSheet->AddListStyle(numberedList);

    wxRichTextListStyleDefinition* outlineList = new wxRichTextListStyleDefinition(wxT("Outline List 1"));
    for (i = 0; i < 10; i++)
    {
        long numberStyle;
        if (i < 4)
            numberStyle = wxTEXT_ATTR_BULLET_STYLE_OUTLINE|wxTEXT_ATTR_BULLET_STYLE_PERIOD;
        else
            numberStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD;

        outlineList->SetAttributes(i, (i+1)*120, 120, numberStyle);
    }

    m_styleSheet->AddListStyle(outlineList);

}

#endif //USE_RICH_EDIT

void MainApp::InitDailyWorkParser()
{
   dwparser.Parse();
   currentDates.Clear();
   dwparser.GetExcludedDays(excludedDays);
   LoadDailyWorkInTree();  // même si parse renvoie -1,  on charge quand même l'arbre   
   LoadFavoritesInComboBox();
}

void MainApp::LoadDailyWorkInTree()
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
    bool succeed = SelectFirstTreeDatesItem();
    if (! succeed)
        SetEmptyWorkSpace();
    long t = stopwatch.Time();
    LOG(INFO) << wxString::Format("Tree Loaded in %ldms", t);
}

wxTreeItemId MainApp::AddBranchHierarchy(wxTreeItemId rootId, wxDateTime date)
{
    wxDateTime tempDate = date;
    
    tempDate.SetMonth(wxDateTime::Jan).SetDay(1); //début d'année de date
    wxTreeItemId itemId = AddItem(rootId, date.Format("%Y"), tempDate, true);
    
    tempDate.SetMonth(date.GetMonth()); //début de mois de date
    itemId = AddItem(itemId, date.Format("%m [%b]"), tempDate, true); //"%B (%m)"
    
    return AddItem(itemId, date.Format("%d %A"), date, false);  //%e ne marche pas //"%A %d"
}

wxTreeItemId MainApp::AddBranchSimple(wxTreeItemId rootId, wxDateTime date)
{
    return AddItem(rootId, date.Format("%Y-%m-%d %a"), date, false);   //% F ne marche pas = Short YYYY-MM-DD date, equivalent to %Y-%m-%d
}


int MainApp::AddDateToTree(const wxDateTime& date, bool selectItem)
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
wxTreeItemId MainApp::AddItem(wxTreeItemId parent, wxString text, wxDateTime date, bool setDataEmpty)
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
    
wxTreeItemId MainApp::AddItemData(wxTreeItemId itemId, wxDateTime date, bool setDataEmpty)
{
    if ( ! setDataEmpty)
        currentDates.dates.insert(date);  // on ne stocke que les date valide
    DWItemData *itemData = new DWItemData(date, setDataEmpty);
    frame->m_treeDates->SetItemData(itemId, itemData);  
    return itemId; 
}

bool MainApp::SelectFirstTreeDatesItem()
{
    wxTreeCtrl* tree = frame->m_treeDates;
    wxTreeItemId itemId = tree->GetRootItem();
    if (tree->HasChildren(itemId)) { 
        wxTreeItemIdValue cookie;
        itemId = tree->GetFirstChild(itemId, cookie);
        tree->ScrollTo(itemId);
        if ( IsHierarchicalTree() && itemId.IsOk()) { //on a l'année
            if (tree->HasChildren(itemId)) { 
                itemId = tree->GetFirstChild(itemId, cookie); //le mois
                if ( itemId.IsOk() && tree->HasChildren(itemId) ) { 
                    itemId = tree->GetFirstChild(itemId, cookie); //le mois                    
                }
            }   
        }
        tree->SelectItem(itemId);
        return true;
    } // tree is empty
    else {
        return false;
    }
}

void MainApp::DeleteDateSelected()
{
   // wxDateTime date = GetDateFromTreeDatesSelection(); ne marche pas ici parceque ne renvoie que les dates non "empty" i.e ni les années ni les mois
    wxTreeCtrl* tree = frame->m_treeDates;
    wxTreeItemId itemId = tree->GetSelection();
    if (itemId.IsOk()) {
        wxDateTime date = GetDateFromItem(tree, itemId); 
        wxString textSelection = tree->GetItemText(itemId);
        wxString msg;
        if (! IsHierarchicalTree()) 
            msg = _("the date ")+date.FormatDate();
        else if (textSelection.length()==4) //année
            msg = date.Format(_("the year %Y"));
        else if (tree->ItemHasChildren(itemId))  // mois
            msg = date.Format(_("the month %B %Y"));
        else 
            msg = _("the day ")+date.FormatDate();

        wxMessageDialog dial(frame, wxString::Format(_("Delete %s ?"),msg), _("Warning"), wxYES_NO|wxCENTER_FRAME);
        if (dial.ShowModal()==wxID_YES) { //on supprime            
            if (DeleteItemData(itemId)) {
                tree->Delete(itemId); 
                tree->Unselect();
                frame->m_textCurDate->SetLabel("");                
            }
        }
    }       
}

void DeleteDate(wxDateTime date)
{
    //todo
}

// on ne supprime que les données parce que la suppression de l'itemId se fait recursivement
bool MainApp::DeleteItemData(wxTreeItemId itemId) 
{    
    if (itemId.IsOk()) {
        wxTreeCtrl* tree = frame->m_treeDates;
        if (tree->ItemHasChildren(itemId)) {
            wxTreeItemId childId;
            wxTreeItemIdValue cookie;
            childId = tree->GetFirstChild(itemId, cookie);
            while (childId.IsOk()) {
                DeleteItemData(childId);
                childId = tree->GetNextChild(itemId, cookie);    
            }            
        }
        DWItemData* itemData = (DWItemData*) tree->GetItemData(itemId); 
        if ((itemData != NULL) && (! itemData->IsEmpty())){
            currentDates.dates.erase(itemData->GetDate());
            dwparser.DeleteItem(itemData->GetDate());
        }
        else {
            LOG(DEBUG) << "Pas de donné associée à l'item";
        }
    } 
    return true;    //todo revoir retour
} 

/*
 *  return item selected or ! isOk
 * */
wxTreeItemId MainApp::SelectDateInChild(wxTreeItemId parent, wxDateTime date)
{
    wxTreeCtrl* tree = frame->m_treeDates;
    wxTreeItemIdValue cookie;
    wxTreeItemId itemId = tree->GetFirstChild(parent, cookie);
    wxTreeItemId itemId2;
    wxDateTime itemDate;
    while(itemId.IsOk()) {
        DWItemData *itemData = (DWItemData *) tree->GetItemData(itemId);
        if ( (itemData != NULL) && (!itemData->IsEmpty()) ){ //Compare only valid dates
            itemDate = itemData->GetDate();
            if(itemDate == date) {
                tree->SelectItem(itemId); 
                return itemId;                
            }
        }
        itemId2 = SelectDateInChild(itemId, date);
        if (itemId2.IsOk())
            return itemId2;
        itemId  = tree->GetNextChild(parent, cookie);
    }
    return itemId;  // ! IsOk()
}

void MainApp::SelectDateInTree(const wxDateTime &date)
{
    SelectDateInChild(frame->m_treeDates->GetRootItem(), date);
}

void MainApp::SetCurrentDate(const wxDateTime &date, wxWindow *sender)
{
    wxString text("");
    if (date.IsValid()) {
        LOG(DEBUG) << "Show date " << date.FormatDate();
        currentDates.today = date;    
        currentDates.yesterday = excludedDays.PreviousDay(date);
        currentDates.tomorrow = excludedDays.NextDay(date);
        GetWorkDatesAround(date, currentDates.prevAvailable, currentDates.nextAvailable);
        text = dwparser.GetWorkFromDate(date);
        
        if (sender!=frame->m_treeDates) {
            frame->DisconnectSelectionEvents();
            // utile ou mettre directement "SelectDateInTree(date);"  ?
            wxDateTime treeDate = GetDateFromTreeDatesSelection();
            if ( ( !treeDate.IsValid() ) || ( !date.IsSameDate(treeDate)  ) )
                SelectDateInTree(date);        
            frame->ConnectSelectionEvents();
        }
   }
    else {
        currentDates.Init(); 
        LOG(DEBUG) << "Date invalid, nothing to show";        
    }
    SetButtonsState();
    
    frame->SetText(text);    
    frame->m_editor->SetFocus(); //todo here ?
}

void MainApp::SetCurrentDateFromTreeDatesSelection()
{
    LOG(DEBUG) << "Select Date From tree";
    wxDateTime date = GetDateFromTreeDatesSelection();
    SetCurrentDate(date, frame->m_treeDates);
}
 
void MainApp::SetCurrentDateFromTreeSearchSelection()
{
    LOG(DEBUG) << "Select Date From Search";
    wxDateTime date = GetDateFromTreeSelection(frame->m_treeSearch);
    SetCurrentDate(date, frame->m_treeSearch);
}

void MainApp::SetButtonsState()
{
    frame->m_buttonAddTomorrow->SetLabel(_("Add ")+currentDates.TomorrowToString());
    frame->m_buttonAddYesterday->SetLabel(_("Add ")+currentDates.YesterdayToString());
    frame->m_buttonGoNextAvailable->SetLabel(_("Go to ")+currentDates.NextAvailableToString());
    frame->m_buttonGoPrevAvailable->SetLabel(_("Go to ")+currentDates.PrevAvailableToString());
    frame->m_textCurDate->SetLabel(currentDates.TodayToString());

    bool enable = ( !currentDates.nextAvailable.IsValid() ) || ( currentDates.tomorrow!=currentDates.nextAvailable );
    frame->m_buttonAddTomorrow->Enable(enable);
    enable = ( !currentDates.prevAvailable.IsValid() ) || ( currentDates.yesterday!=currentDates.prevAvailable );
    frame->m_buttonAddYesterday->Enable(enable);
    frame->m_buttonGoNextAvailable->Enable(currentDates.nextAvailable.IsValid());
    frame->m_buttonGoPrevAvailable->Enable(currentDates.prevAvailable.IsValid());   
}
    
void MainApp::SetNextDateAsCurrentDate()
{
    LOG(DEBUG) << "Select Next Date Available";
    SetCurrentDate(currentDates.nextAvailable, frame->m_buttonGoNextAvailable);
}

void MainApp::SetPrevDateAsCurrentDate()
{
    LOG(DEBUG) << "Select Prev Date Available";
    SetCurrentDate(currentDates.prevAvailable, frame->m_buttonGoPrevAvailable);
}
  
void MainApp::AddTomorrowToTree()
{    
    if (currentDates.tomorrow.IsValid())
        AddDateToTree(currentDates.tomorrow, true);
    else
        LOG(DEBUG) << "Tomorrow invalid";
}

void MainApp::AddYesterdayToTree()
{
     if (currentDates.yesterday.IsValid())
        AddDateToTree(currentDates.yesterday, true);
    else
        LOG(DEBUG) << "Yesterday invalid";    
}

wxDateTime MainApp::GetDateFromTreeDatesSelection()
{
   return  GetDateFromTreeSelection(frame->m_treeDates);
}

wxDateTime MainApp::GetDateFromTreeSelection(wxTreeCtrl* tree)
{
    return GetDateFromItem(tree, tree->GetSelection());
}
 
wxDateTime MainApp::GetDateFromItem(wxTreeCtrl* tree, wxTreeItemId itemId)
{
    if(itemId.IsOk()) {
        DWItemData* itemData = (DWItemData*) tree->GetItemData(itemId);
        if ( (itemData != NULL) && (!itemData->IsEmpty()) )
//        if (itemData != NULL)
            return itemData->GetDate();
        LOG(DEBUG) << "Elément selectionné vide";    
    } 
    else
        LOG(DEBUG) << "Aucun élément selectionné";
    return wxDateTime((time_t)-1); 
}
     
wxString MainApp::GetCurrentDateWork()
{
    return dwparser.GetWorkFromDate(currentDates.today);
}

void MainApp::GetWorkDatesAround(const wxDateTime& date, wxDateTime& prevDate, wxDateTime& nextDate)
{
    std::set<wxDateTime>::iterator it; 
//currentNextAvailable = GetNextDateFromTree(date);
    prevDate = (time_t)-1;
    nextDate = (time_t)-1;       
    if (! date.IsValid()) return;
    it = currentDates.dates.find(date);
    if (it != currentDates.dates.end()) { // date trouvée
        if (it != currentDates.dates.begin()) {
            it--; //jour precedent
            LOG(DEBUG) << "precedent " << (*it).Format().ToStdString(); 
            prevDate = *it;
            it++; //retour à date
        }
        LOG(DEBUG) << "actuel " << (*it).Format().ToStdString(); 
        it++;  //jour suivant
        LOG(DEBUG) << "suivant " << (*it).Format().ToStdString(); 
        if (it != currentDates.dates.end())
            nextDate = *it;     
    }    
}

int MainApp::Save()
{
    frame->OnStatusBarMessage(_("Save at ")+wxDateTime::Now().FormatTime().ToStdString());
    return dwparser.Save();    
}

int MainApp::SaveAs(wxString filename)
{
    frame->OnStatusBarMessage(_("Save As... at ")+wxDateTime::Now().FormatTime().ToStdString());
    return dwparser.SaveAs(filename);
}

void MainApp::LoadFavoritesInComboBox()
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

int MainApp::AddToFavorites(wxString text)
{
    if (dwparser.AddToFavorites(text))
        frame->m_comboBoxFavorite->Append(text);
   return 0;
}

int MainApp::DeleteSelectedFavorite()
{
   int index = frame->m_comboBoxFavorite->GetSelection();
   if (index != wxNOT_FOUND) {
        wxString selection = frame->m_comboBoxFavorite->GetString(index);
        dwparser.DeleteFavorite(selection.ToUTF8());  
        frame->m_comboBoxFavorite->Delete(index);
        return 0;
   }
   return 1;
}

void MainApp::InitLanguageSupport()
{
    m_language =  wxLANGUAGE_DEFAULT;
 
    //todo fake functions, use proper implementation
//    if( userWantsAnotherLanguageThanDefault() )
//        m_language = getUsersFavoriteLanguage();

    const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(m_language);
 
    // load language if possible, fall back to english otherwise
    if(wxLocale::IsAvailable(m_language))
    {
        m_locale = new wxLocale(m_language);
 
    // normally this wouldn't be necessary as the catalog files would be found
    // in the default locations, but when the program is not installed the
    // catalogs are in the build directory where we wouldn't find them by
    // default
        wxLocale::AddCatalogLookupPathPrefix(".");
        
        #ifdef __WXGTK__
        // add locale search paths
        m_locale->AddCatalogLookupPathPrefix(wxT("/usr"));
        m_locale->AddCatalogLookupPathPrefix(wxT("/usr/local"));
        wxStandardPaths* paths = (wxStandardPaths*) &wxStandardPaths::Get();
        wxString prefix = paths->GetInstallPrefix();
        m_locale->AddCatalogLookupPathPrefix( prefix );
        #endif
 
        if (!m_locale->AddCatalog(wxT("dailywork")))
        {
            LOG(ERROR) << wxString::Format("Couldn't find/load the 'dailywork' catalog for locale '%s'.",
                       pInfo ? pInfo->GetLocaleName() : _("unknown"));
        }          
        
        if(! m_locale->IsOk() )
        { 
            LOG(ERROR) << wxString::Format("Selected language '%s' is wrong",
                       pInfo ? pInfo->GetLocaleName() : "unknown");
            delete m_locale;
            m_locale = new wxLocale( wxLANGUAGE_ENGLISH );
            m_language = wxLANGUAGE_ENGLISH;
        }
    }
    else
    {
        LOG(INFO) << wxString::Format("The selected language '%s' is not supported by your system.",
                       pInfo ? pInfo->GetLocaleName() : "unknown")  << " Try installing support for this language.";
        m_locale = new wxLocale( wxLANGUAGE_ENGLISH );
        m_language = wxLANGUAGE_ENGLISH;
    } 
}

void MainApp::UpdateCurrentWork()
{
    if (frame->m_editor->IsModified() ) {
        if (currentDates.today.IsValid()) {
            dwparser.UpdateWork(currentDates.today, frame->m_editor->GetValue()); 
        }
        else {
            LOG(DEBUG ) << "invalid date";
        }
        frame->m_editor->DiscardEdits();
    }  
}
int MainApp::CountDates()
{
    return dwparser.CountItems();
}

int MainApp::SearchInDates(wxString text)
{
    if (text.length() < 3 ) return  -1; //on prend au moins 3 caractères
    
    MapFind results;
    int n = dwparser.SearchInDates(text, results);
    if (n>0) {
        wxTreeCtrl *tree = frame->m_treeSearch;
        tree->Freeze(); //prevent drawing
        tree->DeleteAllItems();
        tree->SetWindowStyle(wxTR_HIDE_ROOT);
        wxTreeItemId rootId = tree->AddRoot(wxT("Results")); //hidden
        for (MapFind::iterator it=results.begin(); it!=results.end(); ++it) {
//            std::cout << it->first << " => " << it->second << '\n';
            wxTreeItemId itemId = tree->AppendItem(rootId, dwparser.ToTreeDate(it->date));  
            DWItemData *itemData = new DWItemData(it->date, false);
            tree->SetItemData(itemId, itemData);  
            itemId = tree->AppendItem(itemId, it->text); 
            itemData = new DWItemData(it->date, false);
            tree->SetItemData(itemId, itemData);  // rajoute la date à la ligne pour pouvoir aller à la date en selectionnant cet item
            // add data ?          
        }
        tree->ExpandAll();
        tree->Thaw(); // Re-enables window before selection     
    }
    frame->m_textSearchStat->SetLabel(wxString::Format(_("Result%s : %i"),n>1?"s":"",n));
    return n;    
}

ExcludedDays MainApp::GetExcludedDays()
{
	return excludedDays;
}

void MainApp::SetExcludedDays(ExcludedDays ed)
{
    if (ed != excludedDays) {
        ed.AutoValid();
        dwparser.SetExcludedDays(ed);
        excludedDays = ed;    
    }
}

void MainApp::SetEmptyWorkSpace()
{
    currentDates.tomorrow = wxDateTime::Now();
    currentDates.yesterday = excludedDays.PreviousDay(currentDates.tomorrow);   
    SetButtonsState();    
    frame->SetText("");  
}
