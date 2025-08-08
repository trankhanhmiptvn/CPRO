#include "led.h"

#include <Arduino.h>

static led_status_t current_status = LED_NORMAL;

void init_led(void) {
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_YELLOW_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);

    // Tắt tất cả LED ban đầu
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_YELLOW_PIN, LOW);
    digitalWrite(LED_RED_PIN, LOW);
}

void set_led_status(led_status_t status) {
    current_status = status;

    // Tắt tất cả LED trước
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_YELLOW_PIN, LOW);
    digitalWrite(LED_RED_PIN, LOW);

    switch (status) {
        case LED_NORMAL:
            digitalWrite(LED_GREEN_PIN, HIGH);
            break;
        case LED_WATERING:
            digitalWrite(LED_YELLOW_PIN, HIGH);
            break;
        case LED_LOW_MOISTURE_ALERT:
        case LED_ERROR:
            digitalWrite(LED_RED_PIN, HIGH);
            break;
        case LED_OFF:
          digitalWrite(LED_GREEN_PIN, LOW);
          digitalWrite(LED_YELLOW_PIN, LOW);
          digitalWrite(LED_RED_PIN, LOW);
          break;
    }
}

\
