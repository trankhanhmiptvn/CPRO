#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include "type.h"

void init_buttons();
bool get_mode_pressed();
bool get_pump_pressed();
void simulate_mode_pressed();
void simulate_pump_pressed();

#endif
