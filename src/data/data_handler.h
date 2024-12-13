#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>
#include "models/book.h"

// Fungsi untuk memuat buku dari file JSON
int load_books_from_json(const char *filename, struct Book *books, int max_books);

// Fungsi untuk menyimpan buku ke file JSON
int save_books_to_json(const char *filename, struct Book *books, int count);

// Fungsi CRUD

// Menambahkan buku baru
int add_book(const char *filename, struct Book new_book);

// Mengupdate buku berdasarkan ID
int update_book(const char *filename, int id, struct Book updated_book);

// Menghapus buku berdasarkan ID
int delete_book(const char *filename, int id);

// Mendapatkan buku berdasarkan ID
struct Book *get_book_by_id(const char *filename, int id);

#endif // DATA_HANDLER_H