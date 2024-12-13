#include "HTTPRequest.h"
#include <stdlib.h>
#include <string.h>

int method_select(char *method){
    if(strcmp(method, "GET") == 0){
        return GET;
    } else if(strcmp(method, "POST") == 0){
        return POST;
    } else if(strcmp(method, "PUT") == 0){
        return PUT;
    } else if(strcmp(method, "HEAD") == 0){
        return HEAD;
    } else if(strcmp(method, "PATCH") == 0){
        return PATCH;
    } else if(strcmp(method, "DELETE") == 0){
        return DELETE;
    } else if(strcmp(method, "CONNECT") == 0){
        return CONNECT;
    } else if(strcmp(method, "OPTIONS") == 0){
        return OPTIONS;
    } else if(strcmp(method, "TRACE") == 0){
        return TRACE;
    }
}

struct HTTPRequest http_request_constructor(char *request_string){
    struct HTTPRequest request;
    for(int line = 1; line <= strlen(request_string) - 1; line++){
        if(request_string[line] == '\n' && request_string[line + 1] == '\n'){
            request_string[line + 1] = '|';
        }
    }

    char *request_line = strtok(request_string, "\n");
    char *header_fields = strtok(NULL, "|");
    char *body = strtok(NULL, "|");

    char *method = strtok(request_line, " ");
    request.method = method_select(method);
    char *URI = strtok(NULL, " ");
    request.URI = URI;
    char *HTTPVersion = strtok(NULL, " ");
    HTTPVersion = strtok(HTTPVersion, "/");
    HTTPVersion = strtok(NULL, "/");
    request.HTTPVersion = atof(HTTPVersion);

    return request;
}