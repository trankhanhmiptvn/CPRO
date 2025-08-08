#include "state_machine.h"
#include "sensor.h"
#include "pump.h"
#include "led.h"
#include "button.h"
#include "config.h"
#include <Arduino.h>

// ==== Biến trạng thái nội bộ ====
static system_mode_t current_mode = MODE_AUTO;
static pump_state_t current_pump_state = PUMP_OFF;
static led_status_t current_led_status = LED_NORMAL;

// Thời điểm lần tưới gần nhất (để quản lý thời gian tưới)
static unsigned long last_watering_time = 0;
static unsigned long pump_on_time = 0;

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
    float moisture = read_humidity();  // Cảm biến đất trả về %
    //float temperature = read_temperature(); 

    // ==== Chế độ TỰ ĐỘNG ====
    if (current_mode == MODE_AUTO) {
        if (current_pump_state == PUMP_OFF &&
            moisture < MOISTURE_MIN_THRESHOLD &&
            millis() - last_watering_time > MIN_INTERVAL_BETWEEN_WATERING_MS) {

            set_pump_state(PUMP_ON);
            current_pump_state = PUMP_ON;
            current_led_status = LED_WATERING;
            set_led_status(LED_WATERING);
            pump_on_time = millis();
        }

        // Kiểm tra điều kiện dừng tưới
        if (current_pump_state == PUMP_ON) {
            if (moisture >= MOISTURE_MAX_THRESHOLD ||
                millis() - pump_on_time >= MAX_PUMP_ON_DURATION_MS) {

                set_pump_state(PUMP_OFF);
                current_pump_state = PUMP_OFF;
                last_watering_time = millis();

                current_led_status = LED_NORMAL;
                set_led_status(LED_NORMAL);
            }
        }

        // Độ ẩm thấp nhưng chưa đủ điều kiện tưới lại
        if (moisture < MOISTURE_MIN_THRESHOLD &&
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
            if (moisture < MOISTURE_MIN_THRESHOLD) {
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
    Serial.print("\n[");
    Serial.print(millis() / 1000);  // Thời gian tính bằng giây
    Serial.print("s] ");
    Serial.print(message);
}


void monitor_and_display_status() {
    static float temp_t = -100;
    static float hum_t = -100;
    static system_mode_t mode_t = MODE_AUTO;
    static pump_state_t pump_st_t = PUMP_OFF;
    static led_status_t led_st_t  = LED_NORMAL;

    float temp = read_temperature();
    float hum = read_humidity();
    system_mode_t mode = get_current_mode();
    pump_state_t pump_st = get_current_pump_state();
    led_status_t led_st = get_current_led_status();

    if (fabs(temp - temp_t) > 0.5 || fabs(hum - hum_t) > 1.0 || 
        (mode != mode_t) || (pump_st != pump_st_t) || (led_st != led_st_t)) {

        log_with_time("Nhiệt độ: ");
        Serial.print(temp);
        Serial.print("ºC, Độ ẩm: ");
        Serial.print(hum);
        Serial.print("%, Chế độ: ");
        Serial.println(mode == MODE_AUTO ? "Tự động" : "Thủ công");

        Serial.print("Trạng thái bơm: ");
        Serial.println(pump_st == PUMP_ON ? "Bật" : "Tắt");
        Serial.print("Trạng thái hệ thống: ");

        switch (led_st) {
            case LED_NORMAL:
                Serial.println("Bình thường.");
                break;
            case LED_WATERING:
                Serial.println("Đang tưới nước.");
                break;
            case LED_LOW_MOISTURE_ALERT:
                Serial.println("Cảnh báo độ ẩm thấp!");
                break;
            case LED_ERROR:
                Serial.println("Lỗi hệ thống!");
                break;
            default:
                Serial.println("Chế độ test");
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