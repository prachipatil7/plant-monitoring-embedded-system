// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#pragma once

#include "nrf_twi_mngr.h"

void gpio_init(void);

void green_light_on(void);

void green_light_off(void);

void turn_on_pump(void);
