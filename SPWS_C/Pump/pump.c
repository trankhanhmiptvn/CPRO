#include "pump.h"
#include <stdio.h>

static pump_state_t current_pump_state = PUMP_OFF;

void init_pump(void) {
    current_pump_state = PUMP_OFF;
    printf("[PUMP] Khởi tạo: Bơm tắt.\n");
}

void set_pump_state(pump_state_t state) {
    current_pump_state = state;
}

pump_state_t get_pump_state(void) {
    return current_pump_state;
}
