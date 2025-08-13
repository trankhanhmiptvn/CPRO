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
volatile static system_mode_t current_mode = MODE_AUTO;
volatile static pump_state_t current_pump_state = PUMP_OFF;
volatile static led_status_t current_led_status = LED_NORMAL;
volatile static Sensor_data_t current_sensor_data;

// Thời điểm lần tưới gần nhất (để quản lý thời gian tưới)
static unsigned long last_watering_time = 0;
static unsigned long pump_on_time = 0;
int state = -1;



unsigned long millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL);
}

void simulate_system_input() {
    simulate_temperature();
    simulate_humidity();
    simulate_mode_pressed();
    simulate_pump_pressed();
}

void handle_mode_pressed() {
    if (get_mode_pressed()) {
        if (current_mode == MODE_AUTO) {
            current_mode =  MODE_MANUAL;
        } else {
            current_mode = MODE_AUTO;
        }
    }
}

void handle_pump_pressed() {
    if ( (current_mode!= MODE_AUTO) && get_pump_pressed()) {
        if (current_pump_state == PUMP_OFF) {
            set_pump_state(PUMP_ON);
        } else {
            set_pump_state(PUMP_OFF);
        }
    }
}

void get_system_state() {
    handle_mode_pressed();
    handle_pump_pressed();
    current_pump_state = get_pump_state();
    current_sensor_data.temp = get_temperature();
    current_sensor_data.humi = get_humidity();
    //current_led_status = get_led_status();
    //display_status(current_pump_state, current_led_status);;
}


void control_auto_mode(void) {
    // ==== Bật bơm khi độ ẩm thấp hoặc nhiệt độ cao ====
    if (current_pump_state == PUMP_OFF &&
        (current_sensor_data.humi < HUMI_MIN_THRESHOLD ||
         current_sensor_data.temp > TEMP_MAX_THRESHOLD) &&
        millis() - last_watering_time > MIN_INTERVAL_BETWEEN_WATERING_MS) {
        state = 0;
        set_pump_state(PUMP_ON);
        set_led_status(LED_WATERING);
        pump_on_time = millis();
        return; 
    }
    
    if (current_pump_state == PUMP_OFF &&
        (current_sensor_data.humi < HUMI_MIN_THRESHOLD ||
         current_sensor_data.temp > TEMP_MAX_THRESHOLD) &&
        millis() - last_watering_time <= MIN_INTERVAL_BETWEEN_WATERING_MS) {
        state = 1;
        set_led_status(LED_LOW_MOISTURE_ALERT);
        return; 
    }

    // ==== Dừng bơm khi bơm đủ thời gian hoặc nhiệt độ giảm dưới ngưỡng trung bình hoặc độ ẩm tăng trên ngưỡng trung bình ====
    if (current_pump_state == PUMP_ON) {
        if ((current_sensor_data.humi > (HUMI_MAX_THRESHOLD + HUMI_MIN_THRESHOLD) / 2 &&
             current_sensor_data.temp < (TEMP_MAX_THRESHOLD + TEMP_MIN_THRESHOLD) / 2) ||
            millis() - pump_on_time >= MAX_PUMP_ON_DURATION_MS) {

            set_pump_state(PUMP_OFF);

            if (current_sensor_data.humi >= HUMI_MIN_THRESHOLD &&
                current_sensor_data.humi <= HUMI_MAX_THRESHOLD &&
                current_sensor_data.temp >= TEMP_MIN_THRESHOLD &&
                current_sensor_data.temp <= TEMP_MAX_THRESHOLD) {
                set_led_status(LED_NORMAL);
                state = 2;
            } else {
                set_led_status(LED_LOW_MOISTURE_ALERT);
                state = 3;
                
            }
            last_watering_time = millis();
        }
        return; 
    }
    set_led_status(LED_NORMAL);
}

void control_manual_mode(void) {
    
    if (current_pump_state == PUMP_ON &&
        millis() - pump_on_time >= MANUAL_PUMP_DURATION_MS) {
        set_pump_state(PUMP_OFF);
        state = 4;
    }
    //handle_pump_pressed();
    if (current_sensor_data.humi >= HUMI_MIN_THRESHOLD &&
            current_sensor_data.humi <= HUMI_MAX_THRESHOLD &&
            current_sensor_data.temp >= TEMP_MIN_THRESHOLD &&
            current_sensor_data.temp <= TEMP_MAX_THRESHOLD) {
            set_led_status(LED_NORMAL);
    } else {
            set_led_status(LED_LOW_MOISTURE_ALERT);
    }
}

void control_system_state(void) {
    if (current_mode == MODE_AUTO) {
        control_auto_mode();
    } else if (current_mode == MODE_MANUAL) {
        control_manual_mode();
    }
}



void log_with_time(const char* message) {
    printf("\n[%lus] %s", millis() / 1000, message);
}


void display_status(pump_state_t pump_st,   led_status_t led_st) {
 
    log_with_time("Nhiệt độ: ");
    printf("%.2fºC, Độ ẩm: %.2f%%, Chế độ: %s\n",
               current_sensor_data.temp, 
               current_sensor_data.humi,
               current_mode == MODE_AUTO ? "Tự động" : "Thủ công");
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
            printf("Cảnh báo độ ẩm hoặc nhiệt độ vượt ngưỡng.\n"); 

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
    switch (state)
    {
    case 0:
        printf("(0).Bơm bật do nhiệt độ hoặc độ ẩm vượt ngưỡng, khoảng cách giữa hai lần bơm thỏa mãn.\n");
        break;
     case 1:
        printf("(1),Bơm chưa thể bật do khoảng cách giữa hai lần bật bơm không thỏa mãn phải cách nhau ít nhất %u ms!\n",
                                                                      MIN_INTERVAL_BETWEEN_WATERING_MS); 
        break;
    case 2:
        printf("(2).Thời gian đã bơm: %lu ms.\n",
            millis() - pump_on_time);
        break;
    case 3:
        printf("(3).Thời gian đã bơm: %lu ms\n", (unsigned long)MAX_PUMP_ON_DURATION_MS);
        break;
    case 4:
        printf("(4).Thời gian đã bơm: %lu ms\n", (unsigned long)MANUAL_PUMP_DURATION_MS);
        break;
    case 5:
        printf("(5).Bơm chưa thể tắt do chưa bơm xong theo quy định.\n");
        break;
    case 6:
        printf("(6).\n");
        break;
    case 7:
        printf("(7).");
        break;
    default:
        printf("(8).\n");
        break;
    }
}

void monitor_and_display_status() {
    static pump_state_t last_pump_st = -1; // Giá trị không hợp lệ để đảm bảo in lần đầu
    static led_status_t last_led_st  = -1;
    static system_mode_t last_mode_st = -1; // Giá trị không hợp lệ để đảm bảo in lần đầu
    static Sensor_data_t last_sensor_st  = {-1, -1};

    pump_state_t pump_st =  get_pump_state();
    led_status_t led_st = get_led_status();

    if (pump_st != last_pump_st || 
        led_st != last_led_st || 
        current_mode != last_mode_st || 
        current_sensor_data.humi != last_sensor_st.humi ||
        current_sensor_data.temp != last_sensor_st.temp  ) {
        display_status(pump_st, led_st);
        last_pump_st = pump_st;
        last_led_st  = led_st;
        last_mode_st = current_mode;
        last_sensor_st.humi = current_sensor_data.humi;
        last_sensor_st.temp = current_sensor_data.temp;
    }
}

