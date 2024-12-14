#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <json-c/json.h>
#include "data_handler.h"
#include "../../config/server_config.h"

// Fungsi untuk mengunci file
int lock_file(int fd) {
    struct flock lock;
    lock.l_type = F_WRLCK; // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock seluruh file

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire lock");
        return -1;
    }
    return 0;
}

// Fungsi untuk membuka kunci file
int unlock_file(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK; // Unlock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release lock");
        return -1;
    }
    return 0;
}

// Fungsi membaca buku dari file JSON
int load_books_from_json(struct Book *books) {
    int fd = open(BOOKS_DATA_FILE, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    // Mengunci file untuk operasi aman
    if (lock_file(fd) == -1) {
        close(fd);
        return -1;
    }

    // Membaca isi file
    char buffer[8192] = {0};
    ssize_t read_size = read(fd, buffer, sizeof(buffer) - 1);
    if (read_size == -1) {
        perror("Failed to read file");
        unlock_file(fd);
        close(fd);
        return -1;
    }

    buffer[read_size] = '\0'; // Null-terminate string

    // Jika file kosong atau parsing gagal, inisialisasi JSON default
    struct json_object *parsed_json = NULL;
    if (read_size == 0 || !(parsed_json = json_tokener_parse(buffer))) {
        fprintf(stderr, "Invalid or empty JSON. Resetting to default.\n");
        const char *empty_json_object = "{\"books\":[]}";
        if (ftruncate(fd, 0) == -1 || lseek(fd, 0, SEEK_SET) == -1 || write(fd, empty_json_object, strlen(empty_json_object)) == -1) {
            perror("Failed to reset JSON file");
            unlock_file(fd);
            close(fd);
            return -1;
        }
        lseek(fd, 0, SEEK_SET); // Kembali ke awal file
        parsed_json = json_tokener_parse(empty_json_object); // Parsing ulang default JSON
    }
    // Parsing JSON
    if (!parsed_json) {
        fprintf(stderr, "Failed to parse JSON\n");
        unlock_file(fd);
        close(fd);
        return -1;
    }

    // Loop untuk mengisi struct Book
    size_t n_books = json_object_array_length(parsed_json);
    for (size_t i = 0; i < n_books; i++) {
        struct json_object *book_obj = json_object_array_get_idx(parsed_json, i);
        books[i].id = json_object_get_int(json_object_object_get(book_obj, "id"));
        strncpy(books[i].title, json_object_get_string(json_object_object_get(book_obj, "title")), sizeof(books[i].title));
        strncpy(books[i].author, json_object_get_string(json_object_object_get(book_obj, "author")), sizeof(books[i].author));
        strncpy(books[i].publisher, json_object_get_string(json_object_object_get(book_obj, "publisher")), sizeof(books[i].publisher));
        books[i].year = json_object_get_int(json_object_object_get(book_obj, "year"));
        books[i].pages = json_object_get_int(json_object_object_get(book_obj, "pages"));
        strncpy(books[i].edition, json_object_get_string(json_object_object_get(book_obj, "edition")), sizeof(books[i].edition));
        strncpy(books[i].description, json_object_get_string(json_object_object_get(book_obj, "description")), sizeof(books[i].description));
        strncpy(books[i].status, json_object_get_string(json_object_object_get(book_obj, "status")), sizeof(books[i].status));
    }

    json_object_put(parsed_json); // Free memory

    // Melepaskan kunci dan menutup file
    if (unlock_file(fd) == -1) {
        close(fd);
        return -1;
    }

    close(fd);
    return n_books; // Jumlah buku yang dimuat
}


// Fungsi menyimpan buku ke file JSON
int save_books_to_json(struct Book *books, int count) {
    int fd = open(BOOKS_DATA_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    if (lock_file(fd) == -1) {
        close(fd);
        return -1;
    }

    // Membuat array JSON
    struct json_object *book_array = json_object_new_array();
    for (int i = 0; i < count; i++) {
        struct json_object *book_obj = json_object_new_object();
        json_object_object_add(book_obj, "id", json_object_new_int(books[i].id));
        json_object_object_add(book_obj, "title", json_object_new_string(books[i].title));
        json_object_object_add(book_obj, "author", json_object_new_string(books[i].author));
        json_object_object_add(book_obj, "publisher", json_object_new_string(books[i].publisher));
        json_object_object_add(book_obj, "year", json_object_new_int(books[i].year));
        json_object_object_add(book_obj, "pages", json_object_new_int(books[i].pages));
        json_object_object_add(book_obj, "edition", json_object_new_string(books[i].edition));
        json_object_object_add(book_obj, "description", json_object_new_string(books[i].description));
        json_object_object_add(book_obj, "status", json_object_new_string(books[i].status));
        json_object_array_add(book_array, book_obj);
    }

    // Menulis ke file
    const char *json_str = json_object_to_json_string_ext(book_array, JSON_C_TO_STRING_PRETTY);
    write(fd, json_str, strlen(json_str));
    json_object_put(book_array); // Free memory

    unlock_file(fd);
    close(fd);
    return 0;
}

// Menambahkan buku baru
int add_book(struct Book new_book) {
    struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        return -1; // Error loading books
    }

    // Tambahkan buku ke array
    books[book_count] = new_book;
    book_count++;

    // Simpan kembali ke JSON
    return save_books_to_json(books, book_count);
}

// Mengupdate buku berdasarkan ID
int update_book(int id, struct Book updated_book) {
    struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        return -1; // Error loading books
    }

    // Cari buku berdasarkan ID
    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            // Pertahankan ID asli
            int original_id = books[i].id;
            
            // Update data buku dengan data baru
            books[i] = updated_book;
            
            // Pastikan ID tetap sama dengan yang dicari
            books[i].id = original_id;
            
            found = 1;
            break;
        }
    }

    if (!found) {
        return -1; // Buku tidak ditemukan
    }

    // Simpan perubahan ke file JSON
    return save_books_to_json(books, book_count);
}

// Menghapus buku berdasarkan ID
int delete_book(int id) {
    struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        return -1; // Error loading books
    }

    // Cari buku untuk dihapus
    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < book_count - 1; j++) {
                books[j] = books[j + 1]; // Geser buku berikutnya
            }
            book_count--;
            break;
        }
    }

    if (!found) {
        return -1; // Buku tidak ditemukan
    }

    // Simpan kembali ke JSON
    return save_books_to_json(books, book_count);
}

// Mendapatkan buku berdasarkan ID
struct Book *get_book_by_id(int id) {
    static struct Book books[100]; // Static untuk return pointer
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        return NULL; // Error loading books
    }

    // Cari buku berdasarkan ID
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            return &books[i];
        }
    }

    return NULL; // Buku tidak ditemukan
}

// Fungsi get_book() untuk dapat semua buku yang ada di dalam file JSON
struct Book *get_books() {
    static struct Book books[100]; // Static untuk return pointer
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        return NULL; // Error loading books
    }

    return books;
}
