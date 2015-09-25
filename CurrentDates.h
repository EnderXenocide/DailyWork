#ifndef CURRENTDATES_H
#define CURRENTDATES_H

#include <wx/wx.h>
#include <set>
#include <algorithm>

struct  DateState {
    DateState() { }
    wxDateTime date;   
    bool exist = false;
    wxTreeItemId itemId;
    wxString ToFullString() {  return date.Format("%A %d %B %Y"); };  
    bool IsValid() { return date.IsValid(); };  
    void Set(wxDateTime date, bool exist) {this->date = date; this->exist = exist; };
    bool operator== (const DateState& ds)
    {
       return this->date.IsSameDate(ds.date);
    }
    bool operator!= (const DateState& ds)
    {
       return ! this->date.IsSameDate(ds.date);
    }   
};

class CurrentDates
{
public :
    CurrentDates()
    {
        Init();
    }
    ~CurrentDates()
    {        
    }
    std::set<wxDateTime> dates; // stock les dates de la plus vieille à la plus recente  (l'inverse du tree) 
    wxDateTime today;
    wxDateTime yesterday;  
    wxDateTime tomorrow; 
    wxDateTime prevAvailable;
    wxDateTime nextAvailable;
    wxString TodayToString() {  return ToString(today); };  
    wxString TomorrowToString() {  return ToString(tomorrow); };  
    wxString YesterdayToString() {  return ToString(yesterday); };  
    wxString PrevAvailableToString() {  return ToString(prevAvailable); };  
    wxString NextAvailableToString() {  return ToString(nextAvailable); };      
    void Init() {  today = (time_t)-1; yesterday = today; tomorrow = today; prevAvailable = today; nextAvailable = today;};
private :
    wxString ToString(wxDateTime date) 
    {
        if (date.IsValid())
            return date.Format("%A %d %B %Y"); 
        else
            return _("unknow");
    };      
};

#endif // CURRENTDATES_H
