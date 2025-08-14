#ifndef SENSOR_H
#define SENSOR_H

#include "type.h"
//Khởi tạo cảm biến nhiệt độ, độ ẩm
void init_sensor();

//Đọc nhiệt độ, độ ẩm từ cảm biến (set nhiệt độ, độ ẩm)
void simulate_temperature();
void simulate_humidity();

//Lấy giá trị nhiệt độ, độ ẩm
float get_temperature();
float get_humidity();

#endif