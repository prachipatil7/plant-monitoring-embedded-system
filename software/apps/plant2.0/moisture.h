#pragma once

#include "nrf_twi_mngr.h"
static const uint8_t MOIST_ADDRESS = 0x28;

// Register definitions for moisture sensor
typedef enum {
 MOIST_OUT_REG = 0x05,
 MOIST_POWER_REG = 0xD7,
 MOIST_LED_ON_REG = 0x01,
 MOIST_LED_OFF_REG = 0x00,
 MOIST_NOTHING_NEW_REG = 0x99      
} moist_reg_t;


void moisture_init(const nrf_twi_mngr_t* i2c);

// Read the internal moisture sensor
//
// Return measurement as [What Unit?]
float read_moisture(void);
