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

void pump_init(void) {
  // Initialize output pin
  nrf_gpio_cfg_output(EDGE_P2);

  //Write low to pump
  nrf_gpio_pin_write(EDGE_P12, 0);
}

void turn_on_pump(void) {
    nrf_gpio_pin_write(EDGE_P2, 1);
    nrf_delay_ms(500);
    nrf_gpio_pin_write(EDGE_P2, 0);
}

void turn_off_pump(void) {
    nrf_gpio_pin_write(EDGE_P2, 0);
}
