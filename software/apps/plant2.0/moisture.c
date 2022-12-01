#include "moisture.h"

#define ANALOG_SOIL_IN  NRF_SAADC_INPUT_AIN1
#define ADC_SOIL_CHANNEL  0

/**** HELPER FUNCTIONS ****/

static float adc_sample_blocking(uint8_t channel);
static uint32_t volt_to_soil(float voltage);
static void saadc_event_callback(nrfx_saadc_evt_t const* _unused);

// Read voltage from adc channel, this function blocks until the sample is ready
static float adc_sample_blocking(uint8_t channel) {
    // read ADC counts (0-4095)
    // this function blocks until the sample is ready
    int16_t adc_counts = 0;
    ret_code_t error_code = nrfx_saadc_sample_convert(channel, &adc_counts);
    APP_ERROR_CHECK(error_code);

    // convert ADC counts to volts
    // 12-bit ADC with range from 0 to 3.6 Volts
    float adc_counts_f = (float) adc_counts;
    float volts = (3.6 / 4096.0) * adc_counts_f;

    // return voltage measurement
    return volts;
}

// Event handler -- don't care about SAADC events, ignore
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

/**** ACCESSIBLE FROM MAIN.C ****/

// Initialize the ADC and set up the soil moisture sensor
void soil_moisture_init(void) {
  printf("in soil_moisture_init\r\n");
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

// Returns if the soil is wet or dry based on percentage of 3.3V
// Uses all the helpers
uint32_t get_soil_moisture(void) {
  printf("in get_soil_moisture");
  // Read sensor
  float voltage = adc_sample_blocking(ADC_SOIL_CHANNEL);
  // Get wet or dry
  uint32_t soil = volt_to_soil(voltage);
  // Return
  printf("Soil is %d (0=dry,1=wet)\r\n", soil);
  return soil;
}

// Returns if the soil is wet or dry based on percentage of 3.3V
// Can modify to return based on actual voltage
// No helpers
uint32_t read_soil_moisture(void) {
  //printf("in read_soil_moisture");
  // read ADC counts (0-4095)
  /*int16_t adc_counts = 0;
  ret_code_t error_code = nrfx_saadc_sample_convert(ADC_SOIL_CHANNEL, &adc_counts);
  APP_ERROR_CHECK(error_code);*/

  // convert ADC counts into voltage and percentage
  float total = 0;
  for(uint16_t i = 0; i < 100; i++) {
      total += adc_sample_blocking(0);
  }
  float avg_voltage = total / 100;
  float percentage = avg_voltage*100 / 3.3;

  // soil: the soil moisture is either wet = 1 or dry = 0
  bool soil = percentage >= 99; //was 50 as per js code
  //Around 95 or below is dry soil
  //Around 99-100 or above is wet soil

  printf("avg_voltage: %f, percentage: %f\r\n", avg_voltage, percentage);
  printf("Soil is %d (0=dry,1=wet)\r\n", soil);
  if (soil){
      printf("WET\r\n");
  }
  else {
      printf("DRY\r\n");
  }
  return soil;
}