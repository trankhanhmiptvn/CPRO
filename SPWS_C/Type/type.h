// types.h
#ifndef TYPES_H
#define TYPES_H

typedef enum {
    PUMP_OFF = 0,
    PUMP_ON  = 1
} pump_state_t;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR,
    LED_OFF //For test only
} led_status_t;

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} system_mode_t;

typedef struct
{
    float temp;
    float humi;
} Sensor_data_t;

#endif
