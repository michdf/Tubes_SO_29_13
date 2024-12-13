#include "Router.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Route * initRoute(char* key, void (*handler)(int, struct HTTPRequest*)) {
	struct Route * temp = (struct Route *) malloc(sizeof(struct Route));

	temp->key = key;
	temp->handler = handler;

	temp->left = temp->right = NULL;
	return temp;
}

void show_routes(struct Route* root)
{

    if (root != NULL) {
        show_routes(root->left);
        printf("%s \n", root->key);
        show_routes(root->right);
    }
}

struct Route * addRoute(struct Route * root, char* key, void (*handler)(int, struct HTTPRequest*)) {
	if (root == NULL) {
		return initRoute(key, handler);
	}

	if (strcmp(key, root->key) == 0) {
		printf("============ WARNING ============\n");
		printf("A Route For \"%s\" Already Exists\n", key);
	}else if (strcmp(key, root->key) > 0) {
		root->right = addRoute(root->right, key, handler);
	}else {
		root->left = addRoute(root->left, key, handler);
	}

    return NULL;
}

struct Route * search(struct Route * root, char* key) {
	if (root == NULL) {
		return NULL;
	} 

	if (strcmp(key, root->key) == 0){
		return root;
	}else if (strcmp(key, root->key) > 0) {
		return search(root->right, key);
	}else if (strcmp(key, root->key) < 0) {
		return search(root->left, key);
	}  

    return NULL;
}
