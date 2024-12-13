#include "book.h"
#include <string.h>
#include <stdlib.h>

// Membuat instance buku
struct Book *book_constructor(int id, const char *title, const char *author, const char *publisher, 
                              int year, int pages, const char *edition, const char *description, const char *status) {
    struct Book *new_book = (struct Book *)malloc(sizeof(struct Book));

    if (new_book == NULL) return NULL;

    new_book->id = id;
    strncpy(new_book->title, title, sizeof(new_book->title));
    strncpy(new_book->author, author, sizeof(new_book->author));
    strncpy(new_book->publisher, publisher, sizeof(new_book->publisher));
    new_book->year = year;
    new_book->pages = pages;
    strncpy(new_book->edition, edition, sizeof(new_book->edition));
    strncpy(new_book->description, description, sizeof(new_book->description));
    strncpy(new_book->status, status, sizeof(new_book->status));

    return new_book;
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

// Validasi data buku (return 1 jika valid, 0 jika tidak)
int validate_book(const struct Book *book) {
    if (book == NULL) return 0;

    // Contoh validasi sederhana
    if (book->id <= 0 || book->year <= 0 || book->pages <= 0) return 0;
    if (strlen(book->title) == 0 || strlen(book->author) == 0) return 0;

    return 1; // Valid
}

// Membandingkan dua buku berdasarkan ID (return 1 jika sama, 0 jika berbeda)
int compare_book_by_id(const struct Book *a, const struct Book *b) {
    if (a == NULL || b == NULL) return 0;
    return a->id == b->id;
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

// Fungsi konversi struct book ke JSON (struct book dalam bentuk array dan akan diubah ke JSON)
struct json_object *books_to_json_array(const struct Book **book) {
    struct json_object *book_array = json_object_new_array();
    for (int i = 0; book[i] != NULL; i++) {
        struct json_object *book_obj = json_object_new_object();
        json_object_object_add(book_obj, "id", json_object_new_int(book[i]->id));
        json_object_object_add(book_obj, "title", json_object_new_string(book[i]->title));
        json_object_object_add(book_obj, "author", json_object_new_string(book[i]->author));
        json_object_object_add(book_obj, "publisher", json_object_new_string(book[i]->publisher));
        json_object_object_add(book_obj, "year", json_object_new_int(book[i]->year));
        json_object_object_add(book_obj, "pages", json_object_new_int(book[i]->pages));
        json_object_object_add(book_obj, "edition", json_object_new_string(book[i]->edition));
        json_object_object_add(book_obj, "description", json_object_new_string(book[i]->description));
        json_object_object_add(book_obj, "status", json_object_new_string(book[i]->status));
        json_object_array_add(book_array, book_obj);
    }

    return book_array;
}
