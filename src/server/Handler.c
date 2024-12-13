#include "Handler.h"
#include "http/HTTPResponse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handleNotFound(int socket) {
  char *body = "<html><body><h1>404 Not Found</h1></body></html>";
  char *response = response_constructor(404, body);

  if (response == NULL) {
    perror("handleRoot: response_constructor");
    return;
  }

  write(socket, response, strlen(response));
  free(response);
  close(socket);
}

void handleRoot(int socket) {
  char *body = "<html><body><h1>I got Dejavu sans serif</h1></body></html>";
  char *response = response_constructor(200, body);

  if (response == NULL) {
    perror("handleRoot: response_constructor");
    return;
  }

  write(socket, response, strlen(response));
  free(response);
  close(socket);
}