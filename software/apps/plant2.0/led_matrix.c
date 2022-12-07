// LED Matrix Driver
// Displays characters on the LED matrix

#include <stdbool.h>
#include <stdio.h>

#include "nrf_gpio.h"
#include "app_timer.h"

#include "led_matrix.h"
#include "font.h"
#include "microbit_v2.h"

APP_TIMER_DEF(char_timer);
APP_TIMER_DEF(timer_1);

uint32_t second = 32768;
uint32_t active_row = 0;

char** strings = NULL;
uint32_t str_index = 0;
uint32_t num_strings = 0;
char* active_string = NULL;
uint32_t char_index = 0;

row_leds[] = {LED_ROW1, LED_ROW2, LED_ROW3, LED_ROW4, LED_ROW5};
col_leds[] = {LED_COL1, LED_COL2, LED_COL3, LED_COL4, LED_COL5};

led_states[5][5] = {false};

void clear_led() {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            led_states[row][col] = false; // By default
        }
    }
}

void bar_led(uint16_t temp_pos, uint16_t hum_pos) {
    clear_led();
    led_states[0][temp_pos] = true;
    led_states[1][temp_pos] = true;
    led_states[3][hum_pos] = true;
    led_states[4][hum_pos] = true;
}

void temp_humidity_bar(float temp, float rh) {
    float ideal_temp = 23;
    float temp_interval = 2;
    float ideal_humidity = 40; //Should do 50
    float humidity_interval = 1; //Should do 5

    uint16_t temp_pos;
    if (temp >= ideal_temp+temp_interval*2) {
        temp_pos = 4;
    }
    else if (temp >= ideal_temp+temp_interval) {
        temp_pos = 3;
    }
    else if (temp >= ideal_temp) {
        temp_pos = 2;
    }
    else if (temp >= ideal_temp-temp_interval) {
        temp_pos = 1;
    }
    else {
        temp_pos = 0;
    }

    uint16_t hum_pos;
    if (rh >= ideal_humidity+humidity_interval*2) {
        hum_pos = 4;
    }
    else if (rh >= ideal_humidity+humidity_interval) {
        hum_pos = 3;
    }
    else if (rh >= ideal_humidity) {
        hum_pos = 2;
    }
    else if (rh >= ideal_humidity-humidity_interval) {
        hum_pos = 1;
    }
    else {
        hum_pos = 0;
    }

    bar_led(temp_pos, hum_pos);
}

static void modify_row(void* _unused) {
    //Inactivate Previous Row
    if (active_row == 0) {
        nrf_gpio_pin_clear(row_leds[4]);
    }
    else {
        nrf_gpio_pin_clear(row_leds[active_row-1]);
    }

    //Activate New Row
    nrf_gpio_pin_set(row_leds[active_row]);
    for (int i = 0; i < 5; i++) {
        if (led_states[active_row][i]) {
            nrf_gpio_pin_clear(col_leds[i]);
        }
        else {
            nrf_gpio_pin_set(col_leds[i]);
        }
    }

    active_row += 1;
    if (active_row > 4) {
        active_row = 0;
    }
}

void led_matrix_init(void) {
    for(int i = 0; i < 5; i++) {
        // initialize row pins
        nrf_gpio_pin_dir_set(row_leds[i], NRF_GPIO_PIN_DIR_OUTPUT);
        nrf_gpio_pin_clear(row_leds[i]);
        // initialize col pins
        nrf_gpio_pin_dir_set(col_leds[i], NRF_GPIO_PIN_DIR_OUTPUT);
        nrf_gpio_pin_clear(col_leds[i]);
    }

    app_timer_init();
    app_timer_create(&timer_1, APP_TIMER_MODE_REPEATED, modify_row);
    app_timer_start(timer_1, second/500, NULL);
}
