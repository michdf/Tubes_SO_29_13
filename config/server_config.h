#ifndef SERVER_CONFIG
#define SERVER_CONFIG 

// Port untuk webserver
static int WEBSERVER_PORT = 8080;

// Jumlah maksimal proses yang dapat dijalankan
static int MAX_PROCESSES = 10;

// Jumlah maksimal ukuran data yang dapat dikirim dan diterima
static int MAX_BUFFER_SIZE = 1024;

// File untuk menyimpan data buku dalam format JSON
static const char *BOOKS_DATA_FILE = "books.json";

#endif