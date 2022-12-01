// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf

#include <stdbool.h>
#include <stdint.h>

#include "pump.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "nrf_gpio.h"
#include "nrfx_gpiote.h"

#define LED_RED   EDGE_P13
#define LED_GREEN EDGE_P14
#define LED_BLUE  EDGE_P15

void gpio_init(void) {
  // Initialize output pins
  nrf_gpio_pin_dir_set(EDGE_P13, NRF_GPIO_PIN_DIR_OUTPUT); //LEDs
  nrf_gpio_pin_dir_set(EDGE_P14, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_dir_set(EDGE_P15, NRF_GPIO_PIN_DIR_OUTPUT);


  nrf_gpio_cfg_output(EDGE_P2);
  //nrf_gpio_cfg_output(EDGE_P1);

  // Set LEDs off initially
  nrf_gpio_pin_write(EDGE_P13, 1); //write a high to the LEDs
  nrf_gpio_pin_write(EDGE_P14, 1);
  nrf_gpio_pin_write(EDGE_P15, 1);
}

void green_light_on(void) {
  nrf_gpio_pin_write(EDGE_P14, 0); //Drive pin low to turn red on
}

void green_light_off(void) {
  nrf_gpio_pin_write(EDGE_P14, 1); //Drive pin high to turn red off
}

void turn_on_pump(void) {
    //nrf_gpio_pin_write(EDGE_P1, 0xFFFFFFFF);
    printf("test\n");
    nrf_gpio_pin_write(EDGE_P2, 1);
    nrf_delay_ms(500);
    nrf_gpio_pin_write(EDGE_P2, 0);
}
