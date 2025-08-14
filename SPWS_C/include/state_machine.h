#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "type.h"

//Cấu hình đầu vào hệ thống, nhiệt độ, độ ẩm, chế độ hoạt động, trang thái bơm
void simulate_system_input();

// Lấy trạng thái hệ thống
void get_system_state();

//Điều  khiển bơm, led theo chế độ hoạt động và nhiệt độ, độ ẩm
void control_system_state();
//Lấy thời gian hệ thống
unsigned long millis();

//Hàm hiển thị qua uart console 
void monitor_and_display_status();

#endif
