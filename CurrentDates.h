#ifndef CURRENTDATES_H
#define CURRENTDATES_H

#include <wx/string.h>
#include <set>
#include <algorithm>

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
    void clear() { Init(); dates.clear(); };
private :
    wxString ToString(wxDateTime date) 
    {
        if (date.IsValid())
            return date.Format(_("%A, %B %d %Y"));
        else
            return _("unknow");
    };      
};

#endif // CURRENTDATES_H
