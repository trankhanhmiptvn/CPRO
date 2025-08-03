#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#define NAME_LENGTH  100
#define MAX_BORROWED 2

#include "Library.h"
#include "User.h"

int add_user(Library *lib, const char *name);
int edit_user(Library *lib, const int id_user, const char *new_name);
int delete_user(Library *lib, const int id_user);
int list_users(const Library *lib);
int show_user_info(Library *lib, int id_user);

#endif
