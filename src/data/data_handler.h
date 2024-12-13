#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>

// Struktur Book
struct Book {
    int id;
    char title[100];
    char author[100];
    char publisher[100];
    int year;
    int pages;
    char edition[100];
    char description[1000];
    char status[100];
};

// Fungsi untuk membaca file JSON dan memetakan ke array struct Book
int load_books(const char *filename, struct Book *books, int *count);

// Fungsi untuk menyimpan array struct Book ke file JSON
void save_books(const char *filename, struct Book *books, int count);

// Fungsi untuk menambahkan buku baru
void add_book(struct Book *books, int *count, struct Book new_book);

// Fungsi untuk menghapus buku berdasarkan ID
void delete_book(struct Book *books, int *count, int id);

// Fungsi untuk mengupdate buku berdasarkan ID
void update_book(struct Book *books, int count, int id, struct Book updated_book);

#endif // DATA_HANDLER_H