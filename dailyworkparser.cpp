#include "dailyworkparser.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "easylogging++.h"

DailyWorkParser::DailyWorkParser()
{
}

DailyWorkParser::~DailyWorkParser()
{
}

void DailyWorkParser::ConnectCallback(CallbackMessageInfo cb)
{
    m_cbMessageInfo = cb;
}

int DailyWorkParser::Parse()
{
    //    const char* json = "{\"dailywork\":[ {\"date\":\"2015-07-24\",\"work\":\"rien\"},"
    //                               "{\"date\":\"2015-07-23\",\"work\":\"nothing\"},"
    //                               "{\"date\":\"2015-07-22\",\"work\":\"niet\"} ] }";
    //    if (document.Parse(json).HasParseError()) {
    LOG(INFO) << "Parse file";
    std::ifstream ifs(JSON_FILE);
    if(!ifs) {
        m_cbMessageInfo("Fichier non trouvé");
        return -1;
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    //    m_cbMessageInfo(ss.str());
    //    return -1;

    if(document.Parse<0>(ss.str().c_str()).HasParseError()) {
        ParseErrorCode parseErrorCode = document.GetParseError();
        std::string strErreur = wxString::Format("Erreur de lecture du fichier (offset %u): %s\n",
                                                 (unsigned)document.GetErrorOffset(),
                                                 GetParseError_En(parseErrorCode)).ToStdString();
        m_cbMessageInfo(strErreur);
        return -1;
    }
    return 0;

    // ECRITURE fwrite (buffer.GetString(), buffer.GetSize(), 1, wFile);
}

int DailyWorkParser::LoadDatesTree(wxTreeCtrl* tree)
{
    LOG(INFO) << "Loading Tree with json data...";
    tree->DeleteAllItems();
    tree->SetWindowStyle(wxTR_HIDE_ROOT);
    wxTreeItemId rootID = tree->AddRoot(wxT("Dates"));
    Value& dataArray = document[JSON_ARRAY];
    assert(dataArray.IsArray());

    int retour;
    if(treeWithHierarchy)
        retour = LoadDatesTreeHierarchy(tree, rootID, dataArray);
    else
        retour = LoadDatesTreeSimple(tree, rootID, dataArray);
    if(!retour)
        m_cbMessageInfo("Dates chargées");
    else {
        m_cbMessageInfo("Erreur de chargement des dates");
        LOG(ERROR) << "Erreur de chargement des dates";
    }
    LOG(INFO) << "Tree Loaded";
    return 0;
}

int DailyWorkParser::LoadDatesTreeSimple(wxTreeCtrl* tree, wxTreeItemId rootID, rapidjson::Value& dataArray)
{
    LOG(INFO) << "Loading Tree Simple... ";
    for(SizeType i = 0; i < dataArray.Size(); i++) {
        Value& c = dataArray[i];
        wxString sDate = ToTreeDate(GetDateFromItem(c));
        wxTreeItemId itemID = tree->AppendItem(rootID, sDate);
        DWItemData* itemData = new DWItemData(&c);
        tree->SetItemData(itemID, itemData);
    }
    //   for (Value::ConstValueIterator itr = dataArray.Begin(); itr != d.End(); ++itr)
    //        printf("%d ", itr->GetInt());

    //    for (int i=0;i<10;i++) {
    //        wxTreeItemId id=Tree->AppendItem(rootID,wxString::Format(wxT("Element : %d"),i+1));
    //        for(int j=0;j<2*i+2;j++)
    //            Tree->AppendItem(id,wxString::Format(wxT("Element : %d:%d"),i+1,j+1));
    //    }

    return 0;
}

int DailyWorkParser::LoadDatesTreeHierarchy(wxTreeCtrl* tree, wxTreeItemId rootID, Value& dataArray)
{ // TODO fonction à faire

    // for(Value::ConstMemberIterator it = dataArray.MemberBegin(); it != dataArray.MembersEnd(); it++) {
    // wxTreeItemId rootID = Tree->AddRoot(wxT("Un arbre"));
    //    tree->Expand(rootID);
    LOG(INFO) << "Loading Tree Hierarchy... ";
    wxTreeItemId itemId;
    for(SizeType i = 0; i < dataArray.Size(); i++) {
        Value& c = dataArray[i];
        TDate date = GetDateFromItem(c);
        itemId = AddItem(tree, tree->GetRootItem(), std::to_string(date.annee));
        itemId = AddItem(tree, itemId, std::to_string(date.mois));
        itemId = AddItem(tree, itemId, std::to_string(date.jour));
        DWItemData* itemData = new DWItemData(&c);
        tree->SetItemData(itemId, itemData);
    }
    return 0;
}

std::string DailyWorkParser::GetWorkFromTree(wxTreeCtrl* tree)
{
    wxTreeItemId itemID = tree->GetSelection();
    if(itemID.IsOk()) {
        DWItemData* itemData = (DWItemData*)tree->GetItemData(itemID);
        if(itemData != NULL) {
            Value& pair = *itemData->GetValue();
            return GetWorkFromItem(pair);
        } else
            LOG(DEBUG) << "Pas de donné associée à l'item";
    } else
        LOG(DEBUG) << "Aucun élément selectionné";
    return "";
}

int DailyWorkParser::UpdateWork(DWItemData* itemData, std::string text)
{
    if(itemData != NULL) {
        Value& pair = *itemData->GetValue();
        SetWorkFromItem(pair, text);
    } else {
        LOG(ERROR) << "Mise à jour impossible";
        return -1;
    }
    return 0;
}

int DailyWorkParser::Save()
{
    LOG(INFO) << "Enregistrement";
    FILE* fp = fopen(JSON_FILE, "wb"); // non-Windows use "w"
    char writeBuffer[65536];
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);
    return 0;
}

