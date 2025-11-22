/**
 * @file button.cpp
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @brief Touch button related functions
 * @version 0.1
 * @date 2025-10-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "user.h"
#include "io.h"
#include "config.h"
#ifdef CONFIG_TOUCH_EN
#include <Arduino.h>
#include <driver/touch_sensor.h>
#include <map>

 // Threshold for touch triggers
#define TOUCH_THRESH 1000

/**
 * @brief Get the touch gpio num from touch num
 *
 * @param touch_pad The touch pad that was detected
 * @return gpio_num_t The corrsponding GPIO pin
 */
gpio_num_t touch_pad_to_gpio_num(const uint32_t touch_pad) {
    if (touch_pad == TOUCH_PAD_NUM0) return GPIO_NUM_4;
    if (touch_pad == TOUCH_PAD_NUM1) return GPIO_NUM_0;
    if (touch_pad == TOUCH_PAD_NUM2) return GPIO_NUM_2;
    if (touch_pad == TOUCH_PAD_NUM3) return GPIO_NUM_15;
    if (touch_pad == TOUCH_PAD_NUM4) return GPIO_NUM_13;
    if (touch_pad == TOUCH_PAD_NUM5) return GPIO_NUM_12;
    if (touch_pad == TOUCH_PAD_NUM6) return GPIO_NUM_14;
    if (touch_pad == TOUCH_PAD_NUM7) return GPIO_NUM_27;
    if (touch_pad == TOUCH_PAD_NUM8) return GPIO_NUM_33;
    if (touch_pad == TOUCH_PAD_NUM9) return GPIO_NUM_32;
    return GPIO_NUM_NC;  // Failed to find
}

/**
 * @brief Get the touch pad num from the gpio num
 *
 * @param gpio_num The gpio num to convert
 * @return touch_pad_t The corrsponding touch pad
 */
touch_pad_t gpio_num_to_touch_pad(const gpio_num_t gpio_num) {
    if (gpio_num == GPIO_NUM_4) return TOUCH_PAD_NUM0;
    if (gpio_num == GPIO_NUM_0) return TOUCH_PAD_NUM1;
    if (gpio_num == GPIO_NUM_2) return TOUCH_PAD_NUM2;
    if (gpio_num == GPIO_NUM_15) return TOUCH_PAD_NUM3;
    if (gpio_num == GPIO_NUM_13) return TOUCH_PAD_NUM4;
    if (gpio_num == GPIO_NUM_12) return TOUCH_PAD_NUM5;
    if (gpio_num == GPIO_NUM_14) return TOUCH_PAD_NUM6;
    if (gpio_num == GPIO_NUM_27) return TOUCH_PAD_NUM7;
    if (gpio_num == GPIO_NUM_33) return TOUCH_PAD_NUM8;
    if (gpio_num == GPIO_NUM_32) return TOUCH_PAD_NUM9;
    return TOUCH_PAD_MAX;  // Failed to find
}

std::map<uint8_t, void (*)()> registered_touch_isr;

// bool isr_called = false;
void IRAM_ATTR touch_isr(void * args) {
    uint32_t pad_intr = touch_pad_get_status();
    touch_pad_clear_status();

    for (int i = 0; i < TOUCH_PAD_MAX; i++) {
        // Handle each touch pad interrupt using their registered functions
        if (pad_intr & (1UL << i)) {
            gpio_num_t io_num = touch_pad_to_gpio_num(i);

            auto touch_handler = registered_touch_isr.find(io_num);
            // Make sure we have a handler registered
            if (touch_handler == registered_touch_isr.end()) {
                break;  // No function registered, skip interrupt
            }

            // Call the registered touch function
            touch_handler->second();
        }
    }
}


bool called_once = false;

/**
 * @brief Called only once to setup global touch configs
 */
void call_once(void) {
    if (called_once) return;  // Only allow us to call once


    ESP_ERROR_CHECK(touch_pad_init());
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    ESP_ERROR_CHECK(touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_0V));

    ESP_ERROR_CHECK(touch_pad_isr_register(touch_isr, NULL));
    touch_pad_intr_enable();

    called_once = true;  // Mark the function as called
}

/**
 * @brief Construct a new Button:: Button object
 * This object is used to interface with the touch buttons
 * @param pinNum The pin number the LED is attached to
 */
Button::Button(const uint8_t pinNum) {
    this->pin = (gpio_num_t)pinNum;
    gpio_set_direction(this->pin, GPIO_MODE_INPUT);
    call_once();
    touch_pad_t touch_pad = gpio_num_to_touch_pad(this->pin);

    touch_pad_config(touch_pad, 0);

    touch_pad_filter_start(10);

    // Calibrate pads
    #define AVERAGE_COUNT 10
    uint16_t averaged_value;
    for (int i = 0; i < AVERAGE_COUNT; i++) {
        uint16_t base;
        ESP_ERROR_CHECK(touch_pad_read(touch_pad, &base));

        // Check if the sensor has started reading values
        if (base == 0) {
            i--;
            continue;
        }

        averaged_value += base / AVERAGE_COUNT;
        printf("Value: %d\n", base);
    }
    printf("Final Average: %d\n", averaged_value);

    this->threshold_value = averaged_value * 0.8;
    printf("Threshold: %d\n", threshold_value);
    touch_pad_set_thresh(touch_pad, this->threshold_value);
}

Button::~Button() {}

/**
 * @brief Initialize button interface and setup interrupts
 *
 * @param interrupt_function The function to call when an interrupt to ocur
 */
void Button::attachInterrupt(void (*interrupt_function)()) {
    if (registered_touch_isr.count(this->pin) > 0) {
        printf("Attempted to attach more than one interrupt to a single pin\n");
        return;  // Error, More than one interrupt attach attempted
    }
    registered_touch_isr.insert({this->pin, interrupt_function});
}

/**
 * @brief Detach the Interrupt from the button
 */
void Button::detachInterrupt(void) {
    registered_touch_isr.erase(this->pin);
}

/* --------------------  Setup Buttons  -------------------- */
Button button1(IO_BUTTON_1);
Button button2(IO_BUTTON_2);
Button button3(IO_BUTTON_3);

#endif  // CONFIG_TOUCH_EN