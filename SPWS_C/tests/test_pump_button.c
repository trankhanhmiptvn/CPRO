#include "button.h"
#include "pump.h"
#include <stdio.h>

void handle_pump_button(void) {
    if (get_pump_pressed()) {  // Đúng hàm từ button.h
        pump_state_t current = get_pump_state();
        if (current == PUMP_OFF) {
            set_pump_state(PUMP_ON);
            printf("[ACTION] Nút Pump nhấn -> Bật bơm.\n");
        } else {
            set_pump_state(PUMP_OFF);
            printf("[ACTION] Nút Pump nhấn -> Tắt bơm.\n");
        }
    }
}

int main(void) {
    printf("===== BẮT ĐẦU CHẠY TEST PUMP-BUTTON =====\n");

    init_buttons();
    init_pump();

    // Test 1: bật bơm
    printf("[TEST] Mô phỏng bấm nút Pump lần 1...\n");
    simulate_pump_pressed();   // hỏi user nhập 1 hoặc 0
    handle_pump_button();
    if (get_pump_state() == PUMP_ON) {
        printf("[PASS] Lần 1: Bơm đã bật.\n");
    } else {
        printf("[FAIL] Lần 1: Bơm chưa bật.\n");
    }

    // Test 2: tắt bơm
    printf("[TEST] Mô phỏng bấm nút Pump lần 2...\n");
    simulate_pump_pressed();
    handle_pump_button();
    if (get_pump_state() == PUMP_OFF) {
        printf("[PASS] Lần 2: Bơm đã tắt.\n");
    } else {
        printf("[FAIL] Lần 2: Bơm chưa tắt.\n");
    }

    printf("===== KẾT THÚC TEST PUMP-BUTTON =====\n");
    return 0;
}
