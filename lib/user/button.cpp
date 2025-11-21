/**
 * @file button.cpp
 * @author your name (you@domain.com)
 * @brief Push button related functions
 * @version 0.1
 * @date 2025-10-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "user.h"
#include "io.h"
#include "config.h"
#ifndef CONFIG_TOUCH_EN
#include <Arduino.h>

 /**
  * @brief Construct a new Button:: Button object
  * This object is used to interface with the touch buttons
  * @param pinNum The pin number the LED is attached to
  */
Button::Button(const uint8_t pinNum) {
    this->pin = (gpio_num_t)pinNum;
    gpio_set_direction(this->pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(this->pin, GPIO_PULLDOWN_ONLY);
}

Button::~Button() {}

/**
 * @brief Initialize button interface and setup interrupts
 *
 * @param interrupt_function The function to call when an interrupt to ocur
 */
void Button::attachInterrupt(void (*interrupt_function)()) {
    gpio_intr_enable(this->pin);
    gpio_set_intr_type(this->pin, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(this->pin, (void (*)(void *))interrupt_function, NULL);
}

/**
 * @brief Detach the Interrupt from the button
 */
void Button::detachInterrupt(void) {
    gpio_intr_disable(this->pin);
    gpio_set_intr_type(this->pin, GPIO_INTR_DISABLE);
    gpio_isr_handler_remove(this->pin);
}

/* --------------------  Setup Buttons  -------------------- */
Button button1(IO_BUTTON_1);
Button button2(IO_BUTTON_2);
Button button3(IO_BUTTON_3);


#endif  // CONFIG_BUTTON_EN