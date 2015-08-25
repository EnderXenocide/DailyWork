#include "dailyworkparser.h"
#include "dwitemdata.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

    std::ifstream ifs( "dailywork.json");
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
    tree->DeleteAllItems();
    tree->SetWindowStyle(wxTR_HIDE_ROOT);
    wxTreeItemId rootID = tree->AddRoot(wxT("Dates"));
   const Value& data = document["dailywork"];
   assert(data.IsArray());

    int retour;
    if (withHierarchy)
        retour = LoadDatesTreeHierarchy(tree, rootID, data) ;
    else
        retour = LoadDatesTreeSimple(tree, rootID, data) ;
    if (!retour)
        m_cbMessageInfo("Dates chargées"); 
    else
        m_cbMessageInfo("Erreur de chargement des dates"); 
    return 0;
}

int DailyWorkParser::LoadDatesTreeSimple(wxTreeCtrl* tree, wxTreeItemId rootID, const rapidjson::Value& data) 
{
    for (SizeType i = 0; i < data.Size(); i++) {
        const Value& c = data[i];
        const char* aDate = c["date"].GetString(); 
        int day, month, year;
        std::sscanf(aDate, "%4d-%2d-%2d",  &year, &month,  &day);
        wxTreeItemId itemID = tree->AppendItem(rootID, wxString::Format(wxT("%2d/%2d/%d"), day, month, year));  
        DWItemData* itemData = new DWItemData(c["work"].GetString());
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

int DailyWorkParser::LoadDatesTreeHierarchy(wxTreeCtrl* tree, wxTreeItemId rootID, const rapidjson::Value& data) 
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
        if (itemData != NULL)
            return std::string(itemData->GetDesc());
    }   
    m_cbMessageInfo("Aucun élément"); 
    return "";        
}
