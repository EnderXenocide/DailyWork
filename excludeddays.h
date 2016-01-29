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
    ~ExcludedDays();
    void Clear();    
    wxDateTime NextDay(wxDateTime date);
    wxDateTime PreviousDay(wxDateTime date);
    bool IsValid();
    bool IsWeekDayValid(wxDateTime day);    
    void DefaultValidate();
};

#endif // EXCLUDEDDAYS_H
