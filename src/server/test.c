#include "../../config/server_config.h"
#include "Server.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void launch(struct Server *server) {
  char buffer[80000];
  char *hello =
      "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: "
      "Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 "
      "GMT\nContent-Type: text/html\nConnection: "
      "Closed\n\n<html><body><h1>I got Dejavu</h1></body></html>";
  int address_length = sizeof(server->address);
  int new_socket;

  while (true) {
    printf("WAITING FOR CONNECTION...\n");
    new_socket = accept(server->socket, (struct sockaddr *)&server->address,
                        (socklen_t *)&address_length);
    read(new_socket, buffer, 80000);
    printf("%s\n", buffer);

    write(new_socket, hello, strlen(hello));
    close(new_socket);
  }
}

int main() {
  struct Server server =
      server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, WEBSERVER_PORT,
                         MAX_PROCESSES, launch);
  server.launch(&server);
}