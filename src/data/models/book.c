#include "book.h"
#include <string.h>

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
