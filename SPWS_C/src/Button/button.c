#include <stdio.h>
#include "button.h"


// Cờ báo hiệu nút đã nhấn
volatile bool mode_button_pressed;
volatile bool pump_button_pressed;
    

// Khởi tạo chân nút và ngắt
void init_buttons() {
    printf("[Button] Khởi tạo các nút bấm.\n");
    mode_button_pressed = false;
    pump_button_pressed = false;
}

void simulate_mode_pressed() {
    int mode_input;
    printf("Nhấn nút Mode? (1 = Có, 0 = Không): ");
    scanf("%d", &mode_input);
    mode_button_pressed = (mode_input == 1);
}
void simulate_pump_pressed() {
    int pump_input;
    printf("Nhấn nút Pump? (1 = Có, 0 = Không): ");
    scanf("%d", &pump_input);
    pump_button_pressed = (pump_input == 1);
}
// Lấy và xoá cờ mode_button
bool get_mode_pressed() {
    bool pressed = mode_button_pressed;
    mode_button_pressed = false;
    return pressed;
}

// Lấy và xoá cờ pump_button
bool get_pump_pressed() {
    bool pressed = pump_button_pressed;
    pump_button_pressed = false;
    return pressed;
}
