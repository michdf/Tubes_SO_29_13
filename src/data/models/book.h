#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 100
#define MAX_PUBLISHER_LEN 100
#define MAX_EDITION_LEN 100
#define MAX_DESC_LEN 1000
#define MAX_STATUS_LEN 100

// Struktur untuk merepresentasikan buku
struct Book {
    int id;                      // ID unik buku
    char title[MAX_TITLE_LEN];             // Judul buku
    char author[MAX_AUTHOR_LEN];            // Nama penulis
    char publisher[MAX_PUBLISHER_LEN];         // Nama penerbit
    int year;                    // Tahun penerbitan
    int pages;                   // Jumlah halaman
    char edition[MAX_EDITION_LEN];           // Edisi buku
    char description[MAX_DESC_LEN];      // Deskripsi buku
    char status[MAX_STATUS_LEN];            // Status buku (contoh: "available" atau "borrowed")
};

struct Book *book_constructor(int id, const char *title, const char *author, const char *publisher, 
                              int year, int pages, const char *edition, const char *description, const char *status);

// Fungsi untuk mencetak detail buku
void print_book(const struct Book *book);

// Fungsi validasi data buku
int validate_book(const struct Book *book);

// Fungsi untuk membandingkan dua buku berdasarkan ID
int compare_book_by_id(const struct Book *a, const struct Book *b);

// Fungsi untuk membuat instance buku dari data input
struct Book create_book(int id, const char *title, const char *author, const char *publisher, 
                        int year, int pages, const char *edition, const char *description, const char *status);

// Fungsi mengkonversi data buku ke JSON
struct json_object *books_to_json_array(const struct Book **book);

#endif // BOOK_H
