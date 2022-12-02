// SHTC3 Humidity (and Temperature) Sensor
// Datasheet: https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf



#include "led_driver.h"


// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t *i2c_manager = NULL;

void set_pwm_frequency(uint16_t freq) {



  float prescaleval = ((27000000 / (freq * 4096.0)) + 0.5) - 1;
  uint8_t prescale = (uint8_t)prescaleval;
  
  
  printf("prescale is %d\n", prescale);
  
  if (freq < 1)
    freq = 1;
  if (freq > 3500)
    freq = 3500; // Datasheet limit is 3052=50MHz/(4*4096)
    
 
  if (prescaleval < 3) //3 is smallest prescale
    prescaleval = 3;
  if (prescaleval > 255) //255 is largest prescale
    prescaleval = 255;
  
  
  
  
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
/*
i2c_reg_write(LED_DEV_ADDR, 0x6 +4*pinnum, on);

i2c_reg_write(LED_DEV_ADDR, 0x6 +4*pinnum, on>>8);

i2c_reg_write(LED_DEV_ADDR, 0x6 +4*pinnum, off);
i2c_reg_write(LED_DEV_ADDR, 0x6 +4*pinnum, off>>0);
*/

uint8_t lower_on = (uint8_t)((on_counts-1)&0x00ff);
uint8_t upper_on = (uint8_t)(((on_counts-1)&0x0f00)>>8);
uint8_t lower_off = (uint8_t)((off_counts)&0x00ff);
uint8_t upper_off = (uint8_t)(((off_counts)&0x0f00)>>8);


printf("the on value is %x , %x\n", upper_on, lower_on);
printf("the lower on value is %x, %x \n", upper_off, lower_off);


(LED_DEV_ADDR, address, lower_on);
i2c_reg_write(LED_DEV_ADDR, address+0x1, upper_on);
i2c_reg_write(LED_DEV_ADDR, address+0x2, lower_off);
i2c_reg_write(LED_DEV_ADDR, address+0x3, upper_off);

}

void led_on(void) {
    printf("the led state is %u\n", i2c_reg_read(LED_DEV_ADDR, 0x16));
    //i2c_change_bit(LED_DEV_ADDR, 0x16, 4, 1);
    printf("the led  after change bit is state is %u \n", i2c_reg_read(LED_DEV_ADDR, 0x16));
}

void led_init(const nrf_twi_mngr_t *i2c) {
  i2c_init(i2c);
  set_pwm_frequency(1600);
  set_pwm(0x16, 0.9);
}

