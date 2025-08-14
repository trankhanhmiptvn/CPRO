#ifndef CONFIG_H
#define CONFIG_H

// ===== Pin Mapping =====
#define DHTPIN               15      // Cảm biến DHT nhiệt độ/độ ẩm
#define DHTTYPE              DHT11  // Loại cảm biến

#define PUMP_RELAY_PIN       27     // Chân điều khiển relay bơm
#define PUMP_ACTIVE_LEVEL    1      // Nếu relay active-low 0

#define LED_RED_PIN          13
#define LED_GREEN_PIN        12
#define LED_YELLOW_PIN       14


#define MODE_BUTTON_PIN      25      // Nút chuyển đổi chế độ
#define PUMP_BUTTON_PIN      26      // Nút kích hoạt bơm thủ công

// ===== Ngưỡng cấu hình =====
#define HUMI_MIN_THRESHOLD                20    // Bắt đầu tưới nếu dưới min
#define HUMI_MAX_THRESHOLD                60    // Dừng tưới nếu trên max
#define TEMP_MIN_THRESHOLD                20    // Dừng tưới nếu nhiệt độ dưới min
#define TEMP_MAX_THRESHOLD                40    // Bắt đầu tưới nhiệt độ trên max
#define MANUAL_PUMP_DURATION_MS           10000 // ms, tưới thủ công trong 10 giây
#define MAX_PUMP_ON_DURATION_MS           10000 // ms, thời gian tưới tự động tối đa
#define MIN_INTERVAL_BETWEEN_WATERING_MS  40000 //Khoảng cách tối thiểu giữa hai lần tưới

// ===== Chu kỳ hệ thống =====
#define SENSOR_CHECK_INTERVAL_MS 1000  // Kiểm tra cảm biến mỗi ms

// ===== Chống dội nút nhấn =====
#define DEBOUNCE_TIME_MS     200

#endif
