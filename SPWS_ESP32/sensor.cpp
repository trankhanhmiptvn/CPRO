#include "sensor.h"

#include <DHT.h>

static DHT dht(DHTPIN, DHTTYPE);

void init_sensor() {
    dht.begin();
}

float read_temperature() {
    return dht.readTemperature();
}

float read_humidity() {
    return dht.readHumidity();
}
