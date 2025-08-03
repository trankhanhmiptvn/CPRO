#include <stdio.h>
#include <string.h>
#include "Book_Manager.h"

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

