#include "DailyWorkParser.h"
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

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
    const char* json = "{ \"dailywork\":[ {\"date\":\"2015-07-24\",\"work\":\"rien\"}," 
                               "{\"date\":\"2015-07-23\",\"work\":\"nothing\"},"
                               "{\"date\":\"2015-07-22\",\"work\":\"niet\"} ] }";
    if (d.Parse(json).HasParseError()) {
        //rapidjson::ParseErrorCode parseErrorCode = d.GetParseErrorCode();
        fprintf(stderr, "\nError(offset %u): %s\n", 
        (unsigned)d.GetErrorOffset(),
        "erreur"); //rapidjson::GetParseError_En(parseErrorCode)
        m_cbMessageInfo("Erreur de lecture du fichier");
        return -1;
    }
    //rapidjson::Value& s = d["project"];
    //m_cbMessageInfo(s.GetString());

    return 0;   
}

int DailyWorkParser::LoadDatesTree(wxTreeCtrl* Tree) 
{
   wxTreeItemId rootID=Tree->AddRoot(wxT("Un arbre"));
//   for (rapidjson::Value::ConstValueIterator itr = d.Begin(); itr != d.End(); ++itr)
//        printf("%d ", itr->GetInt());

//    for (int i=0;i<10;i++) {
//        wxTreeItemId id=Tree->AppendItem(rootID,wxString::Format(wxT("Element : %d"),i+1));
//        for(int j=0;j<2*i+2;j++)
//            Tree->AppendItem(id,wxString::Format(wxT("Element : %d:%d"),i+1,j+1));
//    }
    
    return 0;
}
