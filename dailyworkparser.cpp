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

    int retour = 0;
    if(document.Parse<0>(ss.str().c_str()).HasParseError()) {
        ParseErrorCode parseErrorCode = document.GetParseError();
        std::string strErreur = wxString::Format("Erreur de lecture du fichier (offset %u): %s\n",
                                                 (unsigned)document.GetErrorOffset(),
                                                 GetParseError_En(parseErrorCode)).ToStdString();
        m_cbMessageInfo(strErreur);
        retour = -1;
    }
    TestAndUpdate();

    return retour;
}

int DailyWorkParser::UpdateWork(const wxDateTime& date, std::string text)
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
        wxDateTime date((time_t)-1);
        return date;        
    }
}

std::string DailyWorkParser::GetWorkFromDate(const wxDateTime& date)
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

std::string DailyWorkParser::GetWorkFromItem(const Value& item) 
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

int DailyWorkParser::SetWorkFromItem(Value& item, std::string text)
{
    assert(item.IsObject());
    item[JSON_WORK].SetString(text.data(), text.size(), document.GetAllocator());
    modified = true;
    return 0;
}

wxDateTime DailyWorkParser::DWToDate(const std::string DWDate)
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

void DailyWorkParser::AddItem(wxDateTime& date, std::string work)
{  
    std::string DWDate = ToDWDate(date).ToStdString();
    LOG(INFO) << "Ajoute Date " << DWDate;
    Document::AllocatorType& allocator = document.GetAllocator();
    Value value(kObjectType);
    Value valueStringDate(kStringType);
    valueStringDate.SetString(DWDate.data(), DWDate.size(), document.GetAllocator());
    value.AddMember(JSON_DATE, valueStringDate, allocator); 
    Value valueString(kStringType);
    valueString.SetString(work.data(), work.size(), document.GetAllocator());
    value.AddMember(JSON_WORK, valueString, allocator);  
    Value &array = document[JSON_ITEMS];
    array.PushBack(value, allocator); 
    modified = true;
    //return array[array.Size()-1];//todo valid ?      
    
//    static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
//    LOG(INFO) << "Type of member is " << kTypeNames[value.GetType()];    
}

wxDateTime DailyWorkParser::getSelectedDate()
{
    assert(IsSelectedOk());
    return  DWToDate(selected[JSON_DATE].GetString()); 
}

std::string DailyWorkParser::getSelectedWork()
{
    assert(IsSelectedOk());
    return selected[JSON_WORK].GetString();
}

int DailyWorkParser::setSelectedDate(const wxDateTime& date)
{
    if (IsSelectedOk())  {
        std::string text = ToDWDate(date).ToStdString();
        selected[JSON_DATE].SetString(text.data(), text.size(), document.GetAllocator());
        modified = true;
        return 0;
        }
    else
        return -1;
}

int DailyWorkParser::setSelectedWork(std::string work)
{
    if (IsSelectedOk())  {
        selected[JSON_WORK].SetString(work.data(), work.size(), document.GetAllocator());
        modified = true;
        return 0;        
    }
    else
        return -1;
}

SizeType DailyWorkParser::CountItems()
{
    return document[JSON_ITEMS].Size();
}

SizeType DailyWorkParser::CountFavorites()
{
    return document[JSON_FAVORITES].Size();
}

bool DailyWorkParser::IsSelectedOk()
{
    return (selected != NULL) && (selected.IsObject());
}

wxString DailyWorkParser::GetFavorite(int itemIndex)
{
    const Value& item = document[JSON_FAVORITES][itemIndex]; 
    if (item.IsString()) {
        return item.GetString();        
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
    if (version>1) 
        if (!document.HasMember(JSON_FAVORITES)) {
            Value items(kArrayType);
            document.AddMember(JSON_FAVORITES, items, allocator);  
            modified = true;          
    }                
}

int DailyWorkParser::AddToFavorites(wxString text)
{
    LOG(INFO) << "Ajoute le favoris <" << text <<">";
    Document::AllocatorType& allocator = document.GetAllocator();
    Value valueString(kStringType);
    valueString.SetString(text.data(), text.size(), document.GetAllocator());
    Value &array = document[JSON_FAVORITES];
    array.PushBack(valueString, allocator); 
    modified = true;
}

int DailyWorkParser::DeleteFavorite(wxString text)
{
    Value &array = document[JSON_FAVORITES];
    for (Value::ConstValueIterator itr = array.Begin(); itr != array.End(); itr++) {
        if (itr->GetString()==text) {
            array.Erase(itr);
            LOG(INFO) << "Supprime le favoris <" << text <<">";
            modified = true;               
            return 0;   
        }        
    } 
    LOG(DEBUG) << "Favoris <" << text <<"> non trouvé";
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
