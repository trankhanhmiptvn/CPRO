#include "led.h"
#include <stdio.h>

volatile led_status_t led_st;

void init_led(void) {
    printf("[LED] Khởi tạo. Tất cả LED tắt.\n");
    led_st = LED_OFF;
}

void set_led_status(led_status_t status) {
    led_st = status;
}
led_status_t get_led_status() {
    return led_st;
}
