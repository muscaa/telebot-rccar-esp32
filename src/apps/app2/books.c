#include "books.h"

#define CONFIG_DIR "library_books_tracking/"
#define CONFIG_FILE CONFIG_DIR "books.dat" // TODO mkdirs before fopen

/*private int books_length = 0;
private book* books;

private int filtered_books_length = -1;
private book* filtered_books;

private bool init_filter() {
    if (filtered_books_length == -1) {
        filtered_books = malloc(books_length * sizeof(book));
        memcpy(filtered_books, books, books_length * sizeof(book));
        filtered_books_length = books_length;
        return true;
    }
    return false;
}

private int find_book(string title) {
    for (int i = 0; i < books_length; i++) {
        if (strcmp(books[i].title, title) == 0) return i;
    }
    return -1;
}

private bool is_book_available(book book, date date_from, time time_from, date date_to, time time_to) {
    return true;
}

private void save_books() {
    string parent = file_parent(CONFIG_FILE);
    if (parent != NULL) dir_create(parent);

    config_writer w = push_save_config(CONFIG_FILE);
    w.Int(books_length);
    for (int i = 0; i < books_length; i++) {
        book book = books[i];

        w.LenString(book.title);
        w.LenString(book.author);
        w.StringArray(book.types);
    }
    pop_save_config();
}

override
void load_books() {
    if (books_length != 0) { // free memory
        free(books);
        books_length = 0;
    }
    if (!file_exists(CONFIG_FILE)) {
        books = malloc((books_length + 1) * sizeof(book));
        return;
    }

    config_reader r = push_load_config(CONFIG_FILE);
    books_length = r.Int();
    books = malloc((books_length + 1) * sizeof(book));
    for (int i = 0; i < books_length; i++) {
        book book;

        book.title = r.LenString();
        book.author = r.LenString();
        book.types = r.StringArray();

        books[i] = book;
    }
    pop_load_config();
}

override
int get_books_length() {
    return books_length;
}

override
bool add_book(string title, string author, string_array types) {
    load_books();
    if (book_exists(title)) {
        return false;
    }

    book book;
    book.title = title;
    book.author = author;
    book.types = types;
    books[books_length++] = book;

    save_books();
    return true;
}

override
void delete_book(book b) {
    int index = find_book(b.title);
    if (index == -1) return;

    memcpy(&books[index], &books[index + 1], (books_length - index - 1) * sizeof(book));
    books_length--;
    books = realloc(books, books_length * sizeof(book));
    save_books();
}

override
bool book_book(book b, date date_from, time time_from, date date_to, time time_to) {
    return true;
}

override
book get_book(int index) {
    return books[index];
}

override
bool book_exists(string title) {
    return find_book(title) != -1;
}*/
