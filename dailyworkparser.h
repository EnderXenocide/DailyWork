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
    DWItemData* AddDate(wxDateTime& date); 
    int UpdateWork(DWItemData* itemData, std::string text);
    wxDateTime GetDateFromItem(int itemIndex);
    std::string GetWorkFromDWItem(DWItemData* itemData);
    wxString ToDWDate(const wxDateTime& date) const;
    wxString ToTreeDate(const wxDateTime& date) const;
    wxDateTime DWToDate(const std::string DWDate);
    SizeType Count(); 
    //todo delete date 

    int selectItemFromDWItem(DWItemData* itemData);   
    
    std::string getSelectedWork();
    int setSelectedWork(std::string work);
    wxDateTime getSelectedDate();
    int setSelectedDate(const wxDateTime& date);
    int GetVersion() const { return version; }
    bool IsModified() const { return modified; }
    int SaveAs(wxString filename);
    int Save();
    bool IsSelectedOk();
    DWItemData* NewDWItemData(int itemIndex);
private:
    int SetWorkFromItem(Value& item, std::string text);
    std::string GetWorkFromItem(const Value& item); 
    int DeleteItem(const Value& item);
    Value& AddItem(wxDateTime& date, std::string work);

    // The callback provided by the client via ConnectCallback().
    CallbackMessageInfo m_cbMessageInfo;
    Document document;
    int version;
    bool modified; // set if document was modified or not
    Value selected;
};

#endif // DAILYWORKPARSER_H
