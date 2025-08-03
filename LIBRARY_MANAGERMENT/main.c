#include <stdio.h>
#include <string.h>
#include "Library.h"

int main() {
    Library lib;
    init_library(&lib);

    printf("=== Library System Demo ===\n\n");
    
    printf("\n-- Thêm người dùng --\n");
    int u1 = add_user(&lib, "Tran Minh Khang");
    int u2 = add_user(&lib, "Nguyen Minh Triet");
    

    printf("\n-- Thêm sách --\n");
    int b1 = add_book(&lib, "Clean Code", "Robert C. Martin");
    int b2 = add_book(&lib, "The Pragmatic Programmer", "Andrew Hunt");
    int b3 = add_book(&lib, "Introduction to Linux", "Torvalds");
    
    printf("\n-- Danh sách người dùng --\n");
    list_users(&lib);

    printf("\n-- Danh sách sách --\n");
    list_books(&lib);

    printf("\n-- Mượn sách --\n");
    borrow_book(&lib, u1, b1);
    borrow_book(&lib, u1, b2);
    borrow_book(&lib, u1, b3);
    borrow_book(&lib, u2, b3);
    borrow_book(&lib, u2, b1);

    // Hiển thị thông tin người dùng
    printf("\n-- Thông tin người dùng --\n");
    show_user_info(&lib, u1);

    printf("\n-- Thông tin người dùng --\n");
    show_user_info(&lib, u2);
    
    
    printf("\n-- Trả sách --\n");
    return_book(&lib, u1, b1);

    printf("\n-- Thông tin người dùng sau khi trả sách --\n");
    show_user_info(&lib, u1);

    #if 1
  
    printf("\n-- Tìm kiếm sách theo tiêu đề 'Linux' --\n");
    search_books_by_title(&lib, "Linux");

    printf("\n-- Tìm kiếm sách theo tiêu đề 'Martin' --\n");
    search_books_by_author(&lib, "Martin");

    printf("\n-- Sửa sách --\n");
    edit_book(&lib, b1, "Clean Code part 2", "Robert C. Martin");

    printf("\n-- Xóa sách --\n");
    delete_book(&lib, b1);

    printf("\n-- Danh sách sách sau xóa--\n");
    list_books(&lib);
    #endif
    return 0;
}
