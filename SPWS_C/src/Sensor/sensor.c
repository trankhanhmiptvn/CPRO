#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Cờ báo hiệu nút đã nhấn
volatile Sensor_data_t sensor;

void init_sensor() {
    printf("[SENSOR] Khởi tạo cảm biến.\n");
    sensor.temp = 0.00;
    sensor.humi = 0.00;
}

void simulate_temperature() {
    printf("\nNhập nhiệt độ (°C): ");
    scanf("%f", &sensor.temp);
}

void simulate_humidity() {
    printf("Nhập độ ẩm (%%): ");
    scanf("%f", &sensor.humi);
}

float get_temperature() {
    return sensor.temp;
}
float get_humidity() {
    return sensor.humi;
}