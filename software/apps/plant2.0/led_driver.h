#pragma once

#include "nrf_twi_mngr.h"
#include "i2c_utils.h"
#include "nrf_delay.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>


typedef enum {
   LED_DEV_ADDR = 0x40,
   LED_MODE1_REG = 0x00,
   LED_PRESCALER_REG = 0xFE,

   //LEDs
   LED4 = 0x16,
   LED5 = 0x1a,
   LED6 = 0x1e,
   LED7 = 0x22,
   LED8 = 0x26,


} led_reg_t;

void led_init(const nrf_twi_mngr_t *i2c);
void light_on(float r, float g, float b);
void adjust_led_brightness(uint16_t *buf);



