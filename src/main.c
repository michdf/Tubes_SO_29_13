#include "../config/ServerConfig.h"
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

/**
 * @brief Server global untuk penanganan signal
 * 
 * Variable ini digunakan untuk mengakses server saat
 * menangani signal interupsi (SIGINT)
 */
static struct Server *global_server = NULL;

/**
 * @brief Handler untuk signal SIGCHLD
 * 
 * Fungsi ini mencegah terbentuknya proses zombie dengan
 * melakukan wait pada child process yang telah selesai
 * 
 * @param sig Signal number
 */
void handle_sigchld(int sig) {
  while (waitpid(-1, NULL, WNOHANG) > 0);
}

/**
 * @brief Handler untuk signal SIGINT (Ctrl+C)
 * 
 * Fungsi ini melakukan cleanup saat server dimatikan,
 * menutup socket dan mengakhiri program dengan rapi
 * 
 * @param sig Signal number
 */
void handle_sigint(int sig) {
  printf("\nReceived SIGINT (Ctrl+C). Shutting down server...\n");

  if (global_server != NULL) {
    if (global_server->socket > 0) {
      close(global_server->socket);
    }
  }

  exit(0);
}

/**
 * @brief Fungsi utama server
 * 
 * Fungsi ini menjalankan loop utama server yang:
 * 1. Menginisialisasi route-route yang tersedia
 * 2. Menangani incoming connections
 * 3. Melakukan fork untuk setiap koneksi baru
 * 4. Memproses HTTP request
 * 5. Mengirim response ke client
 * 
 * Proses parent:
 * - Menerima koneksi baru
 * - Melakukan fork untuk setiap koneksi
 * - Menutup socket yang tidak digunakan
 * 
 * Proses child:
 * - Memproses request HTTP
 * - Mengirim response
 * - Menutup koneksi
 * - Exit
 * 
 * @param server Pointer ke struct Server
 */
void launch(struct Server *server) {
  char buffer[MAX_BUFFER_SIZE];
  int address_length = sizeof(server->address);
  int new_socket;

  struct Route *route = init_route("/", handle_root, GET);
  add_route(route, "/books", handle_view_books, GET);
  add_route(route, "/books", handle_add_book, POST);
  add_route(route, "/books/:id", handle_view_book_by_id, GET);
  add_route(route, "/books/:id", handle_update_book, PUT);
  add_route(route, "/books/:id", handle_delete_book, DELETE);

  handle_sigchld(SIGCHLD);
  signal(SIGINT, handle_sigint);

  while (true) {
    printf("MENUNGGU KONEKSI...\n");
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
        void (*handler)(int, struct HTTPRequest *, char *params) = find_handler(found, request.method);
        char *params = extract_params(request.URI, found->key);
        if (handler != NULL) {
          char *params = extract_params(found->key, request.URI);
          handler(new_socket, &request, params);
          free(params);
        } else {
          response_error(new_socket, 405, "Method Not Allowed");
        }
      } else {
        handle_not_found(new_socket, &request, NULL);
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

/**
 * @brief Fungsi main
 * 
 * Fungsi ini:
 * 1. Menginisialisasi server dengan konfigurasi default
 * 2. Menyimpan reference ke server global
 * 3. Memulai server
 * 
 * @return int Status exit program
 */
int main(void) {
  struct Server server =
      server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, WEBSERVER_PORT,
                         MAX_PROCESSES, launch);
  global_server = &server;
  server.launch(&server);
  return 0;
}