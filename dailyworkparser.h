#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <string>
#include <functional>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <wx/treectrl.h>
#include <wx/datetime.h>

#include "dwitemdata.h"

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
    int AddDateToTree(wxTreeCtrl* tree, wxDateTime date, bool selectItem = false);
    int LoadDatesTree(wxTreeCtrl* tree);
    std::string GetWorkFromTree(wxTreeCtrl* tree);
    int UpdateWork(DWItemData* itemData, std::string text);
    wxDateTime GetDateFromItem(Value& item);
    std::string GetWorkFromItem(Value& item);
    int SetWorkFromItem(Value& item, std::string text);
    wxString ToDWDate(wxDateTime date);
    wxString ToTreeDate(wxDateTime date);
    wxDateTime DWToDate(std::string DWDate);
    int Save();
    DailyWorkParser& SetTreeWithHierarchy(bool hierarchy) {this->treeWithHierarchy = hierarchy;return *this; }
    bool IsTreeWithHierarchy() const {return treeWithHierarchy; }

private:
    const char* JSON_FILE = "dailywork.json";
    const char* JSON_DATE_FORMAT = "%4d-%2d-%2d";
    const char* TREE_DATE_FORMAT = "%2d/%2d/%d";
    const char* JSON_WORK = "work";
    const char* JSON_DATE = "date";
    const char* JSON_ARRAY = "dailywork";

    // The callback provided by the client via ConnectCallback().
    CallbackMessageInfo m_cbMessageInfo;
    Document document;
    bool treeWithHierarchy;
    int LoadDatesTreeHierarchy(wxTreeCtrl* tree, wxTreeItemId rootID, Value& dataArray);
    int LoadDatesTreeSimple(wxTreeCtrl* tree, wxTreeItemId rootID, Value& dataArray);
    wxTreeItemId AddItem(wxTreeCtrl* tree, wxTreeItemId parent, wxString text);
    Value* AddValue(wxDateTime date);
};

#endif // DAILYWORKPARSER_H
