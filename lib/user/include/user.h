/* User interaction functions, including display and status LED controls */

#ifndef USER_H
#define USER_H



/* ========================================  C++  ========================================  */

#ifdef __cplusplus

class LED {
private:
    uint8_t pin;  // Var used to store the pin number for the LED
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

    void start_blinking(const int period, const int phaseOffset = 0);
    void stop_blinking(void);
};

extern LED red_led;
extern LED green_led;

#endif  // __cplusplus

/* ====================  Display Functions  ==================== */

/* ====================  LED Functions  ==================== */

/* ====================  Button Functions  ==================== */
//     class Button {
//     public:
//         Button(void);

//         int init(void);
//         int deinit(void);
//     };

/* ========================================  C  ========================================  */
#ifdef __cplusplus
extern "C" {
    #endif // __cplusplus

    // TODO C code here
    typedef struct LED LED;
    LED * LED_create(const uint8_t pinNum, const bool is_RGB = false) { return new LED(pinNum, is_RGB); }

    #ifdef __cplusplus
};
#endif // __cplusplus

#endif  // USER_H