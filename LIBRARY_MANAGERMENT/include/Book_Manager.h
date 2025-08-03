#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H


#include "Library.h"
#include "Book.h"

//Book managerment
int add_book(Library *lib, const char *title, const char *author);
int edit_book(Library *lib, const int id_book, const char *new_title, const char *new_author);
int delete_book(Library *lib, const int id_book);
int list_books(const Library *lib);
// Search
int search_books_by_title(const Library *lib, const char *title);
int search_books_by_author(const Library *lib, const char *author);

#endif