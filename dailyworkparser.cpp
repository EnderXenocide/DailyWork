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

int DailyWorkParser::UpdateWork(DWItemData* itemData, std::string text)
{
    if(itemData != NULL) {
        Value& item = itemData->GetValue();
        SetWorkFromItem(item, text);
    } else {
        LOG(ERROR) << "Mise à jour impossible";
        return -1;
    }
    return 0;
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


wxDateTime DailyWorkParser::GetDateFromItem(const Value& item)
{
    return DWToDate(item[JSON_DATE].GetString());
}

std::string DailyWorkParser::GetWorkFromDWItem(DWItemData* itemData)
{
    if(itemData != NULL) {
        const Value& item = itemData->GetValue();
        return GetWorkFromItem(item);
    } 
    else
        LOG(DEBUG) << "Pas de donné associée à l'item";
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

DWItemData* DailyWorkParser::AddDate(wxDateTime& date)
{
    Value &value = AddValue(date);
    //SetWorkFromItem(value, "empty");
    return new DWItemData(value);
}

Value& DailyWorkParser::AddValue(wxDateTime& date)
//Value& DailyWorkParser::AddValue(wxDateTime& date)
{
    std::string DWDate = ToDWDate(date).ToStdString();
    Document::AllocatorType& allocator = document.GetAllocator();
    Value value(kObjectType);
    Value valueString(kStringType);
    valueString.SetString(DWDate.data(), DWDate.size(), document.GetAllocator());
    value.AddMember(JSON_DATE, valueString, allocator); 
    value.AddMember(JSON_WORK, "", allocator);  
    Value &array = document[JSON_ARRAY];
    array.PushBack(value, allocator); 
    modified = true;
    return array[array.Size()-1];//todo valid ?  
    
//    static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
//    LOG(INFO) << "Type of member is " << kTypeNames[value.GetType()];
}

wxDateTime  DailyWorkParser::DWToDate(const std::string DWDate)
{
    wxDateTime date;
//	if (!date.ParseISODate(DWDate)) {
	if (!date.ParseFormat(DWDate, JSON_DATE_FORMAT_EXT, wxDateTime::Today())) {
        LOG(ERROR) << "Can't convert " << DWDate << "to date";
    }
    return date;
}
Value& DailyWorkParser::GetArray()
{
    //todo decommenter code ?
    //Value& value = document[JSON_ARRAY]; 
    //assert(value.IsArray());
    return document[JSON_ARRAY]; //value

}
Value& DailyWorkParser::GetItemFromDWItem(DWItemData* itemData)
{
    if(itemData != NULL) {
       return itemData->GetValue();
    } 
    else
        LOG(DEBUG) << "Pas de donné associée à l'item";
    return new Value(kNullType) ;       
}

int DailyWorkParser::DeleteItem(const Value& item)
{
    //todo finir
    return 0;
}

int DailyWorkParser::DeleteItemFromDWItem(DWItemData* itemData)
{
    return DeleteItem(GetItemFromDWItem(itemData));
}
