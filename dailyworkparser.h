#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <string>
#include <functional>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <wx/treectrl.h>

#include "dwitemdata.h"

#define JSON_FILE "dailywork.json"
#define JSON_DATE_FORMAT_EXT "%Y-%m-%d" // strptime()-like format string
#define JSON_DATE_FORMAT "%4d-%02d-%02d"
#define TREE_DATE_FORMAT "%02d/%02d/%4d"
#define JSON_ARRAY "dailywork"
#define JSON_WORK "work"
#define JSON_DATE "date"
#define JSON_VERSION "version"

using namespace rapidjson;

typedef std::function<void(std::string)> CallbackMessageInfo;
// typedef std::function<int(int)> CallbackFunction;

class DailyWorkParser
{
public:
    DailyWorkParser();
    ~DailyWorkParser();
    void ConnectCallback(CallbackMessageInfo cb);
    int Parse();
    int DeleteItemFromDWItem(DWItemData* itemData);
    int DeleteItem(const Value& item);
    DWItemData* AddDate(wxDateTime& date); // todo wxTreeCtrl& tree instead
    int UpdateWork(DWItemData* itemData, std::string text);
    wxDateTime GetDateFromItem(const Value& item);
    std::string GetWorkFromItem(const Value& item); //todo mettre en private
    std::string GetWorkFromDWItem(DWItemData* itemData);
    int SetWorkFromItem(Value& item, std::string text);
    wxString ToDWDate(const wxDateTime& date) const;
    wxString ToTreeDate(const wxDateTime& date) const;
    wxDateTime DWToDate(const std::string DWDate);
    int Save();
    int SaveAs(wxString filename);
    int GetVersion() const { return version; }
    bool IsModified() const { return modified; }
    Value& GetArray();
    //todo delete date 
    
private:
    //    static constexpr const char* JSON_FILE = "dailywork.json";
    //    static constexpr const char* JSON_DATE_FORMAT_EXT = "%Y-%m-%d"; //strptime()-like format string
    //    static constexpr const char* JSON_DATE_FORMAT = "%4d-%02d-%02d";
    //    static constexpr const char* TREE_DATE_FORMAT = "%02d/%02d/%4d";
    //    static constexpr const char* JSON_WORK = "work";
    //    static constexpr const char* JSON_DATE = "date";
    //    static constexpr const char* JSON_ARRAY = "dailywork";

    // The callback provided by the client via ConnectCallback().
    CallbackMessageInfo m_cbMessageInfo;
    Document document;
    Value& AddValue(wxDateTime& date);
    Value& GetItemFromDWItem(DWItemData* itemData); //todo mettre en private
    int version;
    bool modified; // set if document was modified
};

#endif // DAILYWORKPARSER_H
