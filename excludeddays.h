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
    wxDateTime NextDay(const wxDateTime& date);
    wxDateTime PreviousDay(const wxDateTime& date);
    bool IsValid();
    void DefaultValidate();
};

#endif // EXCLUDEDDAYS_H
