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
#define JSON_DATE_FORMAT_EXT "%Y-%m-%d" //strptime()-like format string
#define JSON_DATE_FORMAT "%4d-%02d-%02d"
#define TREE_DATE_FORMAT "%02d/%02d/%4d"
#define JSON_WORK "work"
#define JSON_DATE "date"
#define JSON_ARRAY "dailywork"

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
    int AddDateToTree(wxTreeCtrl* tree, wxDateTime& date, bool selectItem = false); //todo wxTreeCtrl& tree instead
    int LoadDatesTree(wxTreeCtrl* tree);
    int UpdateWork(DWItemData* itemData, std::string text);
    std::string GetWorkFromTree(const wxTreeCtrl* tree)  ;
    wxDateTime GetDateFromItem(const Value& item) ;
    std::string GetWorkFromItem(const Value& item) ;
    int SetWorkFromItem(Value& item, std::string text);
    wxString ToDWDate(const wxDateTime& date) const ;
    wxString ToTreeDate(const wxDateTime& date) const ;
    wxDateTime DWToDate(const std::string DWDate);
    int Save();
    DailyWorkParser& SetHierarchicalTree(bool hierarchy) {this->treeWithHierarchy = hierarchy;return *this; }
    bool IsHierarchicalTree() const {return treeWithHierarchy; }

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
    bool treeWithHierarchy;
    int LoadDatesTreeHierarchy(wxTreeCtrl* tree, wxTreeItemId rootID, const Value& dataArray);
    int LoadDatesTreeSimple(wxTreeCtrl* tree, wxTreeItemId rootID, const Value& dataArray);
    wxTreeItemId AddItem(wxTreeCtrl* tree, wxTreeItemId parent, wxString text);
    Value& AddValue(wxDateTime& date);
};

#endif // DAILYWORKPARSER_H
