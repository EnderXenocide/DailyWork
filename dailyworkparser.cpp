#include "dailyworkparser.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "easylogging++.h"

DailyWorkParser::DailyWorkParser()
{
    modified = false;
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
    modified = false;

    LOG(INFO) << "Parse file " << JSON_FILE;
    std::ifstream ifs(JSON_FILE);
    if(!ifs) {
        LOG(ERROR) << _("File not found");
        m_cbMessageInfo(_("File not found"));
        return -1;
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    //    m_cbMessageInfo(ss.str());
    //    return -1;

    int retour = 0;
    if(document.Parse<0>(ss.str().c_str()).HasParseError()) {
        ParseErrorCode parseErrorCode = document.GetParseError();
        wxString strErreur = wxString::Format(_("Error reading file (offset %u): %s\n"),
                                                 (unsigned)document.GetErrorOffset(),
                                                 GetParseError_En(parseErrorCode));
        LOG(ERROR) << strErreur;                                         
        m_cbMessageInfo(strErreur);
        retour = -1;
    }
    TestAndUpdate();

    return retour;
}

int DailyWorkParser::UpdateWork(const wxDateTime& date, wxString text)
{
    if(date.IsValid()) {
        std::string sdate = ToDWDate(date).ToStdString();
        Value &array = document[JSON_ITEMS];
        for (SizeType i = 0; i < array.Size(); i++) {
            if (array[i][JSON_DATE].GetString()==sdate) {
                SetWorkFromItem(array[i], text); 
                return 0;
            }
        }
        LOG(DEBUG) << "Date non trouvée :" << sdate;
    }
    LOG(DEBUG) << "Mise à jour impossible";
    return -1;
}

int DailyWorkParser::Save()
{    
    return SaveAs(JSON_FILE);
}

int DailyWorkParser::SaveAs(wxString filename)
{
    wxString msg = "Enregistrement";
    if (filename != JSON_FILE)
        msg += " sous "+filename;
    LOG(INFO) << msg;
    FILE* fp = fopen(filename, "wb"); // non-Windows use "w"
    char writeBuffer[65536];
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);

    modified = false;
    return 0;
}


wxDateTime DailyWorkParser::GetDateFromItem(int itemIndex)
{
    const Value& item = document[JSON_ITEMS][itemIndex]; 
    if (item.IsObject()) {
        return DWToDate(item[JSON_DATE].GetString());        
    }
    else {
        return wxDateTime((time_t)-1);        
    }
}

wxString DailyWorkParser::GetWorkFromDate(const wxDateTime& date)
{
    if ( date.IsValid() ) {
        std::string sdate = ToDWDate(date).ToStdString();
        Value &array = document[JSON_ITEMS];
        for (SizeType i = 0; i < array.Size(); i++) {
            if (array[i][JSON_DATE].GetString()==sdate) {
                return GetWorkFromItem(array[i]);
            }
        }
        LOG(DEBUG) << "Date non trouvée :" << sdate;
    } 
    else {
        LOG(DEBUG) << "Date non valide";        
    }
    return "";    
}

wxString DailyWorkParser::GetWorkFromItem(const Value& item) 
{
    return item[JSON_WORK].GetString();
}

/*
 * Ex : Transfome une date en 2015-12-31
 * */
wxString DailyWorkParser::ToDWDate(const wxDateTime& date) const
{
    return wxString::Format(JSON_DATE_FORMAT, date.GetYear(), date.GetMonth()+1, date.GetDay());
}

/*
 * Ex : Transfome une date 2015-12-31 en 31/12/2015
 * */
wxString DailyWorkParser::ToTreeDate(const wxDateTime& date) const
{
    //    std::sscanf(aDWDate.c_str(), JSON_DATE_FORMAT, &year, &month, &day);
    return wxString::Format(TREE_DATE_FORMAT, date.GetDay(), date.GetMonth()+1, date.GetYear());
}

int DailyWorkParser::SetWorkFromItem(Value& item, wxString text)
{
    assert(item.IsObject());
    std::string utf8 = text.ToUTF8().data();
    item[JSON_WORK].SetString(utf8.data(), utf8.size(), document.GetAllocator());
    modified = true;
    return 0;
}

wxDateTime DailyWorkParser::DWToDate(const wxString DWDate)
{
    wxDateTime date;
//	if (!date.ParseISODate(DWDate)) {
	if (!date.ParseFormat(DWDate, JSON_DATE_FORMAT_EXT, wxDateTime::Today())) {
        LOG(ERROR) << "Can't convert " << DWDate << "to date";
    }
    return date;
}

int DailyWorkParser::DeleteItem(wxDateTime date)
{
    if (date.IsValid()) {
        std::string sdate = ToDWDate(date).ToStdString();
        Value & array = document[JSON_ITEMS];
        for (Value::ConstValueIterator itr = array.Begin(); itr != array.End(); itr++) {
            if (itr->FindMember(JSON_DATE)->value.GetString()==sdate) {
                array.Erase(itr);
                LOG(INFO) << "Supprime la date " << sdate;
                modified = true;               
                return 0;   
            }        
        }   
    }
    return 1; //non supprimé
}

