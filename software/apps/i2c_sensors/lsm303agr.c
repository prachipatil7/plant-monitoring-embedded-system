// LSM303AGR driver for Microbit_v2
//
// Initializes sensor and communicates over I2C
// Capable of reading temperature, acceleration, and magnetic field strength

#include <stdbool.h>
#include <stdint.h>

#include "lsm303agr.h"
#include "nrf_delay.h"
#include <math.h>
void print_temp();
//float tilt_angle(void);

// Pointer to an initialized I2C instance to use for transactions
static const nrf_twi_mngr_t* i2c_manager = NULL;

// Helper function to perform a 1-byte I2C read of a given register
//
// i2c_addr - address of the device to read from
// reg_addr - address of the register within the device to read
//
// returns 8-bit read value
static uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr) {
  uint8_t rx_buf = 0;
  nrf_twi_mngr_transfer_t const read_transfer[] = {
     NRF_TWI_MNGR_WRITE(i2c_addr,
			&reg_addr,
			1,
			NRF_TWI_MNGR_NO_STOP),
     NRF_TWI_MNGR_READ(i2c_addr,
		       &rx_buf,
		       1,
		       0)
						   
						   
  };
  nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);

  return rx_buf;
}

// Helper function to perform a 1-byte I2C write of a given register
//
// i2c_addr - address of the device to write to
// reg_addr - address of the register within the device to write
static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data) {
  //TODO: implement me
  //Note: there should only be a single two-byte transfer to be performed
  uint8_t p_data[] = {reg_addr, data};
  nrf_twi_mngr_transfer_t const write_transfer[] = {
     NRF_TWI_MNGR_WRITE(i2c_addr,
			&p_data,
			2,
			0)				  						   
  };
  nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
}

// Initialize and configure the LSM303AGR accelerometer/magnetometer
//
// i2c - pointer to already initialized and enabled twim instance
void lsm303agr_init(const nrf_twi_mngr_t* i2c) {
  i2c_manager = i2c;

  // ---Initialize Accelerometer---

  // Reboot acclerometer
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG5, 0x80);
  nrf_delay_ms(100); // needs delay to wait for reboot

  // Enable Block Data Update
  // Only updates sensor data when both halves of the data has been read
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG4, 0x80);

  // Configure accelerometer at 100Hz, normal mode (10-bit)
  // Enable x, y and z axes
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_CTRL_REG1, 0x57);

  // Read WHO AM I register
  // Always returns the same value if working
  uint8_t result = i2c_reg_read(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_WHO_AM_I_REG);
  //TODO: check the result of the Accelerometer WHO AM I register
  printf("%x\n", result);

  // ---Initialize Magnetometer---

  // Reboot magnetometer
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_A, 0x40);
  nrf_delay_ms(100); // needs delay to wait for reboot

  // Enable Block Data Update
  // Only updates sensor data when both halves of the data has been read
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_C, 0x10);

  // Configure magnetometer at 100Hz, continuous mode
  i2c_reg_write(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_CFG_REG_A, 0x0C);

  // Read WHO AM I register
  result = i2c_reg_read(LSM303AGR_MAG_ADDRESS, LSM303AGR_MAG_WHO_AM_I_REG);
  //TODO: check the result of the Magnetometer WHO AM I register
  printf("%x\n", result);

  // ---Initialize Temperature---

  // Enable temperature sensor
  i2c_reg_write(LSM303AGR_ACC_ADDRESS, LSM303AGR_ACC_TEMP_CFG_REG, 0xC0);
}



// Read the internal temperature sensor
//
// Return measurement as floating point value in degrees C
float lsm303agr_read_temperature(void) {
  //TODO: implement me
  uint16_t temp_lsb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_TEMP_L);
  uint16_t temp_msb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_TEMP_H);
  // printf("L: %x, R: %x\n", temp_lsb, temp_msb);
  int16_t temp_int = (temp_msb << 8) |  temp_lsb;
  float temp = ((float) temp_int) * 1.0/256.0 + 25.0;
  return temp;
}

