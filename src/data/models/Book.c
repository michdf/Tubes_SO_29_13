/**
 * @file Book.c
 * @author Micho Dhani Firmansyah (micho.dhani.tif423@polban.ac.id)
 * @brief Implementasi ADT untuk manajemen data buku dalam sistem perpustakaan
 * @date 2024-12-14
 */

#include "Book.h"
#include "../../helper/Utils.h"
#include <json-c/json.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book* book_constructor(int id, const char* title, const char* author,
                            const char* publisher, int year, int pages,
                            const char* edition, const char* description,
                            const char* status, int* error) {
    if (error) *error = BOOK_SUCCESS;
    
    if (!title || !author || !publisher || !edition || !description || !status) {
        if (error) *error = BOOK_ERROR_NULL_POINTER;
        return NULL;
    }

    struct Book* new_book = (struct Book*)malloc(sizeof(struct Book));
    if (!new_book) {
        if (error) *error = BOOK_ERROR_MEMORY;
        return NULL;
    }

    new_book->id = id;
    
    if (!safe_strncpy(new_book->title, title, MAX_TITLE_LEN) ||
        !safe_strncpy(new_book->author, author, MAX_AUTHOR_LEN) ||
        !safe_strncpy(new_book->publisher, publisher, MAX_PUBLISHER_LEN) ||
        !safe_strncpy(new_book->edition, edition, MAX_EDITION_LEN) ||
        !safe_strncpy(new_book->description, description, MAX_DESC_LEN) ||
        !safe_strncpy(new_book->status, status, MAX_STATUS_LEN)) {
        
        free(new_book);
        if (error) *error = BOOK_ERROR_INVALID_INPUT;
        return NULL;
    }

    new_book->year = year;
    new_book->pages = pages;

    return new_book;
}

void book_destructor(struct Book* book) {
    free(book);
}

bool validate_book(const struct Book* book, int* error) {
    if (!book) {
        if (error) *error = BOOK_ERROR_NULL_POINTER;
        return false;
    }

    if (book->id <= 0 || book->year <= 0 || book->pages <= 0 ||
        strlen(book->title) == 0 || strlen(book->author) == 0 ||
        strlen(book->publisher) == 0 || strlen(book->status) == 0) {
        if (error) *error = BOOK_ERROR_INVALID_INPUT;
        return false;
    }

    if (error) *error = BOOK_SUCCESS;
    return true;
}

// Mencetak detail buku ke stdout
void print_book(const struct Book *book) {
    if (book == NULL) return;

    printf("ID: %d\n", book->id);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Publisher: %s\n", book->publisher);
    printf("Year: %d\n", book->year);
    printf("Pages: %d\n", book->pages);
    printf("Edition: %s\n", book->edition);
    printf("Description: %s\n", book->description);
    printf("Status: %s\n", book->status);
    printf("-----------------------\n");
}

// Membandingkan dua buku berdasarkan ID (return 1 jika sama, 0 jika berbeda)
int compare_book_by_id(const struct Book* a, const struct Book* b) {
    if (!a || !b) return 0;
    if (a->id < b->id) return -1;
    if (a->id > b->id) return 1;
    return 0;
}

// Membuat instance buku dari data input
struct Book create_book(int id, const char *title, const char *author, const char *publisher, 
                        int year, int pages, const char *edition, const char *description, const char *status) {
    struct Book new_book;

    new_book.id = id;
    strncpy(new_book.title, title, sizeof(new_book.title));
    strncpy(new_book.author, author, sizeof(new_book.author));
    strncpy(new_book.publisher, publisher, sizeof(new_book.publisher));
    new_book.year = year;
    new_book.pages = pages;
    strncpy(new_book.edition, edition, sizeof(new_book.edition));
    strncpy(new_book.description, description, sizeof(new_book.description));
    strncpy(new_book.status, status, sizeof(new_book.status));

    return new_book;
}

char* book_to_json(const struct Book* book){
    if (!book) return NULL;

    json_object *bookJsonObject = json_object_new_object();
    json_object_object_add(bookJsonObject, "id", json_object_new_int(book->id));
    json_object_object_add(bookJsonObject, "title", json_object_new_string(book->title));
    json_object_object_add(bookJsonObject, "author", json_object_new_string(book->author));
    json_object_object_add(bookJsonObject, "publisher", json_object_new_string(book->publisher));
    json_object_object_add(bookJsonObject, "year", json_object_new_int(book->year));
    json_object_object_add(bookJsonObject, "pages", json_object_new_int(book->pages));
    json_object_object_add(bookJsonObject, "edition", json_object_new_string(book->edition));
    json_object_object_add(bookJsonObject, "description", json_object_new_string(book->description));
    json_object_object_add(bookJsonObject, "status", json_object_new_string(book->status));

    return strdup(json_object_to_json_string(bookJsonObject));
}