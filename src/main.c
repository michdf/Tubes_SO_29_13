#include "../config/server_config.h"
#include "server/Handler.h"
#include "server/Server.h"
#include "server/http/HTTPRequest.h"
#include "server/http/Router.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Add this global variable at the top of main.c
static struct Server *global_server = NULL;

// Add signal handler for SIGCHLD to prevent zombie processes
void handle_sigchld(int sig) {
  while (waitpid(-1, NULL, WNOHANG) > 0)
    ;
}

void handle_sigint(int sig) {
  printf("\nReceived SIGINT (Ctrl+C). Shutting down server...\n");

  if (global_server != NULL) {
    if (global_server->socket > 0) {
      close(global_server->socket);
    }
  }

  exit(0);
}

void launch(struct Server *server) {
  char buffer[MAX_BUFFER_SIZE];
  int address_length = sizeof(server->address);
  int new_socket;

  struct Route *route = initRoute("/", handleRoot, GET);
  addRoute(route, "/books", handleViewBooks, GET);
  addRoute(route, "/books", handleAddBook, POST);
  addRoute(route, "/books/:id", handleUpdateBook, PUT);

  handle_sigchld(SIGCHLD);
  signal(SIGINT, handle_sigint);

  while (true) {
    printf("WAITING FOR CONNECTION...\n");
    new_socket = accept(server->socket, (struct sockaddr *)&server->address,
                        (socklen_t *)&address_length);

    pid_t pid = fork();

    if (pid == 0) {
      // Child process
      close(server->socket); // Close listening socket in child

      read(new_socket, buffer, sizeof(buffer));
      printf("%s\n", buffer);
      struct HTTPRequest request = http_request_constructor(buffer);
      printf("REQUEST URI: %s\n", request.URI);

      struct Route *found = search(route, request.URI);
      if (found != NULL) {
        void (*handler)(int, struct HTTPRequest *, char *params) =
            findHandler(found, request.method);
        char *params = extract_params(request.URI, found->key);
        if (handler != NULL) {
          char *params = extract_params(found->key, request.URI);
          handler(new_socket, &request, params);
          free(params);
        } else {
          responseError(new_socket, 405, "Method Not Allowed");
        }
      } else {
        handleNotFound(new_socket, &request, NULL);
      }

      close(new_socket);
      exit(0);
    } else if (pid > 0) {
      // Parent process
      close(new_socket); // Close accepted socket in parent
      continue;
    } else {
      perror("fork");
      exit(1);
    }
  }
}

int main(void) {
  struct Server server =
      server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, WEBSERVER_PORT,
                         MAX_PROCESSES, launch);
  global_server = &server;
  server.launch(&server);
  return 0;
}