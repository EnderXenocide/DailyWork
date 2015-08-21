#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <string>
#include <functional>
#include <rapidjson/document.h>
#include <wx/treectrl.h>

typedef std::function<void(std::string)> CallbackMessageInfo;
//typedef std::function<int(int)> CallbackFunction;

class DailyWorkParser
{
public:
    DailyWorkParser();
    ~DailyWorkParser();
    void ConnectCallback(CallbackMessageInfo cb) ;
    int Parse();
    int LoadDatesTree(wxTreeCtrl* Tree, bool withHierarchy);
private:
    // The callback provided by the client via ConnectCallback().
    CallbackMessageInfo m_cbMessageInfo;
    rapidjson::Document document;
    int LoadDatesTreeHierarchy(wxTreeCtrl* Tree);
    int LoadDatesTreeSimple(wxTreeCtrl* Tree);
};

#endif // DAILYWORKPARSER_H
