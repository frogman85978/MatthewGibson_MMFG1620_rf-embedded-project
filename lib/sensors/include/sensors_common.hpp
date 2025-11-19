/**
 * @file sensor.hpp
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief Contains classes and vars common between sensors
 * @version 0.1
 * @date 2025-11-13
 *
 * @copyright Copyright (c) 2025
**/

#ifndef _SENSOR_H
#define _SENSOR_H

#ifdef __cplusplus

#include <string>
#include <map>
#include <any>

void ads1115_init(void);
void ads1115_read(void);
std::string ads1115_string(void);


#endif  // __cplusplus

#endif  // _SENSOR_H