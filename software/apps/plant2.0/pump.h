// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#pragma once

#include "nrf_twi_mngr.h"

void pump_init(void);
void turn_on_pump(void);
void turn_off_pump(void);
