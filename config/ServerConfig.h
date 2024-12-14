/**
 * @file ServerConfig.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief ADT untuk konfigurasi server
 * @date 2024-12-14
 */

#ifndef SERVER_CONFIG
#define SERVER_CONFIG 

/**
 * @brief Port default yang digunakan oleh webserver
 * 
 * Konstanta ini menentukan nomor port yang akan digunakan
 * oleh webserver untuk menerima koneksi HTTP.
 */
static int WEBSERVER_PORT = 8080;

/**
 * @brief Jumlah maksimal proses concurrent yang diizinkan
 * 
 * Konstanta ini membatasi jumlah proses yang dapat berjalan
 * secara bersamaan dalam sistem.
 */
static int MAX_PROCESSES = 10;

/**
 * @brief Ukuran maksimal buffer untuk transfer data
 * 
 * Konstanta ini menentukan ukuran maksimal (dalam bytes) untuk
 * data yang dapat dikirim atau diterima dalam satu operasi.
 */
static int MAX_BUFFER_SIZE = 32768;

/**
 * @brief Kapasitas maksimal penyimpanan buku
 * 
 * Konstanta ini menentukan jumlah maksimal buku yang dapat
 * disimpan dalam sistem.
 */
static int MAX_BOOKS = 1000;

/**
 * @brief Lokasi file penyimpanan data buku
 * 
 * Konstanta ini menentukan path ke file JSON yang digunakan
 * untuk menyimpan data buku secara persisten.
 */
static const char *BOOKS_DATA_FILE = "books.json";

#endif