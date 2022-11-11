// I2C sensors app
//
// Read from I2C accelerometer/magnetometer on the Microbit

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "nrf_delay.h"
#include "nrf_twi_mngr.h"

#include "microbit_v2.h"
//#include "i2c_utils.h"
#include "moisture.h"
#include "app_timer.h"

//APP_TIMER_DEF(TEMP_TIMER);
//void print_temp();
void print_test() {
  printf("Moisture: %f\n", read_moisture());
}

// Global variables
NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);

int main(void) {
  printf("Board started!\n");

  // Initialize I2C peripheral and driver
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = I2C_SCL;
  i2c_config.sda = I2C_SDA;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  i2c_config.interrupt_priority = 0;
  nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

  // Initialize the LSM303AGR accelerometer/magnetometer sensor
  
  moisture_init(&twi_mngr_instance);
  //TODO: implement me!
  /*app_timer_init();
  app_timer_create(&TEMP_TIMER, APP_TIMER_MODE_REPEATED, print_test);
  app_timer_start(TEMP_TIMER, 32768*2, NULL);*/

  // Loop forever
  while (1) {
    // Don't put any code in here. Instead put periodic code in a callback using a timer.
    print_test();
    nrf_delay_ms(1000);
  }
}



