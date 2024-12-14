/**
 * @file HTTPInfo.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief Implementasi ADT untuk informasi dan konstanta HTTP
 * @date 2024-12-14
 */

#include "HTTPInfo.h"

const char* HTTPResponseCodeToString(enum HTTPResponseCodes code) {
    switch (code) {
        case HTTP_OK: return "OK";
        case HTTP_CREATED: return "Created";
        case HTTP_ACCEPTED: return "Accepted";
        case HTTP_NO_CONTENT: return "No Content";
        case HTTP_MOVED_PERMANENTLY: return "Moved Permanently";
        case HTTP_FOUND: return "Found";
        case HTTP_NOT_MODIFIED: return "Not Modified";
        case HTTP_BAD_REQUEST: return "Bad Request";
        case HTTP_UNAUTHORIZED: return "Unauthorized";
        case HTTP_FORBIDDEN: return "Forbidden";
        case HTTP_NOT_FOUND: return "Not Found";
        case HTTP_METHOD_NOT_ALLOWED: return "Method Not Allowed";
        case HTTP_INTERNAL_SERVER_ERROR: return "Internal Server Error";
        case HTTP_NOT_IMPLEMENTED: return "Not Implemented";
        case HTTP_BAD_GATEWAY: return "Bad Gateway";
        case HTTP_SERVICE_UNAVAILABLE: return "Service Unavailable";
        default: return "Unknown Status Code";
    }
}