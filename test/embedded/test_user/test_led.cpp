/**
 * @file test_led.cpp
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief Tests the function of the LEDs
 * @version 0.1
 * @date 2025-11-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <Arduino.h>
#include "unity.h"
#include "user_tests.h"
#include "io.h"

#include "user.h"

 /**
  * @brief Test the operation of the LEDs
 **/
void test_green_led_toggle(void) {
    // Turn on the LED and make sure the pin is on
    green_led.set_state(true);
    delay(100);
    TEST_ASSERT(gpio_get_level((gpio_num_t)IO_LED_2) == true);

    // Turn off the LED and make sure the led is off
    green_led.set_state(false);
    delay(100);
    TEST_ASSERT(gpio_get_level((gpio_num_t)IO_LED_2) == false);
}

/**
 * @brief Test the operation of LED 2
**/
void test_red_led_toggle(void) {
    // Turn on the LED and make sure the pin is on
    red_led.set_state(true);
    delay(100);
    TEST_ASSERT(gpio_get_level((gpio_num_t)IO_LED_1) == true);

    // Turn off the LED and make sure the led is off
    red_led.set_state(false);
    delay(100);
    TEST_ASSERT(gpio_get_level((gpio_num_t)IO_LED_1) == false);
}