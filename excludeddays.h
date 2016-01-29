#ifndef EXCLUDEDDAYS_H
#define EXCLUDEDDAYS_H

#include <wx/string.h>
#include <wx/datetime.h>

//enum WeekDays {monday,tuesday,wednesday,thursday,friday, saturday,sunday};

class ExcludedDays
{
public:
    bool monday,tuesday,wednesday,thursday,friday, saturday,sunday;
    ExcludedDays();
    ExcludedDays(const ExcludedDays& ed);
    ~ExcludedDays();
    bool operator != (const ExcludedDays& ed) const;
    void Clear();    
    wxDateTime NextDay(wxDateTime date);
    wxDateTime PreviousDay(wxDateTime date);
    bool IsWeekDayValid(wxDateTime day);    
    bool IsValid();
    void DefaultValidate();
    void AutoValid();
protected:
    
};

#endif // EXCLUDEDDAYS_H
