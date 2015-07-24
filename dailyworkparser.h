#ifndef DAILYWORKPARSER_H
#define DAILYWORKPARSER_H

#include <string>
#include <functional>

typedef std::function<void(std::string)> CallbackFunction;
//typedef std::function<int(int)> CallbackFunction;

class DailyWorkParser
{
public:
    DailyWorkParser();
    ~DailyWorkParser();
    void ConnectCallback(CallbackFunction cb) ;
    void Parse();
    
private:
    // The callback provided by the client via ConnectCallback().
    CallbackFunction m_cb;
};

#endif // DAILYWORKPARSER_H
