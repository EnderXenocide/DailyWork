#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <string>
#include <functional>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <wx/treectrl.h>
#include <ctime>

#include "dwitemdata.h"

struct TDate {
    int annee; // 
    int mois; // 1-12
    int jour; //1-31
};

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
    int AddDateToTree(wxTreeCtrl* tree, TDate date, bool selectItem = false);
    int LoadDatesTree(wxTreeCtrl* tree);
    std::string GetWorkFromTree(wxTreeCtrl* tree);
    int UpdateWork(DWItemData* itemData, std::string text);
    TDate GetDateFromItem(Value& item);
    std::string GetWorkFromItem(Value& item);
    int SetWorkFromItem(Value& item, std::string text);
    wxString ToDWDate(TDate date);
    wxString ToTreeDate(TDate date);
    TDate DWToDate(std::string DWDate);
    int Save();
    DailyWorkParser& SetTreeWithHierarchy(bool hierarchy) {this->treeWithHierarchy = hierarchy;return *this; }
    bool IsTreeWithHierarchy() const {return treeWithHierarchy; }

private:
    const char* JSON_FILE = "dailywork.json";
    const char* JSON_DATE_FORMAT = "%4d-%02d-%02d";
    const char* TREE_DATE_FORMAT = "%02d/%02d/%4d";
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
    Value* AddValue(TDate date);
};

#endif // DAILYWORKPARSER_H
