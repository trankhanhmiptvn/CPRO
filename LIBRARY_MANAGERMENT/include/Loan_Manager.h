#ifndef LOAN_MANAGER_H
#define LOAN_MANAGER_H

#include "Library.h"

int borrow_book(Library *lib, const int id_user, const int id_book);
int return_book(Library *lib, const int id_user, const int id_book);

#endif