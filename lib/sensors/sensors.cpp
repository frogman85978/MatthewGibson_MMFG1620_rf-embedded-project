/**
 * @file sensors.cpp
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief Contains functionality for handling sensors and reading their data
 * @version 0.1
 * @date 2025-11-21
 *
 * @copyright Copyright (c) 2025
 */

#include <Arduino.h>
#include "sensors.h"
#include <memory>

 // std::make_unique is not implemented in c++11, So do it my self
#if __cplusplus <= 201103L
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif

/**
 * @brief Construct a new Sensors::Sensors object
 */
Sensors::Sensors() {

}

/**
 * @brief Destroy the Sensors::Sensors object
 */
Sensors::~Sensors() {

}

sensor_data_t Sensors::read_all(void) {
  sensor_data_t sensor_data;

  sensor_data["battery_voltage"] = make_unique<SensorValue<float>>("Battery Voltage", 12.47f, VOLTS);
  sensor_data["cpu_temp"] = make_unique<SensorValue<int>>("CPU Temperature", 55, DEG_C);
  sensor_data["raw_adc"] = make_unique<SensorValue<uint16_t>>("RAW ADC Reading", 1234, RAW);

  std::string output;

  output += sensor_data.find("battery_voltage")->second->str_name();
  output += ", " + sensor_data.find("cpu_temp")->second->str_name();
  output += ", " + sensor_data.find("raw_adc")->second->str_name();

  printf("Sensor names: %s\n", output.c_str());

  printf("sensor name is: %s\n", sensor_data.find("raw_adc")->second->str_name().c_str());

  return sensor_data;
}

// Instantiate the sensors object
Sensors sensors = Sensors();
