#include <Arduino.h>

#include "sensor.h"
#include "pump.h"
#include "led.h"
#include "button.h"
#include "state_machine.h"

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT); //for test board
    // // Khởi tạo các thành phần phần cứng
    init_sensor();
    init_pump();
    init_led();
    init_buttons();

    // // Khởi tạo trạng thái hệ thống
    init_system_state();

    Serial.println("Hệ thống tưới cây thông minh");
    // // Test sensor 
    // float temp = read_temperature();
    // float hum = read_humidity();
    // Serial.print("Nhiệt độ: ");
    // Serial.print(temp);
    // Serial.print("ºC, Độ ẩm: ");
    // Serial.println(hum);

    // //Test leds
    // set_led_status(LED_NORMAL); //green
    // delay(1000);
    // set_led_status(LED_WATERING); // yellow
    // delay(1000);
    // set_led_status(LED_LOW_MOISTURE_ALERT); // red
    // delay(1000);
    // set_led_status(LED_OFF); // off
    // delay(1000);
    // set_led_status(LED_ERROR); // red
    // delay(1000);
    // set_led_status(LED_OFF); // off

    // //Test relay and pump
    // set_pump_state(PUMP_ON);
    // delay(1000);
    // set_pump_state(PUMP_OFF);

}

void loop() {
    // Xử lý nút nhấn (có debounce và flag trong ISR)
    handle_mode_button();
    handle_manual_pump_button();

    unsigned long last_check = -SENSOR_CHECK_INTERVAL_MS;

    if (millis() - last_check >= SENSOR_CHECK_INTERVAL_MS) {
      // Cập nhật logic điều khiển chính của hệ thống (FSM)
      update_system_state();
      monitor_and_display_status();
      last_check = millis();
    }
    

    // //test board 
    // digitalWrite(led1, HIGH);
    // delay(1000);                    
    // digitalWrite(led1, LOW); 
    // delay(1000);  

    // //test button
    // if(get_and_clear_mode_button_flag()) { Serial.println("Nút mode được nhấn"); }
    // if(get_and_clear_pump_button_flag()) { Serial.println("Nut pump được nhấn."); }

    delay(500);
}

