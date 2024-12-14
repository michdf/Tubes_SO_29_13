#include "Handler.h"
#include "../data/data_handler.h"
#include "../data/models/book.h"
#include "http/HTTPRequest.h"
#include "http/HTTPResponse.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void responseError(int socket, int code, const char *message) {
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

void handleNotFound(int socket, struct HTTPRequest *request, char *params) {
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

void handleRoot(int socket, struct HTTPRequest *request, char *params) {
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

void handleAddBook(int socket, struct HTTPRequest *request, char *params) {
  printf("%d\n", request->method);
  if (request->method != POST) {
    responseError(socket, 405, "Method Not Allowed");
    return;
  }

  cJSON *jsonObj = cJSON_CreateObject();
  cJSON *requestBody = cJSON_Parse(request->body);
  char *response;

  if (jsonObj == NULL) {
    perror("addBook: cJSON_CreateObject");
    return;
  }

  // Add book to database
  if (requestBody == NULL) {
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
      cJSON_GetObjectItem(requestBody, "status")->valuestring);

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

void handleViewBooks(int socket, struct HTTPRequest *request, char *params) {
  if (request->method != GET) {
    responseError(socket, 405, "Method Not Allowed");
    return;
  }

  struct Book books[100];
  int book_count = load_books_from_json(books);

  if (book_count == -1) {
    responseError(socket, 500, "Internal Server Error");
    return;
  }

  cJSON *bookArray = cJSON_CreateArray();

  for (int i = 0; i < book_count; i++) {
    cJSON *bookObj = cJSON_CreateObject();
    cJSON_AddNumberToObject(bookObj, "id", books[i].id);
    cJSON_AddStringToObject(bookObj, "title", books[i].title);
    cJSON_AddStringToObject(bookObj, "author", books[i].author);
    cJSON_AddStringToObject(bookObj, "publisher", books[i].publisher);
    cJSON_AddNumberToObject(bookObj, "year", books[i].year);
    cJSON_AddNumberToObject(bookObj, "pages", books[i].pages);
    cJSON_AddStringToObject(bookObj, "edition", books[i].edition);
    cJSON_AddStringToObject(bookObj, "description", books[i].description);
    cJSON_AddStringToObject(bookObj, "status", books[i].status);

    cJSON_AddItemToArray(bookArray, bookObj);
  }

  char *responseBody = cJSON_PrintUnformatted(bookArray);

  char *httpResponse = response_constructor(200, responseBody);

  write(socket, httpResponse, strlen(httpResponse));

  cJSON_Delete(bookArray);
  free(responseBody);
  free(httpResponse);
  close(socket);
}

void handleViewBookById(int socket, struct HTTPRequest *request, char *params) {
  if (request->method != GET) {
    responseError(socket, 405, "Method Not Allowed");
    return;
  }

  int book_id = atoi(params);
  struct Book *book = get_book_by_id(book_id);

  if (book == NULL) {
    responseError(socket, 404, "Book not found");
    return;
  }

  cJSON *response = cJSON_CreateObject();
  cJSON_AddNumberToObject(response, "id", book->id);
  cJSON_AddStringToObject(response, "title", book->title);
  cJSON_AddStringToObject(response, "author", book->author);
  cJSON_AddStringToObject(response, "publisher", book->publisher);
  cJSON_AddNumberToObject(response, "year", book->year);
  cJSON_AddNumberToObject(response, "pages", book->pages);
  cJSON_AddStringToObject(response, "edition", book->edition);
  cJSON_AddStringToObject(response, "description", book->description);
  cJSON_AddStringToObject(response, "status", book->status);

  char *responseBody = cJSON_PrintUnformatted(response);
  char *httpResponse = response_constructor(200, responseBody);

  write(socket, httpResponse, strlen(httpResponse));

  free(responseBody);
  free(httpResponse);
  cJSON_Delete(response);
  close(socket);
}

void handleUpdateBook(int socket, struct HTTPRequest *request, char *params) {
  printf("%d\n", request->method);
  if (request->method != PUT) {
    responseError(socket, 405, "Method Not Allowed");
    return;
  }

  int book_id = atoi(params);

  cJSON *requestBody = cJSON_Parse(request->body);
  if (requestBody == NULL) {
    responseError(socket, 400, "Bad Request");
    return;
  }

  struct Book *updated_book = book_constructor(
      cJSON_GetObjectItem(requestBody, "id")->valueint,
      cJSON_GetObjectItem(requestBody, "title")->valuestring,
      cJSON_GetObjectItem(requestBody, "author")->valuestring,
      cJSON_GetObjectItem(requestBody, "publisher")->valuestring,
      cJSON_GetObjectItem(requestBody, "year")->valueint,
      cJSON_GetObjectItem(requestBody, "pages")->valueint,
      cJSON_GetObjectItem(requestBody, "edition")->valuestring,
      cJSON_GetObjectItem(requestBody, "description")->valuestring,
      cJSON_GetObjectItem(requestBody, "status")->valuestring);

  printf("AMAN\n");
  if (update_book(book_id, *updated_book) == -1) {
    free(updated_book);
    responseError(socket, 404, "Book not found");
    return;
  }

  free(updated_book);

  cJSON *response = cJSON_CreateObject();
  cJSON_AddNumberToObject(response, "status", 200);
  cJSON_AddStringToObject(response, "message", "Book updated successfully");

  char *responseBody = cJSON_PrintUnformatted(response);
  char *httpResponse = response_constructor(200, responseBody);

  write(socket, httpResponse, strlen(httpResponse));

  free(responseBody);
  free(httpResponse);
  cJSON_Delete(response);
  cJSON_Delete(requestBody);
  close(socket);
}

void handleDeleteBook(int socket, struct HTTPRequest *request, char *params) {
  if (request->method != DELETE) {
    responseError(socket, 405, "Method Not Allowed");
    return;
  }

  int book_id = atoi(params);

  if (delete_book(book_id) == -1) {
    responseError(socket, 404, "Book not found");
    return;
  }

  cJSON *response = cJSON_CreateObject();
  cJSON_AddNumberToObject(response, "status", 200);
  cJSON_AddStringToObject(response, "message", "Book deleted successfully");

  char *responseBody = cJSON_PrintUnformatted(response);
  char *httpResponse = response_constructor(200, responseBody);

  write(socket, httpResponse, strlen(httpResponse));

  free(responseBody);
  free(httpResponse);
  cJSON_Delete(response);
  close(socket);
}