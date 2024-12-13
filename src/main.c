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
#include <unistd.h>
#include <sys/wait.h>

// Add signal handler for SIGCHLD to prevent zombie processes
void handle_sigchld(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void launch(struct Server *server) {
  char buffer[MAX_BUFFER_SIZE];
  int address_length = sizeof(server->address);
  int new_socket;

  struct Route *route = initRoute("/", handleRoot);

  handle_sigchld(SIGCHLD);

  while (true) {
    printf("WAITING FOR CONNECTION...\n");
    new_socket = accept(server->socket, (struct sockaddr *)&server->address,
                        (socklen_t *)&address_length);

    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        close(server->socket);  // Close listening socket in child
        
        read(new_socket, buffer, MAX_BUFFER_SIZE);
        struct HTTPRequest request = http_request_constructor(buffer);
        printf("REQUEST URI: %s\n", request.URI);

        struct Route *found = search(route, request.URI);
        if (found != NULL) {
            found->handler(new_socket);
        } else {
            handleNotFound(new_socket);
        }
        
        close(new_socket);
        exit(0);
    } else if (pid > 0) {
        // Parent process
        close(new_socket);  // Close accepted socket in parent
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
  server.launch(&server);
  return 0;
}