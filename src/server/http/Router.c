#include "Router.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Route * initRoute(char* key, void (*handler)(int, struct HTTPRequest*, char *params), int method) {
	struct Route * temp = (struct Route *) malloc(sizeof(struct Route));
	temp->key = key;
    temp->handlers = malloc(sizeof(struct RouteHandler));
    temp->handlers[0].handler = handler;
    temp->handlers[0].method = method;
    temp->handler_count = 1;
    temp->left = temp->right = NULL;
	return temp;
}

void addHandler(struct Route *route, void (*handler)(int, struct HTTPRequest*, char *params), int method) {
    route->handler_count++;
    route->handlers = realloc(route->handlers, sizeof(struct RouteHandler) * route->handler_count);
    route->handlers[route->handler_count - 1].handler = handler;
    route->handlers[route->handler_count - 1].method = method;
}

struct Route * addRoute(struct Route * root, char* key, void (*handler)(int, struct HTTPRequest*, char *params), int method) {
    if (root == NULL) {
        return initRoute(key, handler, method);
    }

    if (strcmp(key, root->key) == 0) {
        // Route exists, add new handler for different method
        addHandler(root, handler, method);
        return root;
    } else if (strcmp(key, root->key) > 0) {
        root->right = addRoute(root->right, key, handler, method);
    } else {
        root->left = addRoute(root->left, key, handler, method);
    }
    return root;
}

void* findHandler(struct Route* route, int method) {
    for (int i = 0; i < route->handler_count; i++) {
        if (route->handlers[i].method == method) {
            return route->handlers[i].handler;
        }
    }
    return NULL;
}

struct Route * search(struct Route * root, char* key) {
	if (root == NULL) {
        return NULL;
    }

    // Check if the route pattern contains a wildcard (e.g. /books/:id)
    char* wildcard = strchr(root->key, ':');
    if (wildcard != NULL) {
        // Compare only the static part of the route
        size_t static_length = wildcard - root->key;
        if (strncmp(key, root->key, static_length) == 0) {
            return root;
        }
    }

    // Normal exact matching
    if (strcmp(key, root->key) == 0) {
        return root;
    } else if (strcmp(key, root->key) > 0) {
        return search(root->right, key);
    } else {
        return search(root->left, key);
    }
}

// New function to extract parameters from URI
char* extract_params(const char* pattern, const char* uri) {
    char* wildcard = strchr(pattern, ':');
    if (wildcard == NULL) return NULL;

    size_t prefix_len = wildcard - pattern;
    return strdup(uri + prefix_len);
}
