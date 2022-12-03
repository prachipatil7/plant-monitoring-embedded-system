#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "nrf_delay.h"
#include "nrf_twi_mngr.h"

#include "microbit_v2.h"
#include "moisture.h"
#include "temp-humidity.h"
#include "pump.h"
#include "spectral.h"
#include "app_timer.h"
#include "led_driver.h"
#include "led_matrix.h"

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

  //Initializers
  shtc3_init(&twi_mngr_instance);
  pump_init();
  soil_moisture_init();
  spectral_init(&twi_mngr_instance);
  led_init(&twi_mngr_instance);
  nrf_delay_ms(1000);

  uint16_t spectral_buf[10];

  /*char** strings = (char **)malloc(3 * sizeof(char *));
  strings[0] = "DICK";
  strings[1] = "AND Balls!";
  strings[2] = "0End";
  led_matrix_string(strings);*/
  led_matrix_init();

    // Loop forever
    while (1) {
    read_spectral_all_channels(spectral_buf);
    for (uint8_t i=0; i<10; i++) {
      printf("F%d: %d\n\r", i+1, spectral_buf[i]);
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

    temp_bar(T);


    printf("\n");
    nrf_delay_ms(2000);
  }
}



