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
#define TREE_DATE_FORMAT "%02d/%02d/%4d" //todo format en/fr ?
#define JSON_ITEMS "dailyworks"
#define JSON_WORK "work"
#define JSON_DATE "date"
#define JSON_VERSION "version"
#define JSON_FAVORITES "favorites"


using namespace rapidjson;

typedef std::function<void(wxString)> CallbackMessageInfo;
// typedef std::function<int(int)> CallbackFunction;

class DailyWorkParser
{
public:
    DailyWorkParser();
    ~DailyWorkParser();
    void ConnectCallback(CallbackMessageInfo cb);
    int Parse();
    void New();
    //DWItemData* AddDate(wxDateTime& date); 
    int UpdateWork(const wxDateTime& date, std::string text);
    wxDateTime GetDateFromItem(int itemIndex);
    wxString ToDWDate(const wxDateTime& date) const;
    wxString ToTreeDate(const wxDateTime& date) const;
    wxDateTime DWToDate(const wxString DWDate);
    //todo delete date 

   // int selectItemFromDate(const wxDateTime& date);   
    
    wxString getSelectedWork();
    int setSelectedWork(wxString work);
    wxDateTime getSelectedDate();
    int setSelectedDate(const wxDateTime& date);
    int GetVersion() const { return version; }
    bool IsModified() const { return modified; }
    int SaveAs(wxString filename);
    int Save();
    bool IsSelectedOk();
    
    void AddItem(wxDateTime& date, wxString work="");
    SizeType CountItems(); 
    int DeleteItem(wxDateTime date);
    wxString GetWorkFromDate(const wxDateTime& date);
    
    int AddToFavorites(wxString text);
    SizeType CountFavorites(); 
    int DeleteFavorite(wxString text);
    wxString GetFavorite(int itemIndex);
    
private:
    int SetWorkFromItem(Value& item, wxString text);
    wxString GetWorkFromItem(const Value& item); 
    void TestAndUpdate();
    //bool FindItem(const wxDateTime& date, Value& item); //todo fonction ne marche pas, bouge les objets
    //Value& FindItem(const wxDateTime& date);

    // The callback provided by the client via ConnectCallback().
    CallbackMessageInfo m_cbMessageInfo;
    Document document;
    int version;
    bool modified; // set if document was modified or not
    Value selected;
};

#endif // DAILYWORKPARSER_H
