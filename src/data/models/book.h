#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>

// Struktur untuk merepresentasikan buku
struct Book {
    int id;                      // ID unik buku
    char title[100];             // Judul buku
    char author[100];            // Nama penulis
    char publisher[100];         // Nama penerbit
    int year;                    // Tahun penerbitan
    int pages;                   // Jumlah halaman
    char edition[100];           // Edisi buku
    char description[1000];      // Deskripsi buku
    char status[100];            // Status buku (contoh: "available" atau "borrowed")
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

#endif // BOOK_H
