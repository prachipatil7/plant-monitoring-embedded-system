#pragma once

#include "nrf_twi_mngr.h"
static const uint8_t MOIST_ADDRESS = 0x28;

// Register definitions for moisture sensor
typedef enum {
 MOIST_OUT_REG = 0xA0,
 MOIST_POWER_REG = 0xD7
	      
} moist_reg_t;

void lsm_init(const nrf_twi_mngr_t* i2c);

// Read the internal moisture sensor
//
// Return measurement as [What Unit?]
float read_moisture(void);
