#include "dailyworkparser.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "easylogging++.h"

using namespace rapidjson;


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

    std::ifstream ifs(JSON_FILE);
    if ( ! ifs )  { 
        m_cbMessageInfo("Fichier non trouvé");
        return -1;
    }    
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
//    m_cbMessageInfo(ss.str());
//    return -1;
    
    if (document.Parse<0>(ss.str().c_str()).HasParseError()) {    
        ParseErrorCode parseErrorCode = document.GetParseError();
        std::string strErreur = wxString::Format( 
        "Erreur de lecture du fichier (offset %u): %s\n",
        (unsigned) document.GetErrorOffset(),
        GetParseError_En(parseErrorCode) ).ToStdString();
        m_cbMessageInfo(strErreur); 
        return -1;
    }
   return 0;   
    
    // ECRITURE fwrite (buffer.GetString(), buffer.GetSize(), 1, wFile);
}

int DailyWorkParser::LoadDatesTree(wxTreeCtrl* tree, bool withHierarchy) 
{
    LOG(INFO) << "Loading Tree with json data..." ;
    tree->DeleteAllItems();
    tree->SetWindowStyle(wxTR_HIDE_ROOT);
    wxTreeItemId rootID = tree->AddRoot(wxT("Dates"));
    Value& data = document["dailywork"];
    assert(data.IsArray());

    int retour;
    if (withHierarchy)
        retour = LoadDatesTreeHierarchy(tree, rootID, data) ;
    else
        retour = LoadDatesTreeSimple(tree, rootID, data) ;
    if (!retour)
        m_cbMessageInfo("Dates chargées"); 
    else {
        m_cbMessageInfo("Erreur de chargement des dates"); 
        LOG(ERROR) << "Erreur de chargement des dates" ;
    }
    LOG(INFO) << "Tree Loaded" ;
    return 0;
}

int DailyWorkParser::LoadDatesTreeSimple(wxTreeCtrl* tree, wxTreeItemId rootID, rapidjson::Value& data) 
{
    LOG(INFO) << "Loading Tree Simple... " ;
    for (SizeType i = 0; i < data.Size(); i++) {
        Value& c = data[i];
        wxString sDate = ToTreeDate(GetDateFromItem(c)); 
        wxTreeItemId itemID = tree->AppendItem(rootID, sDate);  
        DWItemData* itemData = new DWItemData(&c);
        tree->SetItemData(itemID, itemData);
    }
//   for (Value::ConstValueIterator itr = data.Begin(); itr != d.End(); ++itr)
//        printf("%d ", itr->GetInt());

//    for (int i=0;i<10;i++) {
//        wxTreeItemId id=Tree->AppendItem(rootID,wxString::Format(wxT("Element : %d"),i+1));
//        for(int j=0;j<2*i+2;j++)
//            Tree->AppendItem(id,wxString::Format(wxT("Element : %d:%d"),i+1,j+1));
//    }
    
    return 0;
}

int DailyWorkParser::LoadDatesTreeHierarchy(wxTreeCtrl* tree, wxTreeItemId rootID, rapidjson::Value& data) 
{   //TODO fonction à faire 

   //for(Value::ConstMemberIterator it = data.MemberBegin(); it != data.MembersEnd(); it++) {
    //wxTreeItemId rootID = Tree->AddRoot(wxT("Un arbre"));
//    tree->Expand(rootID);
    return 0;
}

std::string DailyWorkParser::GetWorkFromTree(wxTreeCtrl* tree)
{
    wxTreeItemId itemID=tree->GetSelection();
    if (itemID != NULL) {
        DWItemData* itemData=(DWItemData*) tree->GetItemData(itemID);
        if (itemData != NULL) {
            Value& pair =  *itemData->GetValue(); 
            return GetWorkFromItem(pair);
        }
    }   
    LOG(ERROR) << "Aucun élément"; 
    return "";        
}

int DailyWorkParser::UpdateWork(DWItemData* itemData, std::string text)
{
    if (itemData != NULL) {
         //char buffer[1024];
        //int len = sprintf(buffer, "%s", text); 
        //teste qui marche : text = "éàer";
        Value& pair =  *itemData->GetValue(); 
        SetWorkFromItem(pair, text);
       //memset(buffer, 0, sizeof(len));
   }
    else {
        LOG(ERROR) << "Mise à jour impossible";
        return -1;        
    }
    return 0;
}

int DailyWorkParser::Save()
{
    FILE* fp = fopen(JSON_FILE, "wb"); // non-Windows use "w"
    char writeBuffer[65536];
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);
    return 0;
}
int DailyWorkParser::AddDateToTree(wxTreeCtrl* tree, rapidjson::Value& data, wxTreeItemId addBeforeId)
{

}

std::string DailyWorkParser::GetDateFromItem(rapidjson::Value& item)
{
    return item["date"].GetString(); 
}

std::string DailyWorkParser::GetWorkFromItem(rapidjson::Value& item)
{
    return item["work"].GetString(); 
}

/*
 * Ex : Transfome une date 2015-12-31 en 31/12/2015
 * */
wxString DailyWorkParser::ToTreeDate(std::string aDWDate)
{
    int day, month, year;
    std::sscanf(aDWDate.c_str(), "%4d-%2d-%2d",  &year, &month,  &day);
    return wxString::Format(wxT("%2d/%2d/%d"), day, month, year) ;
}

int DailyWorkParser::SetWorkFromItem(rapidjson::Value& item, std::string text)
{
    assert(item.IsObject());
    item["work"].SetString(text.data(), text.size(), document.GetAllocator());
    return 0;
}
