#include <stdio.h>
#include "led.h"

// Hàm kiểm tra giá trị LED hiện tại và in kết quả
void check_led_status(led_status_t expected, const char *test_name) {
    if (get_led_status() == expected) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s (Expected: %d, Got: %d)\n",
               test_name, expected, get_led_status());
    }
}

// Test khởi tạo LED
void test_init_led() {
    printf("\n[TEST] Bắt đầu test init_led...\n");
    init_led();
    check_led_status(LED_OFF, "init_led đặt LED_OFF");
}

// Test thay đổi trạng thái LED
void test_set_led_status() {
    printf("\n[TEST] Bắt đầu test set_led_status...\n");
    set_led_status(LED_NORMAL);
    check_led_status(LED_NORMAL, "set_led_status đặt LED_NORMAL");

    set_led_status(LED_WATERING);
    check_led_status(LED_WATERING, "set_led_status đặt LED_WATERING");

    set_led_status(LED_LOW_MOISTURE_ALERT);
    check_led_status(LED_LOW_MOISTURE_ALERT, "set_led_status đặt LED_LOW_MOISTURE_ALERT");
}

int main(void) {
    printf("===== BẮT ĐẦU CHẠY TEST LED =====\n");
    test_init_led();
    test_set_led_status();
    printf("===== KẾT THÚC TEST LED =====\n");
    return 0;
}
