// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#pragma once

#include "nrf_twi_mngr.h"

// i2c address for sensor
static const uint8_t TEMP_MOISTURE_SENSOR = 0x70;

// commands from datasheet 
typedef enum {
  // after some time duration = ?? need to put to sleep
  SLEEP_REG = 0xB0,
  SLEEP_COMM = 98,
  // to communicate, needs to be awake
  WAKEUP_REG = 0x35,
  WAKEUP_COMM = 0x17,
  // clock stretching enabled
  READ_TEMP_REG = 0x7C,
  READ_TEMP_COMM = 0xA2,
  READ_HUM_REG = 0x5C,
  READ_HUM_COMM = 0x24,
  CS_READ_T_LP = 0x6458,
  CS_READ_H_LP = 0x44DE,
  // clock stretching disabled
  READ_T = 0x7866,
  READ_H = 0x58E0,
  READ_T_LP = 0x609C,
  READ_H_LP = 0x401A,
  // recalibrate, no measurement can be in progress
  SOFTWARE_RESET = 0x805D,
  // general address reset method
  GEN_ADD_RESET = 0x000,
  // read i2c peripheral ID,
  READ_ID = 0xEFC8
} command_t;

// Function prototypes

// Initialize and configure the SHTC3 Humidity (and Temperature) Sensor
// i2c - pointer to already initialized and enabled twim instance
void shtc3_init(const nrf_twi_mngr_t* i2c);

// Read the temperature
// return - current temp in deg C
float shtc3_read_temperature(void);

// Read the humidity
// return - the relative humidity as a percent of saturated atmospheric humidity
float shtc3_read_humidity(void);
