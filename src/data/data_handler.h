#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <stdio.h>
#include "models/book.h"

// Fungsi untuk memuat buku dari file JSON
int load_books_from_json(struct Book *books);

// Fungsi untuk menyimpan buku ke file JSON
int save_books_to_json(struct Book *books, int count);

// Fungsi CRUD

// Menambahkan buku baru
int add_book(struct Book new_book);

// Mengupdate buku berdasarkan ID
int update_book(int id, struct Book updated_book);

// Menghapus buku berdasarkan ID
int delete_book(int id);

// Mendapatkan buku berdasarkan ID
struct Book *get_book_by_id(int id);

// Mendapatkan semua buku
struct Book *get_books();

#endif // DATA_HANDLER_H