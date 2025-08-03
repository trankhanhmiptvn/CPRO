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

#endif