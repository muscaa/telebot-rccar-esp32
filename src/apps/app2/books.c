#include "books.h"

#include "main.h"

#define CONFIG_DIR "library_books_tracking/"
#define CONFIG_FILE CONFIG_DIR "books.dat" // TODO mkdirs before fopen

private int books_length = 0;
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
    /*for (int i = 0; i < book.bookings_length; i++) {
        booking b = book.bookings[i];

        if (compare_date_time(date_from, time_from, b.date_from, b.time_from) == 0
                && compare_date_time(date_to, time_to, b.date_to, b.time_to) == 0) {
            return false;
        }
        if (compare_date_time(date_from, time_from, b.date_from, b.time_from) >= 0
                && compare_date_time(date_from, time_from, b.date_to, b.time_to) < 0) {
            return false;
        }
        if (compare_date_time(date_to, time_to, b.date_from, b.time_from) > 0
                && compare_date_time(date_to, time_to, b.date_to, b.time_to) <= 0) {
            return false;
        }
    }*/
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

        /*w.Int(book.bookings_length);
        for (int j = 0; j < book.bookings_length; j++) {
            booking booking = book.bookings[j];

            w.Byte(booking.date_from.day);
            w.Byte(booking.date_from.month);
            w.Int(booking.date_from.year);

            w.Byte(booking.time_from.hour);
            w.Byte(booking.time_from.minute);

            w.Byte(booking.date_to.day);
            w.Byte(booking.date_to.month);
            w.Int(booking.date_to.year);

            w.Byte(booking.time_to.hour);
            w.Byte(booking.time_to.minute);
        }*/
    }
    pop_save_config();
}

override
void load_books() {
    if (books_length != 0) { // free memory
        /*for (int i = 0; i < books_length; i++) {
            if (books[i].bookings_length != 0) {
                free(books[i].bookings);
            }
        }*/
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

        /*book.bookings_length = r.Int();
        book.bookings = malloc((book.bookings_length + 1) * sizeof(booking));
        for (int j = 0; j < book.bookings_length; j++) {
            booking booking;

            booking.date_from.day = r.Byte();
            booking.date_from.month = r.Byte();
            booking.date_from.year = r.Int();

            booking.time_from.hour = r.Byte();
            booking.time_from.minute = r.Byte();

            booking.date_to.day = r.Byte();
            booking.date_to.month = r.Byte();
            booking.date_to.year = r.Int();

            booking.time_to.hour = r.Byte();
            booking.time_to.minute = r.Byte();

            book.bookings[j] = booking;
        }*/

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
    /*int index = find_book(b.title);
    if (index == -1) return false;

    load_books();
    if (!is_book_available(b, date_from, time_from, date_to, time_to)) {
        return false;
    }

    books[index].bookings[books[index].bookings_length++] = (booking) { date_from, time_from, date_to, time_to };

    save_books();*/
    return true;
}

override
book get_book(int index) {
    return books[index];
}

override
bool book_exists(string title) {
    return find_book(title) != -1;
}