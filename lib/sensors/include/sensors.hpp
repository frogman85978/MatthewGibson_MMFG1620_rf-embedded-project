/**
 * @file sensors.h
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief All Sensors in one class
 * @version 0.1
 * @date 2025-11-13
 *
 * @copyright Copyright (c) 2025
**/


#ifndef _SENSORS_H
#define _SENSORS_H

#ifdef __cplusplus
#include <any>
#include <map>
#include <string>

class Sensors {
private:
    /* data */
public:
    Sensors(/* args */);
    ~Sensors();

    int read(void);
    std::string get_string(void);
    std::map<std::string, std::any> get_data(void);
};

#endif  // __cplusplus
#endif  // _SENSORS_H
