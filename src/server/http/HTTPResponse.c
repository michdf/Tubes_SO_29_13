#include "HTTPResponse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *response_constructor(int status, char *body){
    char *response;

    response = (char *)malloc(sizeof(char) * MAX_BUFFER_SIZE);

    if(response == NULL){
        perror("response_constructor");
        return NULL;
    }

    snprintf(response, sizeof(char) * MAX_BUFFER_SIZE, "HTTP/1.1 %d OK\nContent-Type: text/html\n\n", status);
    strcat(response, body);

    if(response == NULL){
        perror("response_constructor");
        return NULL;
    } else if(strlen(response) > MAX_BUFFER_SIZE){
        perror("response_constructor: response too large");
        return NULL;
    }

    return response;
}