#include "button.h"
#include <Arduino.h>

// Cờ báo hiệu nút đã nhấn
volatile bool mode_button_pressed = false;
volatile bool pump_button_pressed = false;

// Thời điểm lần ngắt trước đó (chống dội)
volatile unsigned long last_mode_interrupt = 0;
volatile unsigned long last_pump_interrupt = 0;

// ISR cho nút chuyển chế độ
void IRAM_ATTR mode_button_isr() {
    unsigned long current_time = millis();
    if (current_time - last_mode_interrupt > DEBOUNCE_TIME_MS) {
        last_mode_interrupt = current_time;
        mode_button_pressed = true;
    }
}

// ISR cho nút điều khiển bơm
void IRAM_ATTR pump_button_isr() {
    unsigned long current_time = millis();
    if (current_time - last_pump_interrupt > DEBOUNCE_TIME_MS) {
        last_pump_interrupt = current_time;
        pump_button_pressed = true;
    }
}

// Khởi tạo chân nút và ngắt
void init_buttons() {
    pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(PUMP_BUTTON_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(MODE_BUTTON_PIN), mode_button_isr, FALLING);
    attachInterrupt(digitalPinToInterrupt(PUMP_BUTTON_PIN), pump_button_isr, FALLING);
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
