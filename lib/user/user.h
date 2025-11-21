/* User interaction functions, including display and status LED controls */
#include <Arduino.h>

#ifndef USER_H
#define USER_H

/* ====================  Display Functions  ==================== */

/* ====================  LED Functions  ==================== */
class LED {
private:
    gpio_num_t pin;  // Var used to store the pin number for the LED
    TickType_t period;  // The period to blink the LED at
    TickType_t phaseOffset;  // The phase offset to apply to the LED blink
    TickType_t lastToggle;  // The time of the last LED toggle
    bool blinkRegistered;  // True if the led is registered in the blink manager

    bool state;  // The current state of the LED
    bool is_RGB;  // True if the LED is an addressable LED

    friend class BlinkManager;

    void updateLED(TickType_t now);
public:

    /* --------------------  Setup Functions  -------------------- */

    LED(const uint8_t pinNum, const bool is_RGB = false);
    ~LED();

    void set_state(const bool state);

    void start_blinking(const int period, const int phaseOffset = 0);
    void stop_blinking(void);
};

extern LED red_led;
extern LED green_led;

/* ====================  Button Functions  ==================== */
/**
 * @brief Class containing functions for detecting button presses
 *
 */
class Button {
private:
    gpio_num_t pin;  // Var used to store the pin number for the LED
    touch_value_t threshold_value;  // Used to store the touch threshold value

public:
    Button(const uint8_t pinNum);
    ~Button();

    void attachInterrupt(void (*interrupt_function)());
    void detachInterrupt(void);
};

extern Button button1;
extern Button button2;
extern Button button3;

#endif  // USER_H