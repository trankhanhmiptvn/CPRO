#include <stdio.h>
#include "button.h"


// Cờ báo hiệu nút đã nhấn
volatile bool mode_button_pressed = false;
volatile bool pump_button_pressed = false;

void update_buttons_from_keyboard() {
    int mode_input, pump_input;
    printf("Nhấn nút Mode? (1 = Có, 0 = Không): ");
    scanf("%d", &mode_input);
    mode_button_pressed = (mode_input == 1);

    printf("Nhấn nút Pump? (1 = Có, 0 = Không): ");
        scanf("%d", &pump_input);
        pump_button_pressed = (pump_input == 1);
}

// Khởi tạo chân nút và ngắt
void init_buttons() {
    printf("[Button] Khởi tạo các nút bấm.\n");
}

// Lấy và xoá cờ mode_button
bool get_and_clear_mode_button_flag() {
    bool pressed = mode_button_pressed;
    mode_button_pressed = false;
    return pressed;
}

// Lấy và xoá cờ pump_button
bool get_and_clear_pump_button_flag() {
    bool pressed = pump_button_pressed;
    pump_button_pressed = false;
    return pressed;
}
