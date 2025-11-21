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

 // Threshold for touch triggers
#define TOUCH_THRESH 1000

 /**
  * @brief Construct a new Button:: Button object
  * This object is used to interface with the touch buttons
  * @param pinNum The pin number the LED is attached to
  */
Button::Button(const uint8_t pinNum) {
    this->pin = (gpio_num_t)pinNum;
    gpio_set_direction(this->pin, GPIO_MODE_INPUT);

    this->threshold_value = touchRead(pinNum) + TOUCH_THRESH;
}

Button::~Button() {}

/**
 * @brief Initialize button interface and setup interrupts
 *
 * @param interrupt_function The function to call when an interrupt to ocur
 */
void Button::attachInterrupt(void (*interrupt_function)()) {
    touchAttachInterrupt(this->pin, interrupt_function, this->threshold_value);
}

/**
 * @brief Detach the Interrupt from the button
 */
void Button::detachInterrupt(void) {
    touchDetachInterrupt(this->pin);
}

/* --------------------  Setup Buttons  -------------------- */
Button button1(IO_BUTTON_1);
Button button2(IO_BUTTON_2);
Button button3(IO_BUTTON_3);

#endif  // CONFIG_TOUCH_EN