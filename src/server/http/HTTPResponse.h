#ifndef HTTPResponse_h
#define HTTPResponse_h

#include "HTTPInfo.h"
#include "../../../config/server_config.h"

char *response_constructor(int status, char *body);

#endif