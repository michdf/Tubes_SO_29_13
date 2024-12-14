/**
 * @file DataHandler.h
 * @author Micho Dhani Firmansyah (micho.dhani.tif423@polban.ac.id)
 * @brief ADT untuk mengelola data buku
 * @date 2024-12-14
 */

#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "models/Book.h"

/**
 * @brief Memuat data buku dari file JSON
 * 
 * Fungsi ini membaca file JSON yang berisi data buku dan memuat datanya
 * ke dalam array of struct Book yang telah dialokasikan.
 * 
 * @param books Pointer ke array of struct Book untuk menyimpan data yang dibaca
 * @return int Jumlah buku yang berhasil dimuat dari file
 *         -1 jika terjadi kesalahan dalam pembacaan file
 */
int load_books_from_json(struct Book *books);

/**
 * @brief Menyimpan data buku ke dalam file JSON
 * 
 * Fungsi ini mengambil array of struct Book dan jumlah buku yang akan disimpan,
 * kemudian menyimpannya ke dalam file JSON. Data akan disimpan dalam format yang
 * telah ditentukan untuk memudahkan pembacaan kembali.
 * 
 * @param books Pointer ke array of struct Book yang berisi data buku yang akan disimpan
 * @param count Jumlah buku yang akan disimpan ke dalam file
 * @return int Status operasi:
 *         0 jika penyimpanan berhasil
 *         -1 jika terjadi kesalahan dalam proses penyimpanan
 */
int save_books_to_json(struct Book *books, int count);

// Fungsi CRUD

/**
 * @brief Menambahkan buku baru ke dalam sistem
 * 
 * Fungsi ini menerima data buku baru dan menambahkannya ke dalam
 * sistem penyimpanan. ID buku akan digenerate secara otomatis.
 * 
 * @param new_book Struct Book berisi data buku yang akan ditambahkan
 * @return int ID buku yang baru ditambahkan jika berhasil
 *         -1 jika terjadi kesalahan
 */
int add_book(struct Book new_book);

/**
 * @brief Mengupdate data buku yang sudah ada
 * 
 * Fungsi ini mencari buku berdasarkan ID dan mengupdate datanya
 * dengan data baru yang diberikan.
 * 
 * @param id ID buku yang akan diupdate
 * @param updated_book Struct Book berisi data baru untuk update
 * @return int 0 jika update berhasil
 *         -1 jika buku tidak ditemukan atau terjadi kesalahan
 */
int update_book(int id, struct Book updated_book);

/**
 * @brief Menghapus buku dari sistem
 * 
 * Fungsi ini menghapus buku dari sistem berdasarkan ID yang diberikan.
 * 
 * @param id ID buku yang akan dihapus
 * @return int 0 jika penghapusan berhasil
 *         -1 jika buku tidak ditemukan atau terjadi kesalahan
 */
int delete_book(int id);

/**
 * @brief Mendapatkan data buku berdasarkan ID
 * 
 * Fungsi ini mencari dan mengembalikan pointer ke data buku
 * yang memiliki ID yang sesuai.
 * 
 * @param id ID buku yang dicari
 * @return struct Book* Pointer ke data buku jika ditemukan
 *         NULL jika buku tidak ditemukan
 */
struct Book *get_book_by_id(int id);

/**
 * @brief Mendapatkan seluruh data buku
 * 
 * Fungsi ini mengembalikan pointer ke array yang berisi
 * seluruh data buku dalam sistem.
 * 
 * @return struct Book* Pointer ke array of Book yang berisi seluruh data buku
 *         NULL jika terjadi kesalahan atau tidak ada buku
 */
struct Book *get_books();

#endif // DATA_HANDLER_H