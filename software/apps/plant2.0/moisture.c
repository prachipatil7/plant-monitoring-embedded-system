#include "moisture.h"

#define ANALOG_SOIL_IN  NRF_SAADC_INPUT_AIN1
#define ADC_SOIL_CHANNEL  0

static void adc_init(void);
static float adc_sample_blocking(uint8_t channel);
static uint32_t volt_to_soil(float voltage);
static void saadc_event_callback(nrfx_saadc_evt_t const* _unused);

// Initialize the ADC and set up the soil moisture sensor
static void adc_init(void) {
  printf("in init\r\n");
  // Initialize the SAADC
  nrfx_saadc_config_t saadc_config = {
    .resolution = NRF_SAADC_RESOLUTION_12BIT,
    .oversample = NRF_SAADC_OVERSAMPLE_DISABLED,
    .interrupt_priority = 0,
    .low_power_mode = false,
  };
  ret_code_t error_code = nrfx_saadc_init(&saadc_config, saadc_event_callback);
  APP_ERROR_CHECK(error_code);

  // Initialize soil moisture sensor channel
  nrf_saadc_channel_config_t soil_channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(ANALOG_SOIL_IN);
  error_code = nrfx_saadc_channel_init(ADC_SOIL_CHANNEL, &soil_channel_config);
  APP_ERROR_CHECK(error_code);
}

static float adc_sample_blocking(uint8_t channel) {
  // read ADC counts (0-4095)
  // this function blocks until the sample is ready
  int16_t adc_counts = 0;
  ret_code_t error_code = nrfx_saadc_sample_convert(channel, &adc_counts);
  APP_ERROR_CHECK(error_code);

  // convert ADC counts to volts
  // 12-bit ADC with range from 0 to 3.3 Volts
  float voltage = adc_counts * (3.3 / 4096);

  // return voltage measurement
  return voltage;
}

static void saadc_event_callback(nrfx_saadc_evt_t const* _unused) {
  float read = adc_sample_blocking(ADC_SOIL_CHANNEL);
  float temp = volt_to_soil(read);
}

static uint32_t volt_to_soil(float voltage) {
  // soil: the soil moisture is either wet = 1 or dry = 0
  // this paper might help convert voltage to wetness
  // https://www.researchgate.net/figure/Voltage-versus-moisture-content-of-the-soil_fig5_305639219
  // or we just try it out to choose the cutoff

  uint32_t percentage = (voltage / 3.3) * 100;
  uint32_t soil = percentage > 50;

  return soil;
}
