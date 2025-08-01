#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS  100
#define MAX_USERS  100

#include "Book.h"
#include "User.h"

typedef struct {
    Book books[MAX_BOOKS];
    int  book_count;
    User users[MAX_USERS];
    int  user_count;
} Library;

void init_library(Library *lib);

//User managerment
int add_user(Library *lib, const char *name);
int edit_user(Library *lib, const int id_user, const char *new_name);
int delete_user(Library *lib, const int id_user);
int list_users(const Library *lib);

//Book managerment
int add_book(Library *lib, const char *title, const char *author);
int edit_book(Library *lib, const int id_book, const char *new_title, const char *new_author);
int delete_book(Library *lib, const int id_book);
int list_books(const Library *lib);

//Borrow/Return
int borrow_book(Library *lib, const int id_user, const int id_book);
int return_book(Library *lib, const int id_user, const int id_book);

// Search
int search_books_by_title(const Library *lib, const char *title);
int search_books_by_author(const Library *lib, const char *author);
int show_user_info(Library *lib, int id_user);

#endif