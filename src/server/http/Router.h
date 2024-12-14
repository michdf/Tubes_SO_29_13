/**
 * @file Router.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief ADT untuk penanganan routing HTTP
 * @date 2024-12-14
 */

#ifndef Route_h
#define Route_h

#include "HTTPRequest.h"

/**
 * @brief Struktur data untuk menyimpan handler route
 * 
 * Struktur ini menyimpan fungsi handler dan metode HTTP
 * yang terkait dengan suatu route.
 */
struct RouteHandler {
    void (*handler)(int, struct HTTPRequest*, char *params); ///< Fungsi handler untuk route
    int method;                                              ///< Metode HTTP yang ditangani
};

/**
 * @brief Struktur data untuk menyimpan informasi route
 * 
 * Struktur ini mengimplementasikan node dalam binary tree
 * untuk menyimpan dan mencari route.
 */
struct Route {
    char* key;                    ///< Path URL untuk route
    struct RouteHandler *handlers; ///< Array dari handler
    int handler_count;            ///< Jumlah handler yang terdaftar
    struct Route *left, *right;   ///< Pointer ke child nodes
};

/**
 * @brief Menginisialisasi route baru
 * 
 * @param key Path URL untuk route
 * @param handler Fungsi handler untuk route
 * @param method Metode HTTP yang akan ditangani
 * @return struct Route* Pointer ke route yang baru dibuat
 */
struct Route * init_route(char* key, void (*handler)(int, struct HTTPRequest*, char *params), int method);

/**
 * @brief Menambahkan route baru ke dalam tree
 * 
 * @param root Root dari route tree
 * @param key Path URL untuk route baru
 * @param handler Fungsi handler untuk route
 * @param method Metode HTTP yang akan ditangani
 * @return struct Route* Root dari tree yang telah diupdate
 */
struct Route * add_route(struct Route * root, char* key, void (*handler)(int, struct HTTPRequest*, char *params), int method);

/**
 * @brief Mencari route berdasarkan key
 * 
 * @param root Root dari route tree
 * @param key Path URL yang dicari
 * @return struct Route* Route yang ditemukan atau NULL
 */
struct Route * search(struct Route * root, char * key);

/**
 * @brief Mencari route berdasarkan metode HTTP
 * 
 * @param route Route yang akan dicari
 * @param method Metode HTTP yang dicari
 * @return struct Route* Route yang sesuai atau NULL
 */
struct Route * find_route(struct Route* route, int method);

/**
 * @brief Mencari handler untuk metode HTTP tertentu
 * 
 * @param route Route yang akan dicari
 * @param method Metode HTTP yang dicari
 * @return void* Handler yang ditemukan atau NULL
 */
void* find_handler(struct Route* route, int method);

/**
 * @brief Menampilkan seluruh route yang terdaftar
 * 
 * @param root Root dari route tree
 */
void show_routes(struct Route * root);

/**
 * @brief Mengekstrak parameter dari URI
 * 
 * @param pattern Pola URL yang digunakan
 * @param uri URI yang akan diekstrak
 * @return char* String parameter yang diekstrak
 */
char * extract_params(const char* pattern, const char* uri);

#endif