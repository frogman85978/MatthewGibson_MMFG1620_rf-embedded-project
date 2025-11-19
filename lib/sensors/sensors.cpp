/**
 * @file sensors.cpp
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief General Sensor Class
 * @version 0.1
 * @date 2025-11-13
 *
 * @copyright Copyright (c) 2025
**/

#include "include/sensors.hpp"
#include "include/sensors_common.hpp"
#include <stdio.h>
#include <string>
#include "io.h"
#include <driver/i2c_master.h>

i2c_master_bus_handle_t i2c_bus_handle;
i2c_master_bus_config_t i2c_mst_config = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = (gpio_num_t)IO_I2C_SDA,
    .scl_io_num = (gpio_num_t)IO_I2C_SCL,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .intr_priority = 0,
    .trans_queue_depth = 0,
    .flags = {
        .enable_internal_pullup = 1,
    },
};

Sensors::Sensors(/* args */) {
    i2c_new_master_bus(&i2c_mst_config, &i2c_bus_handle);

    ads1115_init();
}

Sensors::~Sensors() {
    // i2c_del_master_bus(i2c_bus_handle);
    // i2c_bus_handle = NULL;
}

int Sensors::read(void) {
    printf("Hello from inside sensors.cpp\n");
    ads1115_read();

    return 0;  // Success
}

std::string Sensors::get_string(void) {
    std::string sens_string = "(Test)";
    sens_string += " Hello World";

    return sens_string;
}
