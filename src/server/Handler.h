#ifndef Handler_h
#define Handler_h
#include "http/HTTPRequest.h"

void handleNotFound(int socket, struct HTTPRequest* request);
void handleRoot(int socket, struct HTTPRequest* request);
void handleAddBook(int socket, struct HTTPRequest* request);

#endif