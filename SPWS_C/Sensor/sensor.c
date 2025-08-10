#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void init_sensor() {
    srand(time(NULL)); // Khởi tạo random
    printf("[SENSOR] Khởi tạo cảm biến (mô phỏng).\n");
}

float read_temperature() {
    float temp;
    printf("Nhập nhiệt độ (°C): ");
    scanf("%f", &temp);
    return temp;
}

float read_humidity() {
    float hum;
    printf("\nNhập độ ẩm (%%): ");
    scanf("%f", &hum);
    return hum;
}