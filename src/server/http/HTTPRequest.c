/**
 * @file HTTPRequest.c
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief Implementasi ADT untuk menangani request HTTP
 * @date 2024-12-14
 */

#include "HTTPRequest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void http_request_cleanup(struct HTTPRequest *request) {
  if (request) {
    free(request->body);
    free(request->URI);
  }
}

static int method_select(char *method) {
  if (strcmp(method, "GET") == 0) {
    return GET;
  } else if (strcmp(method, "POST") == 0) {
    return POST;
  } else if (strcmp(method, "PUT") == 0) {
    return PUT;
  } else if (strcmp(method, "HEAD") == 0) {
    return HEAD;
  } else if (strcmp(method, "PATCH") == 0) {
    return PATCH;
  } else if (strcmp(method, "DELETE") == 0) {
    return DELETE;
  } else if (strcmp(method, "CONNECT") == 0) {
    return CONNECT;
  } else if (strcmp(method, "OPTIONS") == 0) {
    return OPTIONS;
  } else if (strcmp(method, "TRACE") == 0) {
    return TRACE;
  } else {
    return -1;
  }
}

struct HTTPRequest http_request_constructor(char *request_string) {
  struct HTTPRequest request;
  memset(&request, 0, sizeof(request));

  // Make a copy of the original request string
  char *request_copy = strdup(request_string);

  // Find the double CRLF that separates headers from body
  char *body_start = strstr(request_copy, "\r\n\r\n");
  if (body_start) {
    // Move pointer past the double CRLF
    body_start += 4;
    request.body = strdup(body_start); // Make a copy of body

    // Null terminate the headers portion without affecting original
    *body_start = '\0';
  }

  // Parse first line from the copy
  char *request_line = strtok(request_copy, "\r\n");
  if (request_line) {
    char *method = strtok(request_line, " ");
    if (method) {
      request.method = method_select(method);
    }

    char *URI = strtok(NULL, " ");
    if (URI) {
      size_t len = strlen(URI);
      // Remove trailing '/' if it exists and length > 1 (keep root '/')
      if (len > 1 && URI[len-1] == '/') {
          URI[len-1] = '\0';
      }
      request.URI = strdup(URI); // Make a copy
    }

    char *HTTPVersion = strtok(NULL, " ");
    if (HTTPVersion) {
      HTTPVersion = strtok(HTTPVersion, "/");
      HTTPVersion = strtok(NULL, "/");
      if (HTTPVersion) {
        request.HTTPVersion = atof(HTTPVersion);
      }
    }
  }

  free(request_copy); // Free the copy
  return request;
}