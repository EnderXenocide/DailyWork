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
public:
    CurrentDates()
    {
    }
    ~CurrentDates()
    {        
    }

    std::set<wxDateTime> dates;
    DateState today;
    DateState yesterday;  
    DateState tomorrow; 
    DateState prevAvailable;
    DateState nextAvailable;
};

#endif // CURRENTDATES_H
