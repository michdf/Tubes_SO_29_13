#ifndef Route_h
#define Route_h

struct Route {
	char* key;
	void (*handler)(int);

	struct Route *left, *right;
};

struct Route * initRoute(char* key, void (*handler)(int));

struct Route * addRoute(struct Route * root, char* key, void (*handler)(int));

struct Route * search(struct Route * root, char * key);

void show_routes(struct Route * root );

#endif