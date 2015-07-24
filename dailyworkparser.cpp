#include "DailyWorkParser.h"
#include <iostream>

#include "rapidjson/document.h"

DailyWorkParser::DailyWorkParser()
{    
}

DailyWorkParser::~DailyWorkParser()
{
}

void DailyWorkParser::ConnectCallback(CallbackFunction cb)  
{ 
    m_cb = cb; 
}


void DailyWorkParser::Parse()
{    
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document d;
    d.Parse(json);
    rapidjson::Value& s = d["project"];
     m_cb(s.GetString());

    return ;
   
   /*
   char *source = "{\"stars\":10}0"; // or read file, whatever
     // do not forget terminate source string with 0
    char *endptr; 
    JsonValue value;
    JsonAllocator allocator;
    int status = jsonParse(source, &endptr, &value, allocator);
    if (status != JSON_OK) {
        m_cb(std::string("%s at %zd\n")+jsonStrError(status));
        //fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - source);
        //exit(EXIT_FAILURE);
    }
    else
        m_cb("ok");
         * */
}
