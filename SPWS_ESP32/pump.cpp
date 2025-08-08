#include "pump.h"
#include <Arduino.h>

static pump_state_t current_pump_state = PUMP_OFF;

void init_pump(void) {
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    digitalWrite(PUMP_RELAY_PIN, !PUMP_ACTIVE_LEVEL);  // Tắt bơm ban đầu
    current_pump_state = PUMP_OFF;
}

void set_pump_state(pump_state_t state) {
    current_pump_state = state;

    if (state == PUMP_ON) {
        digitalWrite(PUMP_RELAY_PIN, PUMP_ACTIVE_LEVEL);      // Bật relay
    } else {
        digitalWrite(PUMP_RELAY_PIN, !PUMP_ACTIVE_LEVEL);     // Tắt relay
    }
}

pump_state_t get_pump_state(void) {
    return current_pump_state;
}
