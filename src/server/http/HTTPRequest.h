/**
 * @file HTTPRequest.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief ADT untuk menangani request HTTP
 * @date 2024-12-14
 */

#ifndef HTTPRequest_h
#define HTTPRequest_h
#include "HTTPInfo.h"

/**
 * @brief Struktur data untuk menyimpan informasi request HTTP
 * 
 * Struktur ini menyimpan komponen-komponen penting dari sebuah
 * HTTP request seperti metode, URI, body, dan versi HTTP.
 */
struct HTTPRequest
{
    int method;         ///< Metode HTTP yang digunakan (GET, POST, dll)
    char *URI;          ///< URI yang diminta oleh client
    char *body;         ///< Isi body dari request
    float HTTPVersion;  ///< Versi protokol HTTP yang digunakan
};

/**
 * @brief Membuat objek HTTPRequest baru dari string request
 * 
 * Fungsi ini mengurai string request HTTP mentah dan mengkonversinya
 * menjadi struktur HTTPRequest yang terorganisir.
 * 
 * @param request_string String mentah yang berisi request HTTP
 * @return struct HTTPRequest Objek HTTPRequest yang telah diinisialisasi
 */
struct HTTPRequest http_request_constructor(char *request_string);

#endif