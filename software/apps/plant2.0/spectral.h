#pragma once

#include "nrf_twi_mngr.h"

// Register definitions for moisture sensor
typedef enum {
   SPECT_DEV_ADDR = 0x39,
   SPECT_WHOAMI_REG = 0x92,
   SPECT_ATIME_REG = 0x81,
   SPECT_ASTEP_REG_L = 0xCA,
   SPECT_ASTEP_REG_H = 0xCB,
   SPECT_AGAIN_REG = 0xAA,
   SPECT_SMUX_CFG_REG = 0xAF,
   SPECT_ENABLE_REG = 0x80,
   SPECT_ASTATUS_REG = 0x94,
   SPECT_CH0_REG_L = 0x95,
   SPECT_CH0_REG_H = 0x96,
   SPECT_DATA_READY_REG = 0xA3,
} spect_reg_t;



void spectral_init(const nrf_twi_mngr_t* i2c);


uint8_t read_spectral_whoami(void);

void read_spectral_all_channels(uint16_t *buf);
