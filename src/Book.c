#include <stdio.h>
#include <stddef.h> 
# include "Book.h"
void print_book(const Book *book) {
     if (book == NULL) {
        printf("Invalid book ID.\n");
        return;
    }
    printf("%-5d %-30s %-20s %-10s\n", 
                book->id_book, book->title, book->author,
                book->is_borrowed? "Brrowed": "Available");
}