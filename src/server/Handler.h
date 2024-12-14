/**
 * @file Handler.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief Modul untuk menangani request HTTP pada server
 * @date 2024-12-14
 */

#ifndef HANDLER_H
#define HANDLER_H
#include "http/HTTPRequest.h"

/**
 * @brief Mengirim response error ke client
 * 
 * @param socket Socket koneksi client
 * @param code Kode error HTTP
 * @param message Pesan error yang akan dikirim
 */
void response_error(int socket, int code, const char *message);

/**
 * @brief Menangani request untuk halaman yang tidak ditemukan
 * 
 * @param socket Socket koneksi client
 * @param request Pointer ke struct HTTPRequest yang berisi detail request
 * @param params Parameter URL yang diterima
 */
void handle_not_found(int socket, struct HTTPRequest* request, char *params);

/**
 * @brief Menangani request untuk halaman utama
 * 
 * @param socket Socket koneksi client
 * @param request Pointer ke struct HTTPRequest yang berisi detail request
 * @param params Parameter URL yang diterima
 */
void handle_root(int socket, struct HTTPRequest* request, char *params);

/**
 * @brief Menangani request untuk melihat semua buku
 * 
 * @param socket Socket koneksi client
 * @param request Pointer ke struct HTTPRequest yang berisi detail request
 * @param params Parameter URL yang diterima
 */
void handle_view_books(int socket, struct HTTPRequest* request, char *params);

/**
 * @brief Menangani request untuk melihat buku berdasarkan ID
 * 
 * @param socket Socket koneksi client
 * @param request Pointer ke struct HTTPRequest yang berisi detail request
 * @param params Parameter URL yang berisi ID buku
 */
void handle_view_book_by_id(int socket, struct HTTPRequest* request, char *params);

/**
 * @brief Menangani request untuk menambah buku baru
 * 
 * @param socket Socket koneksi client
 * @param request Pointer ke struct HTTPRequest yang berisi detail request
 * @param params Parameter URL yang diterima
 */
void handle_add_book(int socket, struct HTTPRequest* request, char *params);

/**
 * @brief Menangani request untuk mengupdate data buku
 * 
 * @param socket Socket koneksi client
 * @param request Pointer ke struct HTTPRequest yang berisi detail request
 * @param params Parameter URL yang berisi data update
 */
void handle_update_book(int socket, struct HTTPRequest* request, char *params);

/**
 * @brief Menangani request untuk menghapus buku
 * 
 * @param socket Socket koneksi client
 * @param request Pointer ke struct HTTPRequest yang berisi detail request
 * @param params Parameter URL yang berisi ID buku
 */
void handle_delete_book(int socket, struct HTTPRequest* request, char *params);

#endif