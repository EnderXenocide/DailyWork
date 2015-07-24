#include "DailyWorkParser.h"
#include "gason.h"
#include "stdio.h"

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
    char *source = "{\"project\":\"rapidjson\",\"stars\":10}"; // or read file, whatever
    // do not forget terminate source string with 0
    char *endptr = 0; /*
    JsonValue value;
    JsonAllocator allocator;
    int status = jsonParse(source, &endptr, &value, allocator);
    if (status != JSON_OK) {
        fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - source);
        exit(EXIT_FAILURE);
    }*/
    //m_cb("ok");
    m_cb(5);
}
