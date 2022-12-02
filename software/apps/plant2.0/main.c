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
#include "temp-humidity.h"
#include "pump.h"
#include "spectral.h"
#include "app_timer.h"
#include "led_driver.h"
//APP_TIMER_DEF(TEMP_TIMER);
//void print_temp();
void print_test() {
  printf("Moisture: %ld\n", read_soil_moisture());
}

// Global variables
NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);

int main(void) {
  printf("\rBoard started!\r\n");

  // Initialize I2C peripheral and driver
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = EDGE_P19;
  i2c_config.sda = EDGE_P20;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  i2c_config.interrupt_priority = 0;
  nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

  // Initialize the LSM303AGR accelerometer/magnetometer sensor
  /*shtc3_init(&twi_mngr_instance);
  shtc3_read_temperature();
  shtc3_read_humidity();*/
  //moisture_init(&twi_mngr_instance);
  //TODO: implement me!
  /*app_timer_init();
  app_timer_create(&TEMP_TIMER, APP_TIMER_MODE_REPEATED, print_test);
  app_timer_start(TEMP_TIMER, 32768*2, NULL);*/
  spectral_init(&twi_mngr_instance);
  led_init(&twi_mngr_instance);
  nrf_delay_ms(1000);
  // Loop forever
  uint16_t buf[10];

  //Initializers
  shtc3_init(&twi_mngr_instance);
  pump_init();
  soil_moisture_init();

  //Turn pump on and off
  /*turn_on_pump();
  nrf_delay_ms(500);
  turn_off_pump();*/



    while (0) {
    //print_test();
    read_spectral_all_channels(buf);
    for (uint8_t i=0; i<10; i++) {
      printf("F%d: %d\n", i+1, buf[i]);
    }
    printf("\n");

    uint32_t is_wet = read_soil_moisture();
    if(!is_wet) {
        turn_on_pump();
        nrf_delay_ms(500);
        turn_off_pump();
        printf("Soil is DRY\r\n");
    }
    else {
        printf("Soil is WET\r\n");
    }

    float T = shtc3_read_temperature();
    float RH = shtc3_read_humidity();

    printf("TEMP: %f degC\r\n", T);
    printf("HUMIDITY: %f \r\n", RH);


    printf("\n");
    nrf_delay_ms(2000);
  }
}



