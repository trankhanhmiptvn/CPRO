#include "led.h"
#include <stdio.h>

static led_status_t current_status = LED_NORMAL;

void init_led(void) {
    current_status = LED_OFF;
    printf("[LED] Khởi tạo. Tất cả LED tắt.\n");
}

void set_led_status(led_status_t status) {
    current_status = status;
}
