/**
 * @file DataHandler.h
 * @author Micho Dhani Firmansyah (michodhani01@gmail.com)
 * @brief Implementasi ADT untuk mengelola data buku
 * @date 2024-12-14
 */

#include "DataHandler.h"
#include "../../config/ServerConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <cjson/cJSON.h>

static int lock_file(int fd) {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire lock");
        return -1;
    }
    return 0;
}

static int unlock_file(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release lock");
        return -1;
    }
    return 0;
}

int load_books_from_json(struct Book *books) {
    int fd = open(BOOKS_DATA_FILE, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    char buffer[8192] = {0};
    ssize_t read_size = read(fd, buffer, sizeof(buffer) - 1);
    if (read_size == -1) {
        perror("Failed to read file");
        unlock_file(fd);
        close(fd);
        return -1;
    }

    buffer[read_size] = '\0';

    cJSON *parsed_json = cJSON_Parse(buffer);
    if (!parsed_json || read_size == 0) {
        fprintf(stderr, "Invalid or empty JSON. Resetting to default.\n");
        const char *empty_json_object = "[]";
        if (ftruncate(fd, 0) == -1 || lseek(fd, 0, SEEK_SET) == -1 || 
            write(fd, empty_json_object, strlen(empty_json_object)) == -1) {
            perror("Failed to reset JSON file");
            unlock_file(fd);
            close(fd);
            return -1;
        }
        lseek(fd, 0, SEEK_SET);
        parsed_json = cJSON_Parse(empty_json_object);
    }

    if (!parsed_json) {
        fprintf(stderr, "Failed to parse JSON\n");
        close(fd);
        return -1;
    }

    int n_books = cJSON_GetArraySize(parsed_json);
    for (int i = 0; i < n_books; i++) {
        cJSON *book_obj = cJSON_GetArrayItem(parsed_json, i);
        books[i].id = cJSON_GetObjectItem(book_obj, "id")->valueint;
        strncpy(books[i].title, cJSON_GetObjectItem(book_obj, "title")->valuestring, sizeof(books[i].title));
        strncpy(books[i].author, cJSON_GetObjectItem(book_obj, "author")->valuestring, sizeof(books[i].author));
        strncpy(books[i].publisher, cJSON_GetObjectItem(book_obj, "publisher")->valuestring, sizeof(books[i].publisher));
        books[i].year = cJSON_GetObjectItem(book_obj, "year")->valueint;
        books[i].pages = cJSON_GetObjectItem(book_obj, "pages")->valueint;
        strncpy(books[i].edition, cJSON_GetObjectItem(book_obj, "edition")->valuestring, sizeof(books[i].edition));
        strncpy(books[i].description, cJSON_GetObjectItem(book_obj, "description")->valuestring, sizeof(books[i].description));
        strncpy(books[i].status, cJSON_GetObjectItem(book_obj, "status")->valuestring, sizeof(books[i].status));
    }

    cJSON_Delete(parsed_json);

    close(fd);
    return n_books;
}

int save_books_to_json(struct Book *books, int count) {
    int fd = open(BOOKS_DATA_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    cJSON *book_array = cJSON_CreateArray();
    for (int i = 0; i < count; i++) {
        cJSON *book_obj = cJSON_CreateObject();
        cJSON_AddNumberToObject(book_obj, "id", books[i].id);
        cJSON_AddStringToObject(book_obj, "title", books[i].title);
        cJSON_AddStringToObject(book_obj, "author", books[i].author);
        cJSON_AddStringToObject(book_obj, "publisher", books[i].publisher);
        cJSON_AddNumberToObject(book_obj, "year", books[i].year);
        cJSON_AddNumberToObject(book_obj, "pages", books[i].pages);
        cJSON_AddStringToObject(book_obj, "edition", books[i].edition);
        cJSON_AddStringToObject(book_obj, "description", books[i].description);
        cJSON_AddStringToObject(book_obj, "status", books[i].status);
        cJSON_AddItemToArray(book_array, book_obj);
    }

    char *json_str = cJSON_Print(book_array);
    write(fd, json_str, strlen(json_str));
    free(json_str);
    cJSON_Delete(book_array);

    close(fd);
    return 0;
}

int add_book(struct Book new_book) {
    int fd = open(BOOKS_DATA_FILE, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    if (lock_file(fd) == -1) {
        close(fd);
        return -1;
    }

    struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        unlock_file(fd);
        close(fd);
        return -1;
    }

    books[book_count] = new_book;
    book_count++;

    int result = save_books_to_json(books, book_count);

    unlock_file(fd);
    close(fd);

    return result;
}

int update_book(int id, struct Book updated_book) {
    int fd = open(BOOKS_DATA_FILE, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    if (lock_file(fd) == -1) {
        close(fd);
        return -1;
    }

    struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        return -1;
    }

    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            int original_id = books[i].id;
            books[i] = updated_book;
            books[i].id = original_id;
            found = 1;
            break;
        }
    }

    if (!found) {
        unlock_file(fd);
        close(fd);
        return -1;
    }

    int result = save_books_to_json(books, book_count);

    unlock_file(fd);
    close(fd);
    return result;
}

int delete_book(int id) {
    int fd = open(BOOKS_DATA_FILE, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return -1;
    }

    if (lock_file(fd) == -1) {
        close(fd);
        return -1;
    }

    struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        return -1;
    }

    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < book_count - 1; j++) {
                books[j] = books[j + 1];
            }
            book_count--;
            break;
        }
    }

    if (!found) {
        unlock_file(fd);
        close(fd);
        return -1;
    }

    int result = save_books_to_json(books, book_count);

    unlock_file(fd);
    close(fd);
    return result;
}

struct Book *get_book_by_id(int id) {
    int fd = open(BOOKS_DATA_FILE, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return NULL;
    }

    if (lock_file(fd) == -1) {
        close(fd);
        return NULL;
    }

    static struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        unlock_file(fd);
        close(fd);
        return NULL;
    }

    struct Book *result = NULL;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            result = &books[i];
            break;
        }
    }

    unlock_file(fd);
    close(fd);
    return result;
}

struct Book *get_books() {
    int fd = open(BOOKS_DATA_FILE, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return NULL;
    }

    if (lock_file(fd) == -1) {
        close(fd);
        return NULL;
    }

    static struct Book books[100];
    int book_count = load_books_from_json(books);
    if (book_count == -1) {
        unlock_file(fd);
        close(fd);
        return NULL;
    }

    unlock_file(fd);
    close(fd);
    return books;
}