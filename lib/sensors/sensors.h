/**
 * @file sensors.h
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief Contains functions for reading and setting up sensors
 * @version 0.1
 * @date 2025-11-21
 *
 * @copyright Copyright (c) 2025
 */
#ifndef SENSORS_H
#define SENSORS_H

#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <typeinfo>

typedef enum {
    /* ----------  Digital  ---------- */

    /* ----------  Electricity  ---------- */
    VOLTS,  // Voltage
    AMPS,   // Amps

    /* ----------  Temperature  ---------- */
    DEG_C,  // Degrees Celsius
    DEG_F,  // Degrees Fahrenheit 

    /* ----------  Angle  ---------- */
    DEG,    // Degrees

    /* ----------  Speed  ---------- */
    MM_S,   // mm/s
    M_S,    // m/s

    /* ----------  Light  ---------- */

    /* ----------  Raw  ---------- */
    RAW,    // RAW Value
} sensor_units_t;

static const char * unit_string[] = {
    /* ----------  Digital  ---------- */

    /* ----------  Electricity  ---------- */
    [VOLTS] = "V",
    [AMPS] = "A",

    /* ----------  Temperature  ---------- */
    [DEG_C] = "°C",
    [DEG_F] = "°F",

    /* ----------  Angle  ---------- */
    [DEG] = "°",

    /* ----------  Speed  ---------- */
    [MM_S] = "mm/s",
    [M_S] = "m/s",

    /* ----------  Light  ---------- */

    /* ----------  Raw  ---------- */
    [RAW] = "",
};

/**
 * @brief Base class for all sensors
 */
class SensorBase {
public:
    virtual ~SensorBase() = default;

    // Return value to string (e.g. "12.5")
    virtual std::string str_value() const = 0;

    // Return Convert value + unit to string (e.g. "12.5V")
    virtual std::string str_value_unit() const = 0;

    // Return name + value + unit to string (e.g. "Battery: 12.5V")
    virtual std::string str_name_value_unit() const = 0;

    // Return the name of the sensor (e.g. "Battery")
    virtual std::string str_name() const = 0;

    // Return the units of the sensor
    virtual std::string str_units() const = 0;

    // // Return typeid(T)so callers can discover the underlying type
    // virtual const std::type_info & type() const = 0;

    // Return the unit of the sensor
    virtual sensor_units_t units() const = 0;
};


/**
 * @brief Templated derived sensor class
 */
template<typename T>
class SensorValue :public SensorBase {
private:
    T value_;
    std::string name_;
    sensor_units_t units_;
public:

    SensorValue(std::string name, T initial, sensor_units_t units)
        : name_(name), value_(initial), units_(units) {}

    // Set the value
    void set(T v) {
        value_ = v;
    }

    // Retrieve the value
    T get(void) const {
        return value_;
    }

    std::string str_value() const override {
        std::ostringstream ss;
        ss << value_;
        return ss.str();
    }

    std::string str_value_unit() const override {
        std::ostringstream ss;
        ss << value_ << " " << unit_string[units_];
        return ss.str();
    }

    std::string str_name_value_unit() const override {
        std::ostringstream ss;
        ss << name_ << ": " << value_ << " " << unit_string[units_];
        return ss.str();
    }

    std::string str_name() const override {
        std::ostringstream ss;
        ss << name_;
        return ss.str();
    }

    std::string str_units() const override {
        std::ostringstream ss;
        ss << unit_string[units_];
        return ss.str();
    }

    // const std::type_info & type() const override {
    //     return type(value_);
    // }

    sensor_units_t units() const override {
        return units_;
    }
};

// Data type for storing sensor data
typedef std::map<std::string, std::unique_ptr<SensorBase>> sensor_data_t;


/**
 * @brief Class for handling external sensors
 *
 */
class Sensors {
private:
    /* data */
public:
    Sensors();
    ~Sensors();

    sensor_data_t read_all(void);

};

extern Sensors sensors;

#endif  // SENSORS_H

