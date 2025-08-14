#ifndef PUMP_H
#define PUMP_H

#include "type.h"

void init_pump(void);
void set_pump_state(pump_state_t state);
pump_state_t get_pump_state(void);

#endif
