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
#include "lsm303agr.h"
#include "sensors.h"
#include "app_timer.h"

APP_TIMER_DEF(TEMP_TIMER);
//void print_temp();
void print_test() {
  //printf("Temp: %f\n", lsm303agr_read_temperature());
  //lsm303agr_measurement_t acc = lsm303agr_read_accelerometer();
  //printf("Acceleration: x: %f, y: %f, z: %f\n", acc.x_axis, acc.y_axis, acc.z_axis);
  //lsm303agr_measurement_t mag = lsm303agr_read_magnetometer();
  // printf("Magnetism: x: %f, y: %f, z: %f\n", mag.x_axis, mag.y_axis, mag.z_axis);
  
  //float angle = tilt_angle();
  //printf("Angle: %f\n==========================================================\n", angle);

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
  
  lsm303agr_init(&twi_mngr_instance);
  
  //TODO: implement me!
  app_timer_init();
  app_timer_create(&TEMP_TIMER, APP_TIMER_MODE_REPEATED, print_test);
  app_timer_start(TEMP_TIMER, 32768*2, NULL);

  // Loop forever
  while (1) {
    // Don't put any code in here. Instead put periodic code in a callback using a timer.
    nrf_delay_ms(1000);
  }
}



