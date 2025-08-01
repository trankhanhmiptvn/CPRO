#include <stdio.h>
#include <string.h>
#include "Library.h"

void init_library(Library *lib){
    lib->book_count = 0;
    lib->user_count = 0;
}


//User managerment
int add_user(Library *lib, const char *name) {
    if(lib->user_count >= MAX_USERS) {
        printf("User list is full. Cannot add more user.\n");
        return -1;
    }
    else if(!name || strlen(name) == 0) {
        printf("The input information is not correct.\n");
        return -2;
    }
    else {
        User *u = &lib->users[lib->user_count];
        strncpy(u->name, name, NAME_LENGTH - 1);
        u->name[NAME_LENGTH-1] = '\0';
        u->id_user = lib->user_count + 100;
        lib->user_count++;
        u->borrowed_count = 0;
        printf("Add user %s to the library.\n", name);
        return u->id_user;
    }
}
int edit_user(Library *lib, const int id_user, const char *new_name) {
    if(id_user < 0 || id_user >= lib->user_count) {
        printf("Invalite user id. Cannot edit the user.\n");
        return -1;
    }
    else if(!new_name || strlen(new_name) == 0) {
        printf("The input information is not correct.\n");
        return -2;
    }
    else {
        User *u = &lib->users[id_user];
        strncpy(u->name, new_name, NAME_LENGTH - 1);
        u->name[NAME_LENGTH-1] = '\0';
        printf("The user has been update\n");
        return 0;
    }
}
int delete_user(Library *lib, const int id_user) {
    if(id_user < 0 || id_user >= lib->user_count) {
        printf("Invalite user id. Cannot delete the user.\n");
        return -1;
    }
    else {
        for(int i = id_user; i < lib->user_count - 1; i++) {
            lib->users[i] = lib->users[i+1];
        }
        lib->user_count--;
        printf("The user has been delete\n");
        return 0;
    }
}
int list_users(const Library *lib) {
    if(lib->user_count == 0) {
        printf("No users found.\n");
        return -1;
    }
    else {
        printf("List of users in the library:\n");
        printf("%-5s %-30s %-s\n", "ID", "Name", "Books borrowed");
        printf("----------------------------------------------------------\n");
        for(int i = 0; i < lib->user_count; i++){
            const User *u = &lib->users[i];
            print_user(u);
        }
        return 0;
    }
}

//Book managerment
int add_book(Library *lib, const char *title, const char *author) {
    if(lib->book_count >= MAX_BOOKS) {
        printf("Book list is full. Cannot add more book.\n");
        return -1;
    }
    else if(!title || !author || strlen(title) == 0 || strlen(author) == 0) {
        printf("The input information is not correct.\n");
        return -2;
    }
    else {
        Book *b = &lib->books[lib->book_count];
        strncpy(b->title, title, TITLE_LENGTH - 1);
        b->title[TITLE_LENGTH-1] = '\0';
        strncpy(b->author, author, AUTHOR_LENGTH - 1);
        b->author[AUTHOR_LENGTH-1] = '\0';
        b->id_book = lib->book_count + 100;
        b->is_borrowed = 0;
        lib->book_count++;
        printf("Add book with title %s, author %s to the library.\n", 
            title, author);
        return b->id_book;
    }
}
int edit_book(Library *lib, const int id_book, const char *new_title, const char *new_author) {
    int index_book = -1;
    for(int i = 0; i < lib->book_count; i++) {
        if(lib->books[i].id_book == id_book) {
            index_book = i;
            break;
        }
    }
    if(index_book == -1) {
        printf("Invalide book id. Cannot edit book.\n");
        return -1;
    }
    else if(!new_title || !new_author || strlen(new_title) == 0 || strlen(new_author) == 0) {
        printf("The input information is not correct.\n");
        return -2;
    }
    else {
        Book *b = &lib->books[index_book];
        printf("The book beforupdating:\n");
        print_book(b);
        strncpy(b->title, new_title, TITLE_LENGTH - 1);
        b->title[TITLE_LENGTH-1] = '\0';
        strncpy(b->author, new_author, AUTHOR_LENGTH - 1);
        b->author[AUTHOR_LENGTH-1] = '\0';
        printf("The book has been update.\n");
        print_book(b);
        return 0;
    }
}
int delete_book(Library *lib, const int id_book) {
    int index_book = -1;
    for(int i = 0; i < lib->book_count; i++) {
        if(lib->books[i].id_book == id_book) {
            index_book = i;
            break;
        }
    }
    if(index_book == -1) {
        printf("Invalide book id. Cannot edit book.\n");
        return -1;
    }
    else {
        printf("The book %s has been delete.\n", lib->books[index_book].title);
        for(int i = index_book; i < lib->book_count - 1; i++){
            lib->books[i] = lib->books[i+1];
        }
        lib->book_count--; 
        return 0;
    }
    
}
int list_books(const Library *lib){
    if(lib->book_count == 0) {
        printf("No books found.\n");
        return -1;
    }
    else {
        printf("List of books in the library:\n");
        printf("%-5s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
        printf("----------------------------------------------------------\n");
        for(int i = 0; i < lib->book_count; i++){
            const Book *b = &lib->books[i];
             print_book(b);
        }
        return 0;
    }
}

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

// Search
int search_books_by_title(const Library *lib, const char *title) {
    if(!lib || !title || strlen(title) == 0){
        printf("Invalid library or title\n");
        return -1;
    }
    int found = 0;
    for(int i = 0; i < lib->book_count; i++){
        if(strstr(lib->books[i].title, title) != NULL) {
            const Book *b = &lib->books[i];
            printf("%-5s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
            print_book(b);
            found = 1;
            break;
        }
    }
    if(!found) {
        printf("No book found.\n");
        return -2;
    }
    return 0;
}
int search_books_by_author(const Library *lib, const char *author) {
    if(!lib || !author || strlen(author) == 0){
        printf("Invalid library or author\n");
        return -1;
    }
    int found = 0;
    for(int i = 0; i < lib->book_count; i++){
        if(strstr(lib->books[i].author, author) != NULL) {
            const Book *b = &lib->books[i];
            printf("%-5s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
            print_book(b);
            found = 1;
            break;
        }
    }
    if(!found) {
        printf("No book found.\n");
        return -2;
    }
    return 0;
}

int show_user_info(Library *lib, int id_user){
    int index_user = -1;
    for(int i = 0; i < lib->user_count; i++){
        if(lib->users[i].id_user == id_user){
            index_user = i;
            break;
        }
    }
    if(lib == NULL || index_user == -1) {
        printf("Invalid user id.\n");
        return -1;
    }
    User *u = &lib->users[index_user];
    printf("User ID:           %d\n", u->id_user);
    printf("Name:              %s\n", u->name);
    printf("Borrowed books:    %d\n", u->borrowed_count);
    if(u->borrowed_count == 0) {
        printf("No books borrowed.\n");
        return 0;
    }
    printf("%-5s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
    for(int i = 0; i < u->borrowed_count; i++) {
        for(int j = 0; j < lib->book_count; j++){
            if(u->borrowed_books[i] == lib->books[j].id_book){
                Book *b = &lib->books[j];
                print_book(b);
            }
            
        }
        
    }
    return 0;
}