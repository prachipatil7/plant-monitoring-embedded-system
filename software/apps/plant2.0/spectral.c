// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>

#include "spectral.h"
#include "i2c_utils.h"
#include "nrf_delay.h"
#include <math.h>


// Read the moisture sensor
//
// Return measurement as [What Unit?]
uint8_t read_spectral_whoami(void) {
  uint8_t whoami = i2c_reg_read(SPECT_DEV_ADDR, SPECT_WHOAMI_REG);			       
  return whoami;
}

void disable_all_smux_channels(void) {
  for (uint16_t i=0; i < 0x14; i++) {
     i2c_reg_write(SPECT_DEV_ADDR, i, 0x0);
  }
}

void setup_channel_f1_left(void) {
   disable_all_smux_channels();
   i2c_reg_write(SPECT_DEV_ADDR, 0x01, 0x01);
}

void setup_low_channels() {
   disable_all_smux_channels();
   i2c_reg_write(SPECT_DEV_ADDR, 0x00, 0x30);
   i2c_reg_write(SPECT_DEV_ADDR, 0x01, 0x01);
   i2c_reg_write(SPECT_DEV_ADDR, 0x05, 0x42);
   i2c_reg_write(SPECT_DEV_ADDR, 0x08, 0x50);
   i2c_reg_write(SPECT_DEV_ADDR, 0x0C, 0x20);
   i2c_reg_write(SPECT_DEV_ADDR, 0x0D, 0x04);
   i2c_reg_write(SPECT_DEV_ADDR, 0x0F, 0x30);
   i2c_reg_write(SPECT_DEV_ADDR, 0x10, 0x01);
   i2c_reg_write(SPECT_DEV_ADDR, 0x11, 0x50);
   i2c_reg_write(SPECT_DEV_ADDR, 0x13, 0x06);
}

void setup_high_channels() {
   disable_all_smux_channels();
   i2c_reg_write(SPECT_DEV_ADDR, 0x03, 0x40);
   i2c_reg_write(SPECT_DEV_ADDR, 0x04, 0x02);
   i2c_reg_write(SPECT_DEV_ADDR, 0x06, 0x10);
   i2c_reg_write(SPECT_DEV_ADDR, 0x07, 0x03);
   i2c_reg_write(SPECT_DEV_ADDR, 0x08, 0x50);
   i2c_reg_write(SPECT_DEV_ADDR, 0x09, 0x10);
   i2c_reg_write(SPECT_DEV_ADDR, 0x0A, 0x03);
   i2c_reg_write(SPECT_DEV_ADDR, 0x0E, 0x24);
   i2c_reg_write(SPECT_DEV_ADDR, 0x11, 0x50);
   i2c_reg_write(SPECT_DEV_ADDR, 0x13, 0x06);
}

void enable_spectral_measurement(bool enable) {
   i2c_change_bit(SPECT_DEV_ADDR, SPECT_ENABLE_REG, 1, (int)enable);
   //printf("    EN REG: %x \n", i2c_reg_read(SPECT_DEV_ADDR, SPECT_ENABLE_REG));
}

void set_smux_low(bool f1_f4) {
   //printf("disable spectral measurement\n");
   enable_spectral_measurement(false);
   i2c_reg_write(SPECT_DEV_ADDR, SPECT_SMUX_CFG_REG, 2<<3); // set to write
   if (f1_f4) {
    setup_low_channels();
  } else {
    setup_high_channels();
  }
  //printf("enable smux\n");
  i2c_change_bit(SPECT_DEV_ADDR, SPECT_ENABLE_REG, 4, 1); // enable SMUX
  //printf("    EN REG: %x \n", i2c_reg_read(SPECT_DEV_ADDR, SPECT_ENABLE_REG));
}

bool data_is_ready(){
  uint8_t ready = i2c_reg_read(SPECT_DEV_ADDR, SPECT_DATA_READY_REG);
  return (bool) ((ready >> 6) & 1);
}

void delay_for_data() {
  while(!data_is_ready()) {
    nrf_delay_ms(2);
  }
}

uint16_t read_channel(uint8_t channel) {
   
   uint8_t lsb = i2c_reg_read(SPECT_DEV_ADDR, SPECT_CH0_REG_L + 2 * channel);
   uint16_t msb = (uint16_t) i2c_reg_read(SPECT_DEV_ADDR, SPECT_CH0_REG_H + 2 * channel);
   //printf("LSB: %d \n MSB: %d \n", lsb, msb);
   return (msb << 8) | lsb;
}

void read_status() {
  uint8_t status = i2c_reg_read(SPECT_DEV_ADDR, SPECT_ASTATUS_REG);
  //printf("   ASTATUS: %d\n", status);
}

void read_spectral_all_channels(uint16_t *buf) {
  set_smux_low(true);
  enable_spectral_measurement(true);
  delay_for_data();
  uint8_t buf_index = 0;
  
  //read low channels
  for (uint8_t channel=0; channel<4; channel++) {
    buf[buf_index] = read_channel(channel);
    buf_index++;
  }
  
  set_smux_low(false);
  enable_spectral_measurement(true);
  delay_for_data();
  
  //read high channels
  for (uint8_t channel=0; channel<6; channel++) {
    buf[buf_index] = read_channel(channel);
    buf_index++;
  }
}


void spectral_init(const nrf_twi_mngr_t* i2c) {
  i2c_init(i2c);
  
  i2c_reg_write(SPECT_DEV_ADDR, SPECT_ENABLE_REG, 1);
  
  i2c_reg_write(SPECT_DEV_ADDR, SPECT_ATIME_REG, 100);
  
  i2c_reg_write(SPECT_DEV_ADDR, SPECT_ASTEP_REG_H, 999>>8);
  i2c_reg_write(SPECT_DEV_ADDR, SPECT_ASTEP_REG_L, (uint8_t)((999<<8)>>8));

  i2c_reg_write(SPECT_DEV_ADDR, SPECT_AGAIN_REG, 9);
}



























