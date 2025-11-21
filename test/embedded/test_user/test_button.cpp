/**
 * @file test_touch.cpp
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief Test the functionality of the touch inputs
 * @version 0.1
 * @date 2025-11-19
 *
 * @copyright Copyright (c) 2025
 *
**/

#include "config.h"
#include <Arduino.h>
#include "unity.h"
#include "user_tests.h"
#include <user.h>

bool button_1_pressed = false;
bool button_2_pressed = false;
bool button_3_pressed = false;

IRAM_ATTR void button1_isr(void) {
    button_1_pressed = true;
}

IRAM_ATTR void button2_isr(void) {
    button_2_pressed = true;
}

IRAM_ATTR void button3_isr(void) {
    button_3_pressed = true;
}

#define TIMEOUT 10000

/**
 * @brief Test button 1
**/
void test_button_1(void) {
    /* --------------------  Test Button 1  -------------------- */
    button1.attachInterrupt(button1_isr);

    printf("Press button 1 NOW \n");

    unsigned long startTime = millis();
    while (millis() - startTime < TIMEOUT) {
        if (button_1_pressed) {
            button1.detachInterrupt();
            TEST_PASS();
        }
    }

    // Function Timed out
    TEST_FAIL_MESSAGE("Button press not detected after 10s");
}

/**
 * @brief Test button 2
 */
void test_button_2(void) {
    /* --------------------  Test Button 2  -------------------- */
    button2.attachInterrupt(button2_isr);

    printf("Press button 2 NOW \n");

    unsigned long startTime = millis();
    while (millis() - startTime < TIMEOUT) {
        if (button_2_pressed) {
            button2.detachInterrupt();
            TEST_PASS();
        }
    }

    // Function Timed out
    TEST_FAIL_MESSAGE("Button press not detected after 10s");
}

/**
 * @brief Test button 3
 */
void test_button_3(void) {
    /* --------------------  Test Button 3  -------------------- */
    button3.attachInterrupt(button3_isr);

    printf("Press button 3 NOW \n");

    unsigned long startTime = millis();
    while (millis() - startTime < TIMEOUT) {
        if (button_3_pressed) {
            button3.detachInterrupt();
            TEST_PASS();
        }
    }

    // Function Timed out
    TEST_FAIL_MESSAGE("Button press not detected after 10s");
}