#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include "type.h"

void init_buttons();
bool get_and_clear_mode_button_flag();
bool get_and_clear_pump_button_flag();
void update_buttons_from_keyboard();

#endif
