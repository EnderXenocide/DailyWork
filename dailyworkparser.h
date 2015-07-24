#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <wx/string.h>

//typedef std::function<(wxString)> CallbackFunction;
typedef std::function<int(int)> CallbackFunction;

class DailyWorkParser
{
public:
    DailyWorkParser();
    ~DailyWorkParser();
    void ConnectCallback(CallbackFunction cb) 
    void Parse();
    
private:
    // The callback provided by the client via connectCallback().
    CallbackFunction m_cb;
};

#endif // DAILYWORKPARSER_H
