#ifndef Handler_h
#define Handler_h
#include "http/HTTPRequest.h"

void responseError(int socket, int code, const char *message);
void handleNotFound(int socket, struct HTTPRequest* request, char *params);
void handleRoot(int socket, struct HTTPRequest* request, char *params);
void handleViewBooks(int socket, struct HTTPRequest* request, char *params);
void handleAddBook(int socket, struct HTTPRequest* request, char *params);
void handleUpdateBook(int socket, struct HTTPRequest* request, char *params);

#endif