#ifndef USER_H
#define USER_H

#define NAME_LENGTH  100
#define MAX_BORROWED 2

typedef struct {
    char name[NAME_LENGTH];
    int  id_user;
    int borrowed_books[MAX_BORROWED]; // contain id borrowed books
    int borrowed_count;
} User;

void print_user(const User *u);

#endif