void DailyWorkParser::AddItem(wxDateTime& date, wxString work)
{  
    std::string DWDate = ToDWDate(date).ToStdString();
    std::string utf8Work = work.ToUTF8().data();
    LOG(INFO) << "Ajoute Date " << DWDate;
    Document::AllocatorType& allocator = document.GetAllocator();
    Value value(kObjectType);
    Value valueStringDate(kStringType);
    valueStringDate.SetString(DWDate.data(), DWDate.size(), document.GetAllocator());
    value.AddMember(JSON_DATE, valueStringDate, allocator); 
    Value valueString(kStringType);
    valueString.SetString(utf8Work.data(), utf8Work.size(), document.GetAllocator());
    value.AddMember(JSON_WORK, valueString, allocator);  
    Value &array = document[JSON_ITEMS];
    array.PushBack(value, allocator); 
    modified = true;
    //return array[array.Size()-1];//todo valid ?      
    
//    static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
//    LOG(INFO) << "Type of member is " << kTypeNames[value.GetType()];    
}

SizeType DailyWorkParser::CountItems()
{
    return document[JSON_ITEMS].Size();
}

SizeType DailyWorkParser::CountFavorites()
{
    return document[JSON_FAVORITES].Size();
}

wxString DailyWorkParser::GetFavorite(int itemIndex)
{
    const Value& item = document[JSON_FAVORITES][itemIndex]; 
    if (item.IsString()) {
        return wxString::FromUTF8(item.GetString());        
    }
    else {
        return "";        
    }
}

void DailyWorkParser::New()
{
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();
    Value items(kArrayType);
    document.AddMember(JSON_ITEMS, items, allocator);
    document.AddMember(JSON_FAVORITES, items, allocator);
    Value version(1);
    document.AddMember(JSON_VERSION, version, allocator);
    modified = true;
}

void DailyWorkParser::TestAndUpdate()
{
    Document::AllocatorType& allocator = document.GetAllocator();
    if (document.IsNull())
        document.SetObject();
        
    if (!document.HasMember(JSON_ITEMS))
    {
        Value items(kArrayType);
        document.AddMember(JSON_ITEMS, items, allocator);  
        modified = true; 
    }  
    
    if (!document.HasMember(JSON_VERSION))
    {
        Value items(2);
        document.AddMember(JSON_VERSION, items, allocator);  
        modified = true; 
    }  
    
    version = document[JSON_VERSION].GetInt();
    if (version==1) 
       document[JSON_VERSION].SetInt(2);  //passage à la version 2
    if (!document.HasMember(JSON_FAVORITES)) {
        Value items(kArrayType);
        document.AddMember(JSON_FAVORITES, items, allocator);  
        modified = true;          
    }                
}

bool DailyWorkParser::AddToFavorites(wxString text)
{
    std::string utf8Text = text.ToUTF8().data();
    if (IsInFavorites(text)) {
         LOG(INFO) << "Pas d'ajout du favoris <" << utf8Text <<"> déja éxistant";
        return false;
    }
    LOG(INFO) << "Ajoute le favoris <" << utf8Text <<">";
    Document::AllocatorType& allocator = document.GetAllocator();
    Value valueString(kStringType);
    valueString.SetString(utf8Text.c_str(), utf8Text.size(), document.GetAllocator());
    Value &array = document[JSON_FAVORITES];
    array.PushBack(valueString, allocator); 
    modified = true;
    return true;
}

int DailyWorkParser::DeleteFavorite(wxString text)
{
    std::string utf8Text = text.ToUTF8().data();
    Value &array = document[JSON_FAVORITES];
    for (Value::ConstValueIterator itr = array.Begin(); itr != array.End(); itr++) {
        if (itr->GetString()==utf8Text) {
            array.Erase(itr);
            LOG(INFO) << "Supprime le favoris <" << utf8Text <<">";
            modified = true;               
            return 0;   
        }        
    } 
    LOG(DEBUG) << "Favoris <" << utf8Text <<"> non trouvé";
    return  -1; 
}

//bool DailyWorkParser::FindItem(const wxDateTime& date, Value& item)
//{
//    std::string sdate = ToDWDate(date).ToStdString();
//    Value &array = document[JSON_ITEMS];
//    for (SizeType i = 0; i < array.Size(); i++) {
//        if (array[i][JSON_DATE].GetString()==sdate) {
//            item = array[i]; 
//            return TRUE;  
//        }  
//    }
//    LOG(DEBUG) << "Date non trouvée :" << sdate;
//    return false;
//}

bool DailyWorkParser::IsInFavorites(wxString text)
{
    std::string utf8Text = text.ToUTF8().data();
    Value &array = document[JSON_FAVORITES];
    for (Value::ConstValueIterator itr = array.Begin(); itr != array.End(); itr++) {
        if (itr->GetString()==utf8Text) {
                return true;
        }
    } 
    return false; 
}
