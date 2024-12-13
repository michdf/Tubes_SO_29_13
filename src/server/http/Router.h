#ifndef Route_h
#define Route_h

#include "HTTPRequest.h"

struct RouteHandler {
	void (*handler)(int, struct HTTPRequest*, char *params);
	int method;
};

struct Route {
	char* key;
	struct RouteHandler *handlers;
	int handler_count;
	struct Route *left, *right;
};

struct Route * initRoute(char* key, void (*handler)(int, struct HTTPRequest*, char *params), int method);

struct Route * addRoute(struct Route * root, char* key, void (*handler)(int, struct HTTPRequest*, char *params), int method);

struct Route * search(struct Route * root, char * key);

struct Route * findRoute(struct Route* route, int method);

void* findHandler(struct Route* route, int method);

void show_routes(struct Route * root );

char * extract_params(const char* pattern, const char* uri);

#endif