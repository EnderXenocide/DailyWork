#include "excludeddays.h"
#include "easylogging++.h"

ExcludedDays::ExcludedDays()
{
    Clear();
}

ExcludedDays::~ExcludedDays()
{
    
}

void ExcludedDays::Clear()
{
    monday = false;
    tuesday = false;
    wednesday = false;
    thursday = false;
    friday = false;
    saturday = false;
    sunday = false;
}

wxDateTime ExcludedDays::NextDay(const wxDateTime& date)
{
    return date + wxDateSpan::Day(); 
}

wxDateTime ExcludedDays::PreviousDay(const wxDateTime& date)
{
    return date - wxDateSpan::Day(); 
}
bool ExcludedDays::IsValid()
{
	bool v = ! (monday && tuesday && wednesday && thursday && friday && saturday && sunday);
    LOG_IF(!v, ERROR) << "Excluded Days unvalid.";
    return v;
}

void ExcludedDays::DefaultValidate()
{
    LOG(INFO) << "Excluded Days. Remove first day";
    monday = false;
}