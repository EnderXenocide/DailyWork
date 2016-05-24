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
    jsonFile = JSON_FILE;
}

DailyWorkParser::~DailyWorkParser()
{
}

void DailyWorkParser::StatusBarMessageCallback(CallbackMessageInfo cb)
{
    m_cbMessageInfo = cb;
}

void DailyWorkParser::DialogMessageCallback(CallbackMessageInfo cb)
{
    m_cbDialog = cb;
}


int DailyWorkParser::Parse()
{
    //    const char* json = "{\"dailywork\":[ {\"date\":\"2015-07-24\",\"work\":\"rien\"},"
    //                               "{\"date\":\"2015-07-23\",\"work\":\"nothing\"},"
    //                               "{\"date\":\"2015-07-22\",\"work\":\"niet\"} ] }";
    modified = false;
    int retour = 0;

    LOG(INFO) << "Parse file " << jsonFile;
    std::ifstream ifs(jsonFile);
    if(ifs) {
        std::stringstream ss;
        ss << ifs.rdbuf();
        ifs.close();

        if(document.Parse<0>(ss.str().c_str()).HasParseError()) {
            ParseErrorCode parseErrorCode = document.GetParseError();
            wxString strErreur = wxString::Format(_("Error reading file (offset %u): %s\n"),
                                                     (unsigned)document.GetErrorOffset(),
                                                     GetParseError_En(parseErrorCode));
            LOG(ERROR) << strErreur;                                         
            m_cbMessageInfo(strErreur);
            retour = -1;
        }
    }
    else {
        LOG(ERROR) << _("File not found");
        m_cbMessageInfo(_("File not found"));
        retour = -1;
    }

    TestAndUpdate();
    if (modified) {
       wxString msg = wxString::Format(_("File updated to version %d"),JSON_VERSION_SCHEMA);
       LOG(INFO) << msg;
       m_cbDialog(msg); 
    }
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
        LOG(DEBUG) << "Date nt found :" << sdate;
    }
    LOG(DEBUG) << "Update impossible";
    return -1;
}

int DailyWorkParser::Save()
{    
    return SaveAs(jsonFile);
}

int DailyWorkParser::SaveAs(wxString filename)
{
    wxString msg = "Save";
    if (filename != jsonFile)
        msg += " as "+filename;
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
        LOG(DEBUG) << "Date not found :" << sdate;
    } 
    else {
        LOG(DEBUG) << "Invalid Date";        
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
    LOG(DEBUG ) << "Edit modified : " << utf8;
    modified = true;
    return 0;
}

wxDateTime DailyWorkParser::DWToDate(const wxString DWDate) const
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
                LOG(INFO) << "Delete date " << sdate;
                modified = true;               
                return 0;   
            }        
        }   
    }
    return 1; //non supprimé
}

void DailyWorkParser::AddItem(const wxDateTime& date, wxString work)
{  
    std::string DWDate = ToDWDate(date).ToStdString();
    std::string utf8Work = work.ToUTF8().data();
    LOG(INFO) << "Add Date " << DWDate;
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
/*
 * Doublon avec TestAndUpdate() ?
 * */
void DailyWorkParser::New()
{
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();
    Value items(kArrayType);
    document.AddMember(JSON_ITEMS, items, allocator);
    document.AddMember(JSON_FAVORITES, items, allocator);
    document.AddMember(JSON_EXCLUDED_DAYS, items, allocator);  
    Value version(JSON_VERSION_SCHEMA);
    document.AddMember(JSON_VERSION, version, allocator);
    modified = true;
}

void DailyWorkParser::TestAndUpdate()
{
    Document::AllocatorType& allocator = document.GetAllocator();
    if (document.IsNull())
        document.SetObject();
        
    if (!document.HasMember(JSON_ITEMS)) {
        Value items(kArrayType);
        document.AddMember(JSON_ITEMS, items, allocator);  
        modified = true; 
    } 
 
    if (!document.HasMember(JSON_VERSION)) {
        Value items(JSON_VERSION_SCHEMA);
        document.AddMember(JSON_VERSION, items, allocator);  
        modified = true; 
    }  
    
    version = document[JSON_VERSION].GetInt();
    if (version<JSON_VERSION_SCHEMA) {
       document[JSON_VERSION].SetInt(JSON_VERSION_SCHEMA);  //passage à la version n° JSON_VERSION_SCHEMA
        modified = true;          
    }                

    if (!document.HasMember(JSON_FAVORITES)) {
        Value items(kArrayType);
        document.AddMember(JSON_FAVORITES, items, allocator);  
        modified = true;          
    }                
   
    if (!document.HasMember(JSON_EXCLUDED_DAYS)) {
        Value items(kArrayType);
        document.AddMember(JSON_EXCLUDED_DAYS, items, allocator);  
        modified = true; 
    }  
}

bool DailyWorkParser::AddToFavorites(wxString text)
{
    std::string utf8Text = text.ToUTF8().data();
    if (IsInFavorites(text)) {
         LOG(INFO) << "Can't add existing favorite <" << utf8Text <<">";
        return false;
    }
    LOG(INFO) << "Add favorite <" << utf8Text <<">";
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
            LOG(INFO) << "Delete favorite <" << utf8Text <<">";
            modified = true;               
            return 0;   
        }        
    } 
    LOG(DEBUG) << "Favorite <" << utf8Text <<"> not found";
    return  -1; 
}

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


