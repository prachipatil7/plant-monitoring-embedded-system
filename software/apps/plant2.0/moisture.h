#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "app_timer.h"
#include "nrf_delay.h"
#include "nrfx_saadc.h"

#include "microbit_v2.h"

void soil_moisute_init(void);

// Same functionality, maybe rounding difference
uint32_t get_soil_moisture(void);
uint32_t read_soil_moisture(void);
