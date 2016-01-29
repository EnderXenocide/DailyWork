#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <string>
#include <functional>
#include <set>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <wx/treectrl.h>

#include "dwitemdata.h"
#include "results.h"
#include "excludeddays.h"

#define JSON_VERSION_SCHEMA 3

#define JSON_FILE "dailywork.json"
#define JSON_DATE_FORMAT_EXT "%Y-%m-%d" // strptime()-like format string
#define JSON_DATE_FORMAT "%4d-%02d-%02d"
#define TREE_DATE_FORMAT "%02d/%02d/%4d" //todo format en/fr ?
#define JSON_ITEMS "dailyworks"
#define JSON_WORK "work"
#define JSON_DATE "date"
#define JSON_VERSION "version"
#define JSON_FAVORITES "favorites"
#define JSON_EXCLUDED_DAYS "excluded days"

using namespace rapidjson;

typedef std::function<void(wxString)> CallbackMessageInfo;
// typedef std::function<int(int)> CallbackFunction;

typedef std::multiset<Result, ResultComp> MapFind;

class DailyWorkParser
{
public:
    DailyWorkParser();
    ~DailyWorkParser();
    void ConnectCallback(CallbackMessageInfo cb);
    int Parse();
    void New();

    int UpdateWork(const wxDateTime& date, wxString text);
    wxDateTime GetDateFromItem(int itemIndex);
    wxString ToDWDate(const wxDateTime& date) const;
    wxString ToTreeDate(const wxDateTime& date) const;
    wxDateTime DWToDate(const wxString DWDate) const;

    int GetVersion() const { return version; }
    bool IsModified() const { return modified; }
    int SaveAs(wxString filename);
    int Save();
    
    void AddItem(const wxDateTime& date, wxString work="");
    SizeType CountItems(); 
    int DeleteItem(wxDateTime date);
    wxString GetWorkFromDate(const wxDateTime& date);
    
    bool AddToFavorites(wxString text);
    SizeType CountFavorites(); 
    int DeleteFavorite(wxString text);
    wxString GetFavorite(int itemIndex);
    bool IsInFavorites(wxString text);

    int GetExcludedDays(ExcludedDays &ed);
    int SetExcludedDays(ExcludedDays ed);

    int SearchInDates(const wxString text, MapFind &results);
    std::string GetLine(const std::string &str, std::size_t idx) const;
    std::size_t findStringIC(const std::string &strHaystack, const std::string &strNeedle) const;
private:
    int SetWorkFromItem(Value& item, wxString text);
    wxString GetWorkFromItem(const Value& item); 
    void TestAndUpdate();
    
    // The callback provided by the client via ConnectCallback().
    CallbackMessageInfo m_cbMessageInfo;
    Document document;
    int version;
    bool modified; // set if document was modified or not
};

#endif // DAILYWORKPARSER_H
