#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "type.h"

// Khởi tạo trạng thái hệ thống
void init_system_state();

// Hàm gọi định kỳ để cập nhật hệ thống (FSM logic chính)
void update_system_state();

// Xử lý khi nút chuyển chế độ được nhấn
void handle_mode_button();

// Xử lý khi nút tưới thủ công được nhấn
void handle_manual_pump_button();

void scan_input();

// Các hàm getter trạng thái
system_mode_t get_current_mode();
pump_state_t get_current_pump_state();
led_status_t get_current_led_status();

//Lấy thời gian hệ thống
unsigned long millis();

//Hàm hiển thị qua uart console 
void monitor_and_display_status();

#endif
