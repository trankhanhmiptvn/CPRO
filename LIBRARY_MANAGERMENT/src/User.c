#include <stdio.h>
#include <stddef.h>
#include "User.h"

void print_user(const User *u){
    if (u == NULL) {
        printf("Invalid user ID.\n");
        return;
    }
    printf("%-5d %-30s ",u->id_user, u->name);
    if(u->borrowed_count == 0) {
        printf("None.\n");
    }
    else {
        for(int j = 0; j < u->borrowed_count; j++){
            printf("%d", u->borrowed_books[j]);
            if(j < u->borrowed_count - 1) { printf(", "); }
            else { printf("\n"); }
        }
    }
}

