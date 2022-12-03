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

////
char** strings = NULL;
uint32_t str_index = 0;
uint32_t num_strings = 0;
char* active_string = NULL;
uint32_t char_index = 0;
////

row_leds[] = {LED_ROW1, LED_ROW2, LED_ROW3, LED_ROW4, LED_ROW5};
col_leds[] = {LED_COL1, LED_COL2, LED_COL3, LED_COL4, LED_COL5};

led_states[5][5] = {false};

static void char_handler(void* _unused) {
    character_led(active_string[char_index]);
    char_index += 1;
    if (char_index > strlen(active_string)) { //string is completed
        str_index += 1;
        if (str_index >= num_strings) {//string array is completed
            str_index = 0;
        }
        active_string = strings[str_index];
        printf("Active: %s\n", active_string);
        char_index = 0;
    }
}

void character_led(char c) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            if ((font[c][row] >> col) & 1) {
                led_states[row][col] = true;
            }
            else {
                led_states[row][col] = false; //By default
            }
        }
    }
}

void clear_led() {
    printf("clear_led\r\n");
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            led_states[row][col] = false; //By default
        }
    }
}

void bar_led(uint16_t pos, bool is_temp) {
    printf("bar_led\r\n");
    clear_led();
    printf("cleared leds\r\n");
    if (is_temp) {
        led_states[0][pos] = true;
        led_states[1][pos] = true;
    }
}

void temp_bar(float temp) {
    printf("temp_bar\r\n");
    if (temp >= 23) {
        bar_led(2, true);
    }
    else {
        bar_led(0, true);
    }
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

    //nrf_gpio_pin_toggle(LED_COL2);
    //nrf_gpio_pin_toggle(LED_COL3);
    //printf("modified\n");

    active_row += 1;
    if (active_row > 4) {
        active_row = 0;
    }

}

void led_matrix_string(char** str_arr) {
    strings = str_arr;
    //printf("in loop: %s\n", strings[0]);
    //printf("in loop: %s\n", strings[1]);
    while(strings[str_index] != "0End") {
        // printf("in loop: %s\n", strings[str_index]);
        str_index += 1;
    }
    num_strings = str_index; ///////!!!
    str_index = 0;
    active_string = strings[0];
    printf("Active: %s\n", active_string);

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

    // initialize timer(s) (Part 3 and onwards)
    app_timer_init();
    //app_timer_create(&string_timer, APP_TIMER_MODE_REPEATED, string_led);
    //app_timer_start(string_timer, 5*second, NULL);
    //character_led('C');
    app_timer_create(&timer_1, APP_TIMER_MODE_REPEATED, modify_row);
    app_timer_start(timer_1, second/500, NULL);

    //app_timer_create(&char_timer, APP_TIMER_MODE_REPEATED, char_handler);
    //app_timer_start(char_timer, second, NULL);
    //set default state for the LED display (Part 4 and onwards)
}