#include "state_machine.h"
#include "sensor.h"
#include "pump.h"
#include "led.h"
#include "button.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>

// ==== Biến trạng thái nội bộ ====
system_mode_t current_mode = MODE_AUTO;
static pump_state_t current_pump_state = PUMP_OFF;
static led_status_t current_led_status = LED_NORMAL;

// Thời điểm lần tưới gần nhất (để quản lý thời gian tưới)
static unsigned long last_watering_time = 0;
static unsigned long pump_on_time = 0;

// Biến toàn cục lưu dữ liệu cảm biến
static float latest_temp = NAN;
static float latest_hum = NAN;

unsigned long millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL);
}


void scan_input() {
    latest_hum = read_humidity();
    latest_temp = read_temperature();
    update_buttons_from_keyboard();
}

void init_system_state() {
    current_mode = MODE_AUTO;
    current_pump_state = PUMP_OFF;
    current_led_status = LED_NORMAL;

    set_pump_state(PUMP_OFF);
    set_led_status(LED_NORMAL);
    last_watering_time = millis();
}

void handle_mode_button() {
    if (get_and_clear_mode_button_flag()) {
        if (current_mode == MODE_AUTO) {
            current_mode = MODE_MANUAL;
            set_pump_state(PUMP_OFF);  // Tắt bơm khi vào manual
        } else {
            current_mode = MODE_AUTO;
        }
    }
}

void handle_manual_pump_button() {
    if (get_and_clear_pump_button_flag() && current_mode == MODE_MANUAL) {
        set_pump_state(PUMP_ON);
        pump_on_time = millis();
        current_pump_state = PUMP_ON;
        current_led_status = LED_WATERING;
        set_led_status(LED_WATERING);
    }
}

void update_system_state() {
      // ==== Chế độ TỰ ĐỘNG ====
    if (current_mode == MODE_AUTO) {
        if (current_pump_state == PUMP_OFF &&
            latest_hum < MOISTURE_MIN_THRESHOLD &&
            millis() - last_watering_time > MIN_INTERVAL_BETWEEN_WATERING_MS) {
            set_pump_state(PUMP_ON);
            current_pump_state = PUMP_ON;
            current_led_status = LED_WATERING;
            set_led_status(LED_WATERING);
            pump_on_time = millis();
        }

        // Kiểm tra điều kiện dừng tưới
        if (current_pump_state == PUMP_ON) {
            if (latest_hum >= MOISTURE_MAX_THRESHOLD ||
                millis() - pump_on_time >= MAX_PUMP_ON_DURATION_MS) {

                set_pump_state(PUMP_OFF);
                current_pump_state = PUMP_OFF;
                last_watering_time = millis();

                current_led_status = LED_NORMAL;
                set_led_status(LED_NORMAL);
            }
        }

        // Độ ẩm thấp nhưng chưa đủ điều kiện tưới lại
        if (latest_hum < MOISTURE_MIN_THRESHOLD &&
            current_pump_state == PUMP_OFF) {

            current_led_status = LED_LOW_MOISTURE_ALERT;
            set_led_status(LED_LOW_MOISTURE_ALERT);
        }

    // ==== Chế độ THỦ CÔNG ====
    } else if (current_mode == MODE_MANUAL) {
        if (current_pump_state == PUMP_ON &&
            millis() - pump_on_time >= MANUAL_PUMP_DURATION_MS) {

            set_pump_state(PUMP_OFF);
            current_pump_state = PUMP_OFF;

             // Kiểm tra lại độ ẩm để quyết định trạng thái LED
            if (latest_hum < MOISTURE_MIN_THRESHOLD) {
                current_led_status = LED_LOW_MOISTURE_ALERT;
                set_led_status(LED_LOW_MOISTURE_ALERT);
            } else {
                current_led_status = LED_NORMAL;
                set_led_status(LED_NORMAL);
            }
        }
    }
}

system_mode_t get_current_mode() {
    return current_mode;
}

pump_state_t get_current_pump_state() {
    return current_pump_state;
}

led_status_t get_current_led_status() {
    return current_led_status;
}

void log_with_time(const char* message) {
    printf("\n[%lus] %s", millis() / 1000, message);
}


void monitor_and_display_status() {
     static float temp_t = NAN;
    static float hum_t = NAN;
    static system_mode_t mode_t = MODE_AUTO;
    static pump_state_t pump_st_t = PUMP_OFF;
    static led_status_t led_st_t  = LED_NORMAL;

    float temp = latest_temp;
    float hum = latest_hum;
    system_mode_t mode = get_current_mode();
    pump_state_t pump_st = get_current_pump_state();
    led_status_t led_st = get_current_led_status();

    if (fabs(temp - temp_t) > 0.5 || fabs(hum - hum_t) > 1.0 || 
        (mode != mode_t) || (pump_st != pump_st_t) || (led_st != led_st_t)) {

       log_with_time("Nhiệt độ: ");
       printf("%.2fºC, Độ ẩm: %.2f%%, Chế độ: %s\n",
               temp, hum, mode == MODE_AUTO ? "Tự động" : "Thủ công");
        printf("Trạng thái bơm: %s\n", pump_st == PUMP_ON ? "[PUMP] Bơm bật." : 
            "[PUMP] Bơm tắt.");
        printf("Trạng thái hệ thống: ");
        switch (led_st) {
            case LED_NORMAL: 
                printf("Bình thường.\n"); 
                printf("[LED] Xanh ON | Vàng OFF | Đỏ OFF\n");
                break;
            case LED_WATERING: 
                printf("Đang tưới nước.\n"); 
                printf("[LED] Xanh OFF | Vàng ON | Đỏ OFF\n");
                break;
            case LED_LOW_MOISTURE_ALERT: 
                printf("Cảnh báo độ ẩm thấp!\n"); 
                printf("[LED] Xanh OFF | Vàng OFF | Đỏ ON\n");
                break;
            case LED_ERROR: 
                printf("Lỗi hệ thống!\n"); 
                printf("[LED] Xanh OFF | Vàng OFF | Đỏ ON\n");
                break;
            case LED_OFF:
                printf("Test hệ thống.\n");
                printf("[LED] Xanh OFF | Vàng OFF | Đỏ OFF\n");
                break;
        }
         
        // Cập nhật trạng thái trước đó
        temp_t = temp;
        hum_t = hum;
        mode_t = mode;
        pump_st_t = pump_st;
        led_st_t = led_st;
    }
}