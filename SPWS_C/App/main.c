#include "sensor.h"
#include "pump.h"
#include "led.h"
#include "button.h"
#include "state_machine.h"
#include "config.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void setup() {
    printf("Khởi tạo các thiết bị ngoại vi.\n");
    init_sensor();
    init_pump();
    init_led();
    init_buttons();
    init_system_state();
    printf("===============================================\n");
}

void loop() {
    printf("=====Check1====\n");
    scan_input();
    // Xử lý nút nhấn 
    handle_mode_button();
    handle_manual_pump_button();
    printf("=====Check1====\n");
    static unsigned long last_check = 0;
    if (millis() - last_check >= SENSOR_CHECK_INTERVAL_MS) {
       printf("=====Check2====\n");
      update_system_state();
       printf("=====Check2====\n");
      monitor_and_display_status();
      last_check = millis();
    }

}
int main() {
  setup();
  printf("Hệ thống tưới cây thông minh (mô phỏng)\n");
  while(1) {
    loop();
    usleep(200);
  }
  return 0;
}