lsm303agr_measurement_t lsm303agr_read_accelerometer(void) {
  //TODO: implement me
  uint16_t x_lsb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_OUT_X_L);
  uint16_t y_lsb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_OUT_Y_L);
  uint16_t z_lsb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_OUT_Z_L);

  uint16_t x_msb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_OUT_X_H);
  uint16_t y_msb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_OUT_Y_H);
  uint16_t z_msb = (uint16_t) i2c_reg_read(LSM303AGR_ACC_ADDRESS,
				 LSM303AGR_ACC_OUT_Z_H);

  int16_t x_int = (int16_t)((x_msb << 8) |  x_lsb) >> 6;
  int16_t y_int = (int16_t)((y_msb << 8) |  y_lsb) >> 6;
  int16_t z_int = (int16_t)((z_msb << 8) |  z_lsb) >> 6;

  float x_acc = ((float)x_int) * 3.9/1000.0;
  float y_acc = ((float)y_int) * 3.9/1000.0;
  float z_acc = ((float)z_int) * 3.9/1000.0;
  //printf("x: %f, y: %f, z: %f\n", x_acc, y_acc, z_acc);

  lsm303agr_measurement_t measurement = {x_acc, y_acc, z_acc};
  return measurement;
}

lsm303agr_measurement_t lsm303agr_read_magnetometer(void) {
  //TODO: implement me
  uint16_t x_lsb = (uint16_t) i2c_reg_read(LSM303AGR_MAG_ADDRESS,
				 LSM303AGR_MAG_OUT_X_L_REG);
  uint16_t y_lsb = (uint16_t) i2c_reg_read(LSM303AGR_MAG_ADDRESS,
				 LSM303AGR_MAG_OUT_Y_L_REG);
  uint16_t z_lsb = (uint16_t) i2c_reg_read(LSM303AGR_MAG_ADDRESS,
				 LSM303AGR_MAG_OUT_Z_L_REG);

  uint16_t x_msb = (uint16_t) i2c_reg_read(LSM303AGR_MAG_ADDRESS,
				 LSM303AGR_MAG_OUT_X_H_REG);
  uint16_t y_msb = (uint16_t) i2c_reg_read(LSM303AGR_MAG_ADDRESS,
				 LSM303AGR_MAG_OUT_Y_H_REG);
  uint16_t z_msb = (uint16_t) i2c_reg_read(LSM303AGR_MAG_ADDRESS,
				 LSM303AGR_MAG_OUT_Z_H_REG);
  //printf("LSB: %d, %d, %d\n", x_lsb, y_lsb, z_lsb);
  // printf("MSB: %d, %d, %d\n", x_msb, y_msb, z_msb);

  int16_t x_int = (int16_t)((x_msb << 8) |  x_lsb);
  int16_t y_int = (int16_t)((y_msb << 8) |  y_lsb);
  int16_t z_int = (int16_t)((z_msb << 8) |  z_lsb);

  float x_mag = ((float)x_int) * 1.5/10.0;
  float y_mag = ((float)y_int) * 1.5/10.0;
  float z_mag = ((float)z_int) * 1.5/10.0;
  // printf("x: %f, y: %f, z: %f\n", x_mag, y_mag, z_mag);

  lsm303agr_measurement_t measurement = {x_mag, y_mag, z_mag};

  return measurement;
}

float tilt_angle(void){
  lsm303agr_measurement_t acc = lsm303agr_read_accelerometer();

  float x = acc.x_axis;
  float y = acc.y_axis;
  float z = acc.z_axis;
  // printf("x: %f, y: %f, z: %f\n", x,y,z);

  float x_sq = pow(x, 2);
  float y_sq = pow(y, 2);
  float sqr = sqrt(x_sq+y_sq);
  //printf("%f, %f, %f\n", x_sq, y_sq, sqr);
  float result = (float) atan(sqr/z);
  //printf("%lf\n", result);
  float result_deg = result*180.0/M_PI;

  return result_deg;
}