int DailyWorkParser::SearchInDates(const wxString text, MapFind &results)
{
    std::string utf8Text = text.ToUTF8().data();
    Value &array = document[JSON_ITEMS];    
    for (Value::ConstValueIterator itr = array.Begin(); itr != array.End(); itr++) {
         Value::ConstMemberIterator mitrString = itr->FindMember(JSON_WORK);
         if ( mitrString != itr->MemberEnd() ) {
            std::string  str = mitrString->value.GetString();
            //std::size_t idx = str.find(utf8Text); //case sensitive
            std::size_t idx = findStringIC(str, utf8Text); 
             if(idx != std::string::npos){
                Value::ConstMemberIterator mitrDate = itr->FindMember(JSON_DATE);
                if ( mitrDate != itr->MemberEnd() ) {
                    wxDateTime date = DWToDate(mitrDate->value.GetString());
                    std::string line = GetLine(str, idx);
                    Result result(date, wxString::FromUTF8(wxString(line)));
                    results.insert(result);
                }
            }            
//            for(std::size_t pos = 0;pos != std::string::npos && pos < str.size();++pos){
//                std::size_t idx = str.find(utf8Text,pos);
//                if(pos != std::string::npos){
//                    std::cout << sub_str << " trouvé dans " << str
//                        << " à la position " << idx << std::endl;
//                }
//                pos = idx + 1;
//            }            
         }
    } 
    return results.size();
}

/// Try to find in the Haystack the Needle - ignore case
// http://stackoverflow.com/users/195527/cc
std::size_t DailyWorkParser::findStringIC(const std::string &strHaystack, const std::string &strNeedle) const
{
    std::string strHaystackUC = strHaystack;    
    for (auto & c: strHaystackUC) c = toupper(c);
    std::string strNeedleUC = strNeedle;
    for (auto & c: strNeedleUC) c = toupper(c);
    return strHaystackUC.find(strNeedleUC); //case sensitive
}

std::string DailyWorkParser::GetLine(const std::string &str, std::size_t idx) const
{
    //std::string upperstr = str.
    std::size_t idxFirstCR = str.find_last_of('\n', idx); //cherche un retour à la ligne avant idx
    if (idxFirstCR != std::string::npos) { // un retour à la ligne trouvé
        std::size_t len;
        std::size_t pos;

        std::size_t idxLastCR = str.find_first_of('\n', idx+1); // cherche un retour à la ligne après idx
       if (idxFirstCR<idx)  // retour à la ligne trouvé avant idx
            pos = idxFirstCR+1; 
        else 
            pos = 0; //idx sest sur la première igne  return (it != strHaystack.end() );
        if ( idxLastCR != std::string::npos) // retour à la ligne trouvé après idx
            len = idxLastCR-pos;  
        else
            len = std::string::npos;   // recupère reste de la chaine                 
        return str.substr(pos, len);
    }
    else
        return str; // renvoie str qui est sur une ligne
}

int DailyWorkParser::GetExcludedDays(ExcludedDays &ed)
{
    Value &array = document[JSON_EXCLUDED_DAYS];
    ed.Clear();
    LOG(INFO) << "Get Excluded Days : ";
    for (Value::ConstValueIterator itr = array.Begin(); itr != array.End(); itr++) {
        std::string day = itr->GetString();
        if (day=="monday") ed.monday = true;
        else if (day=="tuesday") ed.tuesday = true;
        else if (day=="wednesday") ed.wednesday = true;
        else if (day=="thursday") ed.thursday = true;
        else if (day=="saturday") ed.saturday = true;
        else if (day=="sunday") ed.sunday = true;
        LOG(INFO) << day;
    } 
    if (!ed.IsValid()) {
        ed.DefaultValidate();
        return 0; 
    }
    return  -1; 
}

int DailyWorkParser::SetExcludedDays(ExcludedDays ed)
{
    Value &array = document[JSON_EXCLUDED_DAYS];
    array.Clear();
    ed.AutoValid();
    std::string listeExcludeDays;
    Document::AllocatorType& allocator = document.GetAllocator();
    Value valueString(kStringType);
    if (ed.monday) {
        std::string text = "monday";
        valueString.SetString(text.c_str(), text.size(), allocator);
        array.PushBack(valueString, allocator);
        modified = true;
        listeExcludeDays = text+" ";
    }
    if (ed.tuesday) {
        std::string text = "tuesday";
        valueString.SetString(text.c_str(), text.size(), allocator);
        array.PushBack(valueString, allocator);
        modified = true;
        listeExcludeDays = listeExcludeDays+text+" ";
    };
    if (ed.wednesday) {
        std::string text = "wednesday";
        valueString.SetString(text.c_str(), text.size(), allocator);
        array.PushBack(valueString, allocator);
        modified = true;
        listeExcludeDays = listeExcludeDays+text+" ";
    };
    if (ed.thursday) {
        std::string text = "thursday";
        valueString.SetString(text.c_str(), text.size(), allocator);
        array.PushBack(valueString, allocator);
        modified = true;
        listeExcludeDays = listeExcludeDays+text+" ";
    };
    if (ed.saturday) {
        std::string text = "saturday";
        valueString.SetString(text.c_str(), text.size(), allocator);
        array.PushBack(valueString, allocator);
        modified = true;
        listeExcludeDays = listeExcludeDays+text+" ";
    };
    if (ed.sunday) {
        std::string text = "sunday";
        valueString.SetString(text.c_str(), text.size(), allocator);
        array.PushBack(valueString, allocator);
        modified = true;
        listeExcludeDays = listeExcludeDays+text+" ";
    LOG(INFO) << "Set Excluded Days : "<< listeExcludeDays;
    };
    
    return  -1;        
}
/*
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
*/
