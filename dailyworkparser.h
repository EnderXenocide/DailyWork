#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <string>
#include <functional>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <wx/treectrl.h>

#include "dwitemdata.h"

typedef std::function<void(std::string)> CallbackMessageInfo;
//typedef std::function<int(int)> CallbackFunction;

class DailyWorkParser
{
public:
    DailyWorkParser();
    ~DailyWorkParser();
    void ConnectCallback(CallbackMessageInfo cb);
    int Parse();
    int LoadDatesTree(wxTreeCtrl* tree, bool withHierarchy);
    std::string GetWorkFromTree(wxTreeCtrl* tree);
    int UpdateWork(DWItemData* itemData, std::string text);
    int Save();

private:
    // The callback provided by the client via ConnectCallback().
    CallbackMessageInfo m_cbMessageInfo;
    rapidjson::Document document;
    const char* JSON_FILE = "dailywork.json";
    int LoadDatesTreeHierarchy(wxTreeCtrl* tree, wxTreeItemId rootID, rapidjson::Value& data);
    int LoadDatesTreeSimple(wxTreeCtrl* tree, wxTreeItemId rootID, rapidjson::Value& data);
};

#endif // DAILYWORKPARSER_H
