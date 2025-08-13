#include "pump.h"
#include <stdio.h>

volatile pump_state_t pump_st;

void init_pump(void) {
    printf("[PUMP] Khởi tạo: Bơm tắt.\n");
     pump_st = PUMP_OFF;
}

void set_pump_state(pump_state_t state) {
    pump_st = state;
}

pump_state_t get_pump_state(void) {
    return pump_st;
}
