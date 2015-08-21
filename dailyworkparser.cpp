#include "DailyWorkParser.h"
#include <iostream>
//#include <cstdio>
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

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
//   const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    const char* json = "{\"dailywork\":[ {\"date\":\"2015-07-24\",\"work\":\"rien\"}," 
                               "{\"date\":\"2015-07-23\",\"work\":\"nothing\"},"
                               "{\"date\":\"2015-07-22\",\"work\":\"niet\"} ] }";
    if (document.Parse(json).HasParseError()) {
        //rapidjson::ParseErrorCode parseErrorCode = d.GetParseErrorCode();
        fprintf(stderr, "\nError(offset %u): %s\n", 
        (unsigned) document.GetErrorOffset(),
        "erreur"); //rapidjson::GetParseError_En(parseErrorCode)
        m_cbMessageInfo("Erreur de lecture du fichier");
        return -1;
    }
    //rapidjson::Value& s = d["project"];
    return 0;   
}

int DailyWorkParser::LoadDatesTree(wxTreeCtrl* Tree, bool withHierarchy) 
{
    int retour;
    if (withHierarchy)
        retour = LoadDatesTreeHierarchy(Tree) ;
    else
        retour = LoadDatesTreeSimple(Tree) ;
    if (!retour)
        m_cbMessageInfo("Dates chargées"); //todo unicode
    else
        m_cbMessageInfo("Erreur chargement arbre"); //todo unicode
    return 0;
}

int DailyWorkParser::LoadDatesTreeSimple(wxTreeCtrl* Tree) 
{
    Tree->DeleteAllItems();
    Tree->SetWindowStyle(wxTR_HIDE_ROOT);
    wxTreeItemId rootID = Tree->AddRoot(wxT("Dates"));
   const Value& data = document["dailywork"];
   assert(data.IsArray());
   //for(Value::ConstMemberIterator it = data.MemberBegin(); it != data.MembersEnd(); it++) {
    for (SizeType i = 0; i < data.Size(); i++) {
        const Value& c = data[i];
        const char* aDate = c["date"].GetString(); 
        int day, month, year;
        std::sscanf(aDate, "%4d-%2d-%2d",  &year, &month,  &day);
        Tree->AppendItem(rootID, wxString::Format(wxT("%2d/%2d/%d"), day, month, year));        
    }
    Tree->Expand(rootID);
    m_cbMessageInfo("Dates chargées"); //todo unicode
//   for (Value::ConstValueIterator itr = data.Begin(); itr != d.End(); ++itr)
//        printf("%d ", itr->GetInt());

//    for (int i=0;i<10;i++) {
//        wxTreeItemId id=Tree->AppendItem(rootID,wxString::Format(wxT("Element : %d"),i+1));
//        for(int j=0;j<2*i+2;j++)
//            Tree->AppendItem(id,wxString::Format(wxT("Element : %d:%d"),i+1,j+1));
//    }
    
    return 0;
}

int DailyWorkParser::LoadDatesTreeHierarchy(wxTreeCtrl* Tree) 
{   
    Tree->DeleteAllItems();
    Tree->SetWindowStyle(wxTR_DEFAULT_STYLE);
   const Value& data = document["dailywork"];
   assert(data.IsArray());

   //for(Value::ConstMemberIterator it = data.MemberBegin(); it != data.MembersEnd(); it++) {
    wxTreeItemId rootID = Tree->AddRoot(wxT("Un arbre"));
    for (SizeType i = 0; i < data.Size(); i++) {
        const Value& c = data[i];
        const char* aDate = c["date"].GetString(); 
        int day, month, year;
        std::sscanf(aDate, "%4d-%2d-%2d",  &year, &month,  &day);
        Tree->AppendItem(rootID, wxString::Format(wxT("%2d/%2d/%d"), day, month, year));        
    }
    Tree->Expand(rootID);
    return 0;
}