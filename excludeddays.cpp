#include "excludeddays.h"
#include "easylogging++.h"

ExcludedDays::ExcludedDays()
{
    Clear();
}

ExcludedDays::ExcludedDays(const ExcludedDays& ed)
{
    monday = ed.monday;
    tuesday = ed.tuesday;
    wednesday = ed.wednesday;
    thursday = ed.thursday;
    friday = ed.friday;
    saturday = ed.saturday;
    sunday = ed.sunday;
}

ExcludedDays::~ExcludedDays()
{
    
}

bool ExcludedDays::operator != (const ExcludedDays& ed) const
{
    return  monday != ed.monday ||  tuesday != ed.tuesday || wednesday != ed.wednesday || thursday != ed.thursday || friday != ed.friday || saturday != ed.saturday ||  sunday != ed.sunday;
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

wxDateTime ExcludedDays::NextDay(wxDateTime date)
{
    AutoValid();    
    do { 
        date = date + wxDateSpan::Day(); 
    } 
    while (!IsWeekDayValid(date));
    return date; 
}

wxDateTime ExcludedDays::PreviousDay(wxDateTime date)
{
    AutoValid();    
    do { 
        date = date - wxDateSpan::Day(); 
    } 
    while (!IsWeekDayValid(date));
    return date; 
}
bool ExcludedDays::IsValid()
{
	bool v = ! (monday && tuesday && wednesday && thursday && friday && saturday && sunday);
    LOG_IF(!v, ERROR) << "Excluded Days unvalid.";
    return v;
}

void ExcludedDays::DefaultValidate()
{
    LOG(INFO) << "Excluded Days : remove first day";
    monday = false;
}

bool ExcludedDays::IsWeekDayValid(wxDateTime day)
{ 
    //wxDateTime::WeekDay weekday
    switch (day.GetWeekDay())
    {
        case wxDateTime::WeekDay::Sun: return !sunday;
        case wxDateTime::WeekDay::Mon: return !monday;    
        case wxDateTime::WeekDay::Tue: return !tuesday;
        case wxDateTime::WeekDay::Wed: return !wednesday;    
        case wxDateTime::WeekDay::Thu: return !thursday;
        case wxDateTime::WeekDay::Fri: return !friday;    
        case wxDateTime::WeekDay::Sat: return !saturday;    
        default: return false;
    }
}

void ExcludedDays::AutoValid()
{
    if (!IsValid()) {
        DefaultValidate();
    }
}
