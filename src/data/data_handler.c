#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>


// Struktur Book
struct Book {
    int id;
    char title[100];
    char author[100];
    char publisher[100];
    int year;
    int pages;
    char edition[100];
    char description[1000];
    char status[100];
};

// Fungsi untuk membaca file JSON dan memetakan ke array struct Book
int load_books(const char *filename, struct Book *books, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);
    data[length] = '\0';

    cJSON *json = cJSON_Parse(data);
    free(data);
    if (!json) {
        printf("Error parsing JSON\n");
        return -1;
    }

    cJSON *book_array = cJSON_GetObjectItem(json, "books");
    if (!cJSON_IsArray(book_array)) {
        printf("Invalid JSON format\n");
        cJSON_Delete(json);
        return -1;
    }

    int index = 0;
    cJSON *book_item;
    cJSON_ArrayForEach(book_item, book_array) {
        books[index].id = cJSON_GetObjectItem(book_item, "id")->valueint;
        strcpy(books[index].title, cJSON_GetObjectItem(book_item, "title")->valuestring);
        strcpy(books[index].author, cJSON_GetObjectItem(book_item, "author")->valuestring);
        strcpy(books[index].publisher, cJSON_GetObjectItem(book_item, "publisher")->valuestring);
        books[index].year = cJSON_GetObjectItem(book_item, "year")->valueint;
        books[index].pages = cJSON_GetObjectItem(book_item, "pages")->valueint;
        strcpy(books[index].edition, cJSON_GetObjectItem(book_item, "edition")->valuestring);
        strcpy(books[index].description, cJSON_GetObjectItem(book_item, "description")->valuestring);
        strcpy(books[index].status, cJSON_GetObjectItem(book_item, "status")->valuestring);
        index++;
    }

    *count = index;
    cJSON_Delete(json);
    return 0;
}

// Fungsi untuk menyimpan array struct Book ke file JSON
void save_books(const char *filename, struct Book *books, int count) {
    cJSON *json = cJSON_CreateObject();
    cJSON *book_array = cJSON_CreateArray();

    for (int i = 0; i < count; i++) {
        cJSON *book_item = cJSON_CreateObject();
        cJSON_AddNumberToObject(book_item, "id", books[i].id);
        cJSON_AddStringToObject(book_item, "title", books[i].title);
        cJSON_AddStringToObject(book_item, "author", books[i].author);
        cJSON_AddStringToObject(book_item, "publisher", books[i].publisher);
        cJSON_AddNumberToObject(book_item, "year", books[i].year);
        cJSON_AddNumberToObject(book_item, "pages", books[i].pages);
        cJSON_AddStringToObject(book_item, "edition", books[i].edition);
        cJSON_AddStringToObject(book_item, "description", books[i].description);
        cJSON_AddStringToObject(book_item, "status", books[i].status);
        cJSON_AddItemToArray(book_array, book_item);
    }

    cJSON_AddItemToObject(json, "books", book_array);

    char *data = cJSON_Print(json);
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error writing to file");
        free(data);
        cJSON_Delete(json);
        return;
    }
    fprintf(file, "%s", data);
    fclose(file);

    free(data);
    cJSON_Delete(json);
}

// Fungsi untuk menambahkan buku baru
void add_book(struct Book *books, int *count, struct Book new_book) {
    books[*count] = new_book;
    (*count)++;
}

// Fungsi untuk menghapus buku berdasarkan ID
void delete_book(struct Book *books, int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (books[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                books[j] = books[j + 1];
            }
            (*count)--;
            return;
        }
    }
    printf("Book with ID %d not found\n", id);
}

// Fungsi untuk mengupdate buku berdasarkan ID
void update_book(struct Book *books, int count, int id, struct Book updated_book) {
    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            books[i] = updated_book;
            return;
        }
    }
    printf("Book with ID %d not found\n", id);
}


