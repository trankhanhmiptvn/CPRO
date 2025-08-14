#include "pump.h"
#include <stdio.h>

static void test_init_pump(void) {
    printf("[TEST] Bắt đầu test init_pump...\n");
    init_pump();
    if (get_pump_state() == PUMP_OFF) {
        printf("[PASS] init_pump đặt bơm ở trạng thái PUMP_OFF.\n");
    } else {
        printf("[FAIL] init_pump không đặt đúng trạng thái ban đầu.\n");
    }
}

static void test_set_pump_state(void) {
    printf("[TEST] Bắt đầu test set_pump_state...\n");
    set_pump_state(PUMP_ON);
    if (get_pump_state() == PUMP_ON) {
        printf("[PASS] set_pump_state thay đổi sang PUMP_ON thành công.\n");
    } else {
        printf("[FAIL] set_pump_state không thay đổi đúng trạng thái.\n");
    }
}

static void test_get_pump_state(void) {
    printf("[TEST] Bắt đầu test get_pump_state...\n");
    pump_state_t state = get_pump_state();
    if (state == PUMP_ON) {
        printf("[PASS] get_pump_state đọc đúng trạng thái PUMP_ON.\n");
    } else if (state == PUMP_OFF) {
        printf("[PASS] get_pump_state đọc đúng trạng thái PUMP_OFF.\n");
    } else {
        printf("[FAIL] get_pump_state trả về giá trị không hợp lệ.\n");
    }
}

int main(void) {
    printf("===== BẮT ĐẦU CHẠY TEST PUMP =====\n");
    test_init_pump();
    test_set_pump_state();
    test_get_pump_state();
    printf("===== KẾT THÚC TEST PUMP =====\n");
    return 0;
}
