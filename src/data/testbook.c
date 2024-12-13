#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include "models/book.h"

// Fungsi utama
int main() {
    struct Book books[100];
    int count = 0;

    const char *filename = "model/books.json";

    // Load books from JSON
    if (load_books(filename, books, &count) == -1) {
        printf("Starting with an empty library\n");
    }

    // Display books
    printf("Books loaded: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d: %s by %s\n", books[i].id, books[i].title, books[i].author);
    }

    // Add a new book
    struct Book new_book = {1, "New Book", "Author Name", "Publisher Name", 2023, 250, "1st Edition", "Description here", "Available"};
    add_book(books, &count, new_book);

    struct Book new_book1 = {2, "New Book", "Author Name", "Publisher Name", 2023, 250, "1st Edition", "Description here", "Available"};
    add_book(books, &count, new_book1);

    // Update a book
    struct Book updated_book = {3, "Updated Book", "Updated Author", "Updated Publisher", 2024, 300, "2nd Edition", "Updated description", "Checked Out"};
    update_book(books, count, 3, updated_book);

    // Delete a book
    delete_book(books, &count, 1);

    // Save books to JSON
    save_books(filename, books, count);

    return 0;
}