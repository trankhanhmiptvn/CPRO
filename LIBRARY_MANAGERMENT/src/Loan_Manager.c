#include <stdio.h>
#include <string.h>
#include "Library.h"

//Borrow/Return
int borrow_book(Library *lib, const int id_user, const int id_book) {
    //Find user
    int index_user = -1;
    for(int i = 0; i < lib->user_count; i++) {
        if(lib->users[i].id_user == id_user) { 
            index_user = i;
            break;
        }
    }
    if( index_user == -1) {
        printf("The user not found.\n");
        return -1;
    }

    //Find book
    int index_book = -1;
    for(int i = 0; i < lib->book_count; i++) {
        if(lib->books[i].id_book == id_book) {
            index_book = i;
            break;
        }
    }
    if(index_book == -1) {
        printf("The book not found.\n");
        return -2;
    }

    Book *b = &lib->books[index_book];
    User *u = &lib->users[index_user];
    
    //Test status of the book
    if(b->is_borrowed == 1) {
        printf("The book %s is not avilable for brrowing.\n", b->title);
        return -3;
    }

    //Test the user's borrowing limit
    if(u->borrowed_count >= MAX_BORROWED){
        printf("The user %s has reached the borrowing limit.\n", u->name);
        return -4;
    }

    //Add the book to the list borrowed books of the user
    u->borrowed_books[u->borrowed_count] = id_book;
    b->is_borrowed = 1;
    u->borrowed_count++;
    printf("%s borrowed the book %s successfully.\n", u->name, b->title); 
    return 0;
}

int return_book(Library *lib, const int id_user, const int id_book){
    //Find user
    int index_user = -1;
    for(int i = 0; i < lib->user_count; i++) {
        if(lib->users[i].id_user == id_user) { 
            index_user = i;
            break;
        }
    }
    if( index_user == -1) {
        printf("The user not found.\n");
        return -1;
    }

    //Find book
    int index_book = -1;
    for(int i = 0; i < lib->book_count; i++) {
        if(lib->books[i].id_book == id_book) {
            index_book = i;
            break;
        }
    }
    if(index_book == -1) {
        printf("The book not found.\n");
        return -2;
    }

    Book *b = &lib->books[index_book];
    User *u = &lib->users[index_user];
    
    //Test is the book  in the list borrowed books of the user
    int index_borowed_book = -1;
    for(int i = 0; i < u->borrowed_count; i++) {
        if(u->borrowed_books[i] ==  id_book) {
            index_borowed_book = i;
            break;
        }
    }
    if(index_borowed_book == -1) {
        printf("The user didnot borrow the book.\n");
        return -3;
    }
     
    //Remove the book from the list borrowed books of the user
    for(int i = index_borowed_book; i < u->borrowed_count - 1; i++) {
        u->borrowed_books[i] = u->borrowed_books[i+1];
    }
    u->borrowed_count--;
    b->is_borrowed = 0;
    printf("The user %s returned the book %s successfully.\n", u->name, b->title); 
    return 0;
}

