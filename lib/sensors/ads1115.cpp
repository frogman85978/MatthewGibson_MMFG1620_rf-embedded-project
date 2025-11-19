/**
 * @file ads1115.cpp
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief ADS1115 sensor library
 * @version 0.1
 * @date 2025-11-13
 *
 * @copyright Copyright (c) 2025
**/

#include "include/sensors_common.hpp"
#include "esp-idf-lib/ads111x.h"
#include <stdio.h>

#include <string>

ads1115_t an_in_0;  // Light Sensor
ads1115_t an_in_1;  // NTC
ads1115_t an_in_2;  // TC1046
ads1115_t an_in_3;  // A2D A3

void ads1115_init(void) {
    // Configure the I2C settings for all sensors to the same
    an_in_0 = an_in_1 = an_in_2 = an_in_3 = ads1115_config(I2C_NUM_0, 0x90);

    /* ----------  Light Sensor  ---------- */
    ads1115_set_mux(&an_in_0, ADS1115_MUX_0_GND);  // Read Ain0 vs GND
    ads1115_set_pga(&an_in_0, ADS1115_FSR_4_096);  // ±4.096V range
    ads1115_set_mode(&an_in_0, ADS1115_MODE_SINGLE);      // single-shot mode
    ads1115_set_sps(&an_in_0, ADS1115_SPS_128);           // 128 samples per second
    ads1115_set_max_ticks(&an_in_0, pdMS_TO_TICKS(100));  // Set I2C timeout 

    ads1115_set_mux(&an_in_1, ADS1115_MUX_1_GND);  // Read Ain1 vs GND
    ads1115_set_pga(&an_in_1, ADS1115_FSR_4_096);  // ±4.096V range
    ads1115_set_mode(&an_in_1, ADS1115_MODE_SINGLE);      // single-shot mode
    ads1115_set_sps(&an_in_1, ADS1115_SPS_128);           // 128 samples per second
    ads1115_set_max_ticks(&an_in_1, pdMS_TO_TICKS(100));  // Set I2C timeout 

    ads1115_set_mux(&an_in_2, ADS1115_MUX_2_GND);  // Read Ain2 vs GND
    ads1115_set_pga(&an_in_2, ADS1115_FSR_4_096);  // ±4.096V range
    ads1115_set_mode(&an_in_2, ADS1115_MODE_SINGLE);      // single-shot mode
    ads1115_set_sps(&an_in_2, ADS1115_SPS_128);           // 128 samples per second
    ads1115_set_max_ticks(&an_in_2, pdMS_TO_TICKS(100));  // Set I2C timeout 

    ads1115_set_mux(&an_in_3, ADS1115_MUX_3_GND);  // Read Ain3 vs GND
    ads1115_set_pga(&an_in_3, ADS1115_FSR_4_096);  // ±4.096V range
    ads1115_set_mode(&an_in_3, ADS1115_MODE_SINGLE);      // single-shot mode
    ads1115_set_sps(&an_in_3, ADS1115_SPS_128);           // 128 samples per second
    ads1115_set_max_ticks(&an_in_3, pdMS_TO_TICKS(100));  // Set I2C timeout 
}

void ads1115_read(void) {
    double an_io_0_voltage = ads1115_get_voltage(&an_in_0);
    printf("Voltage Reading %.4f V\n", an_io_0_voltage);

}

std::string ads1115_string(void) {
    return "Hello";
}
