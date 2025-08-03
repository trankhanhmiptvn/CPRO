#include <stdio.h>
#include <string.h>
#include "User_Manager.h"

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