/**
 * @file led.cpp
 * @brief LED related functions
 * These functions are for the LED class.
 *
 * @author Matthew Gibson (frogman85978@gmail.com)
 * @version 0.1
 * @date 2025-10-03
 *
 * @copyright Copyright (c) 2025
**/

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <vector>
#include "user.h"
#include "io.h"

/* ====================  Blink Manager Class  ==================== */

class BlinkManager {
public:
    static BlinkManager & getInstance() {
        static BlinkManager instance;
        return instance;
    }

    /* ----------  Registration Functions  ---------- */

    /**
     * @brief  Checks if the LED is currently registered with the blink task
     *
     * @param led The led object to check for
     * @return true The LED object passed in is currently registered
     * @return false The LED object passed in is not currently registered
     */
    bool isRegistered(LED * led) {
        xSemaphoreTake(mutex, portMAX_DELAY);
        bool registered = isRegisteredInternal(led);
        xSemaphoreGive(mutex);
        return registered;
    }


    void registerLED(LED * led) {
        xSemaphoreTake(mutex, portMAX_DELAY);
        // Make sure the LED isn't already registered
        if (isRegisteredInternal(led)) {
            return;
        }
        leds.push_back(led);
        xSemaphoreGive(mutex);
    }

    void unregisterLED(LED * led) {
        xSemaphoreTake(mutex, portMAX_DELAY);
        // Find the instance of the LED in the list of registered LEDs
        for (auto led_instance = leds.begin(); led_instance != leds.end(); ++led_instance) {
            if (*led_instance == led) {
                leds.erase(led_instance);
                break;
            }
        }
        xSemaphoreGive(mutex);
    }

    /**
     * @brief Starts the LED Blink task
     */
    void start(void) {
        if (led_blink_task_handle == nullptr) {
            xTaskCreate(blinkTaskHandler, "BlinkManager", 2048, this, 2, nullptr);
        }
    }

private:
    // Class Constructors
    BlinkManager(void) { mutex = xSemaphoreCreateMutex(); }
    BlinkManager(const BlinkManager &) = delete;
    BlinkManager & operator=(const BlinkManager &) = delete;

    // Vector used to store the LEDs attached to the blink task
    std::vector<LED *> leds;

    // Task handle for LED flashing
    TaskHandle_t led_blink_task_handle = NULL;

    // Semaphore for thread safety
    SemaphoreHandle_t mutex;


    /* ----------  Task Handler  ---------- */

    /**
     * @brief Blink task handler
     */
    static void blinkTaskHandler(void * pvParameters) {
        BlinkManager * manager = static_cast<BlinkManager *>(pvParameters);
        TickType_t lastWakeTime = xTaskGetTickCount();
        for (;;) {
            TickType_t now = xTaskGetTickCount();
            xSemaphoreTake(manager->mutex, portMAX_DELAY);

            for (auto & led : manager->leds) {
                led->update(now);
            }
            xSemaphoreGive(manager->mutex);
            vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(10));
        }
    }

    /**
     * @brief Checks if the passed led object is registered
     *
     * @param led LED object to check registration status of
     * @return true The LED object passed is currently registered
     * @return false The LED object passed is NOT currently registered
     */
    bool isRegisteredInternal(LED * led) {
        for (auto * led_i : leds) {
            if (led_i == led) return true;
        }
        return false;
    }
};


/* ====================  LED Class  ==================== */

class LED {
private:
    uint8_t pin;  // Var used to store the pin number for the LED
    TickType_t period;  // The period to blink the LED at
    TickType_t phaseOffset;  // The phase offset to apply to the LED blink
    TickType_t lastToggle;  // The time of the last LED toggle

    // void update(TickType_t now) {
    // TODO
        // TickType_t elapsed = (now + phaseOffset) % period;
    // }
public:
    /* --------------------  Setup Functions  -------------------- */
    static void update(TickType_t now);

    /**
     * @brief Construct a new LED::LED object
     * This object is used to control the external LEDs
     * @param pin
     */
    LED(const uint8_t pinNum) {
        this->pin = pinNum;

        pinMode(this->pin, OUTPUT);
    }

    /**
     * @brief Destroy the LED::LED object
     * Resets pin to Input
     */
    ~LED() {
        // TODO add function to stop blinking the LED
        pinMode(this->pin, INPUT);
    }


    /* --------------------  Blink Functions  -------------------- */

    /**
     * @brief Start blinking the LED at a specified period and phase offset from the other LEDs
     *
     * @param period The period to blink the LEDs at
     * @param phaseOffset The phase offset to blink this led compared to the other LEDs
     */
    void start_blinking(const TickType_t period, const TickType_t phaseOffset = 0) {
        this->period = period;
        this->phaseOffset = phaseOffset;

        // TODO
    }

    /**
     * @brief Stops the led from blinking
     */
    void stop_blinking(void) {
        // TODO
    }
    void on(void) {

    }

};



/* ====================  LED Initializers  ==================== */

LED red_led(IO_LED_1);
LED green_led(IO_LED_2);
