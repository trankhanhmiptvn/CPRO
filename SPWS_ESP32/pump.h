#ifndef PUMP_H
#define PUMP_H

#include "config.h"
#include "type.h"

void init_pump();
void set_pump_state(pump_state_t state);
pump_state_t get_pump_state();

#endif
