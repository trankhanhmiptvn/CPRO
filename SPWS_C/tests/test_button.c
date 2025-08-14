#include <stdio.h>
#include <stdbool.h>
#include "button.h"

// Hàm test khởi tạo nút
void test_init_buttons() {
    printf("\n[TEST] Bắt đầu test init_buttons...\n");
    init_buttons();
    if (!get_mode_pressed() && !get_pump_pressed()) {
        printf("[PASS] init_buttons đặt đúng trạng thái ban đầu.\n");
    } else {
        printf("[FAIL] init_buttons sai trạng thái ban đầu.\n");
    }
}

// Hàm test mô phỏng nhấn nút Mode
void test_mode_button() {
    printf("\n[TEST] Bắt đầu test simulate_mode_pressed...\n");
    simulate_mode_pressed();
    if (get_mode_pressed()) {
        printf("[PASS] Mode button hoạt động đúng.\n");
    } else {
        printf("[FAIL] Mode button không hoạt động.\n");
    }
}

// Hàm test mô phỏng nhấn nút Pump
void test_pump_button() {
    printf("\n[TEST] Bắt đầu test simulate_pump_pressed...\n");
    simulate_pump_pressed();
    if (get_pump_pressed()) {
        printf("[PASS] Pump button hoạt động đúng.\n");
    } else {
        printf("[FAIL] Pump button không hoạt động.\n");
    }
}

int main(void) {
    printf("===== BẮT ĐẦU CHẠY TEST BUTTON =====\n");
    test_init_buttons();
    test_mode_button();
    test_pump_button();
    printf("===== KẾT THÚC TEST BUTTON =====\n");
    return 0;
}
