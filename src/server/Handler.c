#include "Handler.h"
#include "http/HTTPResponse.h"
#include "../data/data_handler.h"
#include "../data/models/book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cjson/cJSON.h>

void responseError(int socket, int code, const char *message){
    cJSON *jsonObj = cJSON_CreateObject();
    cJSON_AddNumberToObject(jsonObj, "status", code);
    cJSON_AddStringToObject(jsonObj, "message", message);
    char *responseBody = cJSON_PrintUnformatted(jsonObj);
    cJSON_Delete(jsonObj);

    if (responseBody == NULL) {
        perror("responseError: cJSON_PrintUnformatted");
        return;
    }

    char *response = response_constructor(code, responseBody);

    if (response == NULL) {
        perror("responseError: response_constructor");
        return;
    }

    write(socket, response, strlen(response));
    free(response);
    close(socket);
}

void handleNotFound(int socket, struct HTTPRequest* request) {
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

void handleRoot(int socket, struct HTTPRequest* request) {
  char *body = "<html><body><h1>Tugas Besar API</h1></body></html>";
  char *response = response_constructor(200, body);

  if (response == NULL) {
    perror("handleRoot: response_constructor");
    return;
  }

  write(socket, response, strlen(response));
  free(response);
  close(socket);
}

void handleAddBook(int socket, struct HTTPRequest* request) {
  cJSON *jsonObj = cJSON_CreateObject();
  cJSON *requestBody = cJSON_Parse(request->body);
  char *response;

  if (jsonObj == NULL) {
    perror("addBook: cJSON_CreateObject");
    return;
  }

  // Add book to database
  if(requestBody == NULL) {
    printf("ISI request body: %s\n", request->body);
    responseError(socket, 400, "Bad Request");
    return;
  } 

  struct Book *new_book;
  new_book = book_constructor(
    cJSON_GetObjectItem(requestBody, "id")->valueint,
    cJSON_GetObjectItem(requestBody, "title")->valuestring,
    cJSON_GetObjectItem(requestBody, "author")->valuestring,
    cJSON_GetObjectItem(requestBody, "publisher")->valuestring,
    cJSON_GetObjectItem(requestBody, "year")->valueint,
    cJSON_GetObjectItem(requestBody, "pages")->valueint,
    cJSON_GetObjectItem(requestBody, "edition")->valuestring,
    cJSON_GetObjectItem(requestBody, "description")->valuestring,
    cJSON_GetObjectItem(requestBody, "status")->valuestring
  );

  add_book(*new_book);
  free(new_book);
  
  cJSON_Delete(requestBody);

  cJSON_AddNumberToObject(jsonObj, "status", 200);
  cJSON_AddStringToObject(jsonObj, "message", "Successfully added new book");

  char *responseBody = cJSON_PrintUnformatted(jsonObj);
  cJSON_Delete(jsonObj);

  if (responseBody == NULL) {
    perror("addBook: cJSON_PrintUnformatted");
    return;
  }
  response = response_constructor(200, responseBody);

  if (response == NULL) {
    perror("addBook: response_constructor");
    return;
  }

  write(socket, response, strlen(response));
  free(response);
  close(socket);
}