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
    printf("===============================================\n");
}

void loop() {
    static unsigned long last_check = 0;
    if (millis() - last_check >= SENSOR_CHECK_INTERVAL_MS) {
      simulate_system_input();
      get_system_state();
      last_check = millis();
    }
    control_system_state();
    monitor_and_display_status();

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