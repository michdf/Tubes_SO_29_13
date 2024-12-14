#ifndef HTTPRequest_h
#define HTTPRequest_h
#include "HTTPInfo.h"

struct HTTPRequest
{
    int method;
    char *URI;
    char *body;
    float HTTPVersion;
};

struct HTTPRequest http_request_constructor(char *request_string);

#endif