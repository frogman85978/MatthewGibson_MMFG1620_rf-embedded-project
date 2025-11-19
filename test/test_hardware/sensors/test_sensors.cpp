/**
 * @file test_sensors.c
 * @brief Unit tests for sensors
 *
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
**/

#include "include/sensors.hpp"


extern "C" {
    #include <stdio.h>
    #include <string.h>
    Sensors * Sensors_create(void) { return new Sensors(); }
    int Sensors_read(Sensors * sensors) { return sensors->read(); }
    int Sensors_string(Sensors * sensors, char ** sens_string) {
        std::string sens_str = sensors->get_string();

        *sens_string = (char *)malloc(sens_str.length());
        memcpy(*sens_string, sens_str.c_str(), sens_str.length());

        return sens_str.length();
    }
    void Sensors_destroy(Sensors * sensors) { delete sensors; }

    #include <unity.h>
    #include <unity_test_runner.h>

    TEST_CASE("Sensor - Full", "[SENS]") {
        // Setup the sensors object
        Sensors * sensors = Sensors_create();

        // Read the sensor data
        Sensors_read(sensors);

        // Convert the sensor data to a string
        char * sens_string = NULL;
        int len = Sensors_string(sensors, &sens_string);

        printf("Received: %.*s\n", len, sens_string);

        // Destroy the sensors object
        Sensors_destroy(sensors); sensors = NULL;
    }
}