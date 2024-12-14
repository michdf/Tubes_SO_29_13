/**
 * @file book.h
 * @author Micho Dhani Firmansyah (micho.dhani.tif423@polban.ac.id)
 * @brief File header untuk manajemen data buku dalam sistem perpustakaan
 * @date 2024-12-14
 */

#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

/** @brief Panjang maksimum yang diizinkan untuk judul buku */
#define MAX_TITLE_LEN 100
/** @brief Panjang maksimum yang diizinkan untuk nama penulis */
#define MAX_AUTHOR_LEN 100
/** @brief Panjang maksimum yang diizinkan untuk nama penerbit */
#define MAX_PUBLISHER_LEN 100
/** @brief Panjang maksimum yang diizinkan untuk edisi buku */
#define MAX_EDITION_LEN 100
/** @brief Panjang maksimum yang diizinkan untuk deskripsi buku */
#define MAX_DESC_LEN 1000
/** @brief Panjang maksimum yang diizinkan untuk status buku */
#define MAX_STATUS_LEN 100

/**
 * @brief Struktur data untuk merepresentasikan informasi buku
 * @details Struktur ini menyimpan seluruh atribut yang berkaitan dengan sebuah buku
 */
struct Book {
    int id;                             /**< ID unik untuk identifikasi buku */
    char title[MAX_TITLE_LEN];         /**< Judul dari buku */
    char author[MAX_AUTHOR_LEN];       /**< Nama penulis buku */
    char publisher[MAX_PUBLISHER_LEN];  /**< Nama penerbit buku */
    int year;                          /**< Tahun buku diterbitkan */
    int pages;                         /**< Jumlah halaman buku */
    char edition[MAX_EDITION_LEN];     /**< Edisi atau versi buku */
    char description[MAX_DESC_LEN];    /**< Deskripsi atau sinopsis buku */
    char status[MAX_STATUS_LEN];       /**< Status ketersediaan buku ("tersedia" atau "dipinjam") */
};

/**
 * @brief Daftar kode error yang mungkin terjadi dalam operasi buku
 */
enum BookError {
    BOOK_SUCCESS = 0,               /**< Operasi berhasil dilakukan */
    BOOK_ERROR_NULL_POINTER = -1,   /**< Error: pointer buku bernilai NULL */
    BOOK_ERROR_INVALID_INPUT = -2,  /**< Error: input data buku tidak valid */
    BOOK_ERROR_MEMORY = -3          /**< Error: gagal dalam alokasi memori */
};

/**
 * @brief Membuat objek buku baru
 * @details Mengalokasikan memori dan menginisialisasi struktur Book dengan data yang diberikan
 * 
 * @param id ID unik untuk buku
 * @param title Judul buku
 * @param author Nama penulis buku
 * @param publisher Nama penerbit buku
 * @param year Tahun penerbitan buku
 * @param pages Jumlah halaman buku
 * @param edition Edisi atau versi buku
 * @param description Deskripsi atau sinopsis buku
 * @param status Status ketersediaan buku
 * @param error Pointer untuk menyimpan kode error jika terjadi kesalahan
 * 
 * @return Pointer ke struktur Book yang baru dibuat, NULL jika gagal
 */
struct Book *book_constructor(int id, const char* title, const char* author,
                            const char* publisher, int year, int pages,
                            const char* edition, const char* description,
                            const char* status, int* error);

/**
 * @brief Menampilkan informasi detail buku
 * @details Mencetak seluruh atribut buku ke output standar
 * 
 * @param book Pointer ke struktur Book yang akan ditampilkan
 */
void print_book(const struct Book *book);

/**
 * @brief Memvalidasi data buku
 * @details Memeriksa apakah semua field dalam struktur Book memiliki nilai yang valid
 * 
 * @param book Pointer ke struktur Book yang akan divalidasi
 * @param error Pointer untuk menyimpan kode error jika terjadi kesalahan
 * @return true jika data valid, false jika tidak valid
 */
bool validate_book(const struct Book* book, int* error);

/**
 * @brief Membandingkan dua buku berdasarkan ID
 * @details Fungsi pembanding untuk mengurutkan atau mencari buku berdasarkan ID
 * 
 * @param a Pointer ke buku pertama
 * @param b Pointer ke buku kedua
 * @return -1 jika a < b, 0 jika a = b, 1 jika a > b
 */
int compare_book_by_id(const struct Book *a, const struct Book *b);

/**
 * @brief Menghapus objek buku dari memori
 * @details Membebaskan memori yang dialokasikan untuk struktur Book
 * 
 * @param book Pointer ke struktur Book yang akan dihapus
 */
void book_destructor(struct Book* book);

/**
 * @brief Mengkonversi data buku ke format JSON
 * @details Mengubah struktur Book menjadi string dalam format JSON
 * 
 * @param book Pointer ke struktur Book yang akan dikonversi
 * @return String dalam format JSON yang merepresentasikan data buku
 */
char* book_to_json(const struct Book* book);

#endif // BOOK_H