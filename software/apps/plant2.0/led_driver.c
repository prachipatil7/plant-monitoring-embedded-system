// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf



#include "led_driver.h"


// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t *i2c_manager = NULL;

void set_pwm_frequency(uint16_t freq) {

  float prescaleval = ((27000000 / (freq * 4096.0)) + 0.5) - 1;
  uint8_t prescale = (uint8_t)prescaleval;

  printf("prescale is %d\n\r", prescale);
  
  i2c_change_bit(LED_DEV_ADDR, LED_MODE1_REG, 4, 1); // put to sleep
  i2c_reg_read(LED_DEV_ADDR, LED_PRESCALER_REG);
  i2c_reg_write(LED_DEV_ADDR, LED_PRESCALER_REG, prescale);
  
  i2c_change_bit(LED_DEV_ADDR, LED_MODE1_REG, 4, 0);
  nrf_delay_ms(5);
  i2c_change_bit(LED_DEV_ADDR, LED_MODE1_REG, 5, 1);
}

void set_pwm(uint16_t address, float power){

uint16_t on_counts = (uint16_t)(power*4096);
uint16_t off_counts = on_counts-1 + on_counts - 4096;

uint8_t lower_on = (uint8_t)((on_counts-1)&0x00ff);
uint8_t upper_on = (uint8_t)(((on_counts-1)&0x0f00)>>8);
uint8_t lower_off = (uint8_t)((off_counts)&0x00ff);
uint8_t upper_off = (uint8_t)(((off_counts)&0x0f00)>>8);


//(LED_DEV_ADDR, address, lower_on);
i2c_reg_write(LED_DEV_ADDR, address+0x1, upper_on);
i2c_reg_write(LED_DEV_ADDR, address+0x2, lower_off);
i2c_reg_write(LED_DEV_ADDR, address+0x3, upper_off);

}

void light_on(float r, float g, float b) {
    set_pwm(LED4, r);
    set_pwm(LED5, g);
    set_pwm(LED6, b);
}

void adjust_led_brightness(uint16_t *buf) {
    float ideal[3] = {30000.0,
                      25000.0,
                      12000.0};
    float avg[3] = {buf[6]*0.2 + buf[7]*0.8, //r
                    buf[3]*0.1 + buf[4]*0.8 + buf[5]*0.1, //g
                    buf[0]*0.25 + buf[1]*0.5 + buf[2]*0.25}; //b
    float power[3] = {0,0,0};

    float off = 0.001;
    float max = 0.95;

    for (uint8_t i=0; i<3; i++) {
        if (avg[i] >= ideal[i]) {
            power[i] = off;
        } else {
            power[i] = (ideal[i] - avg[i]) / ideal[i];
        }
        if (power[i] > max) {
            power[i] = max;
        }
        //printf("ideal %d: %f\n\r", i, ideal[i]);
        //printf("avg %d: %f\n\r", i, avg[i]);
        //printf("pow %d: %f\n\r", i, power[i]);
        printf("\n");
    }
    light_on(power[0], power[1], power[2]);
}


void led_init(const nrf_twi_mngr_t *i2c) {
  i2c_init(i2c);
  set_pwm_frequency(1600);
}

