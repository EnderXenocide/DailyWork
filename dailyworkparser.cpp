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

    if(document.Parse<0>(ss.str().c_str()).HasParseError()) {
        ParseErrorCode parseErrorCode = document.GetParseError();
        std::string strErreur = wxString::Format("Erreur de lecture du fichier (offset %u): %s\n",
                                                 (unsigned)document.GetErrorOffset(),
                                                 GetParseError_En(parseErrorCode)).ToStdString();
        m_cbMessageInfo(strErreur);
        return -1;
    }
    assert(document[JSON_ARRAY].IsArray());
    assert(document[JSON_VERSION].IsInt());
    version = document[JSON_VERSION].GetInt();
    return 0;

    // ECRITURE fwrite (buffer.GetString(), buffer.GetSize(), 1, wFile);
}

int DailyWorkParser::UpdateWork(const wxDateTime& date, std::string text)
{
    if(date.IsValid()) {
        Value item;
        if (FindItem(date, item)) {
            SetWorkFromItem(item, text);
            return 0;
        }
    } 
    LOG(ERROR) << "Mise à jour impossible";
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
    const Value& item = document[JSON_ARRAY][itemIndex]; 
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
    Value item;
    if ( date.IsValid() && FindItem(date, item) ) {
            return GetWorkFromItem(item);
    } 
    else {
        LOG(DEBUG) << "Date non valide ou non trouvée";        
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
        Value & array = document[JSON_ARRAY];
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
    Value &array = document[JSON_ARRAY];
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

//int DailyWorkParser::selectItemFromDate(DWItemData* itemData)
//{
//    if (itemData != NULL) {
//        selected = itemData->GetValue();
//        return 0;
//    }
//    else {
//        selected = NULL;
//        LOG(DEBUG) << "Pas de donné associée à l'item";
//        return 1;
//    }   
//}  
 
SizeType DailyWorkParser::Count()
{
    return document[JSON_ARRAY].Size();
}

bool DailyWorkParser::IsSelectedOk()
{
    return (selected != NULL) && (selected.IsObject());
}

bool DailyWorkParser::FindItem(const wxDateTime& date, Value& item)
{
    std::string sdate = ToDWDate(date).ToStdString();
    Value &array = document[JSON_ARRAY];
    for (SizeType i = 0; i < array.Size(); i++) {
        if (array[i][JSON_DATE].GetString()==sdate) {
            item = array[i]; 
            return TRUE;  
        }  
    }
    LOG(DEBUG) << "Date non trouvée :" << sdate;
    return FALSE;
}