TDate DailyWorkParser::GetDateFromItem(Value& item)
{
    return DWToDate(item[JSON_DATE].GetString());
}

std::string DailyWorkParser::GetWorkFromItem(Value& item)
{
    return item[JSON_WORK].GetString();
}

/*
 * Ex : Transfome une date en 2015-12-31
 * */
wxString DailyWorkParser::ToDWDate(TDate date)
{
    return wxString::Format(JSON_DATE_FORMAT, date.jour, date.mois, date.annee);
}

/*
 * Ex : Transfome une date 2015-12-31 en 31/12/2015
 * */
wxString DailyWorkParser::ToTreeDate(TDate date)
{
    //    std::sscanf(aDWDate.c_str(), JSON_DATE_FORMAT, &year, &month, &day);
    return wxString::Format(TREE_DATE_FORMAT, date.jour, date.mois, date.annee);
}

int DailyWorkParser::SetWorkFromItem(rapidjson::Value& item, std::string text)
{
    assert(item.IsObject());
    item["work"].SetString(text.data(), text.size(), document.GetAllocator());
    return 0;
}

int DailyWorkParser::AddDateToTree(wxTreeCtrl* tree, TDate date, bool selectItem)
{
    Value* value = AddValue(date);

    wxTreeItemId itemId;
    if(treeWithHierarchy) {
        itemId = AddItem(tree, tree->GetRootItem(), wxString::Format("%4d", date.annee));
        itemId = AddItem(tree, itemId, wxString::Format("%2d", date.mois));
        itemId = AddItem(tree, itemId, wxString::Format("%2d", date.jour));
    } else {
        itemId = AddItem(tree, tree->GetRootItem(), ToTreeDate(date));
    }
    DWItemData* data = new DWItemData(value);
    tree->SetItemData(itemId, data);
    if(selectItem)
        tree->SelectItem(itemId, false);
    return 0;
}

/*
 * Cherche l'item avec text comme text ou ajout un nouveau dans l'ordre alphabéthique inverse
 */
wxTreeItemId DailyWorkParser::AddItem(wxTreeCtrl* tree, wxTreeItemId parent, wxString text)
{
    wxTreeItemIdValue cookie;
    wxTreeItemId itemId = tree->GetFirstChild(parent, cookie);
    while(itemId.IsOk()) {
        wxString itemText = tree->GetItemText(itemId);
        if(itemText == text)
            return itemId;                         // pas besoin d'ajouter l'item
        else if(text < itemText) {                 // item voulu doit se trouver avant
            itemId = tree->GetPrevSibling(itemId); // on prend l'item precedent pour pouvoir inserer celui qu'on veux
            if(itemId.IsOk())
                return tree->InsertItem(parent, itemId, text);
            else                                          // pas d'item avant
                return tree->InsertItem(parent, 0, text); // insert item en premier
        }
        tree->GetNextChild(parent, cookie);
    }
    return tree->AppendItem(parent, text); // item voulu pas trouver
}

Value* DailyWorkParser::AddValue(TDate date)
{
    wxString DWDate = ToDWDate(date);
    Document::AllocatorType& allocator = document.GetAllocator();
    Value value(kObjectType);
    Value valueString(kStringType);
    valueString.SetString(DWDate.c_str(), allocator);
    value.AddMember("date", valueString, allocator);  //todo JSON_DATE ne marche pas
    value.AddMember("work", "", allocator); //todo JSON_WORK ne marche pas
    document[JSON_ARRAY].PushBack(value, allocator);
    return &value; //todo valid ?
}

TDate  DailyWorkParser::DWToDate(std::string DWDate)
{
    int year, month, day;
    TDate date;
    int n = std::sscanf(DWDate.c_str(), JSON_DATE_FORMAT, &date.annee, &date.mois, &date.jour);
    if (n<3)  {
        LOG(ERROR) << "Can't convert " << DWDate << "to date";
        time_t now = time(0);
        // convert now to tm struct for UTC
        tm* gmtm = gmtime(&now);
        date.annee = gmtm->tm_year+1900;
        date.mois = gmtm->tm_mon+1;        
        date.jour = gmtm->tm_mday;        
    }
   // timev.tm_year = year-1900; timev.tm_mon = month-1; timev.tm_mday = day; 
    return date; 
}
