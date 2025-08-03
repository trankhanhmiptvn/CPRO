#ifndef BOOK_H
#define BOOK_H

#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 100

typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int  id_book;
    int  is_borrowed; //0: available; 1: borrowed 
} Book;


void print_book(const Book *book);

#endif