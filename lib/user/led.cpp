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

    /** * @brief Registers the passed LED to the blink task
     *
     * @param led The LED object to register
     */
    void registerLED(LED * led) {
        // Start the led blink task if its not already running
        if (led_blink_task_handle == nullptr) {
            start();
        }

        xSemaphoreTake(mutex, portMAX_DELAY);
        // Make sure the LED isn't already registered
        if (isRegisteredInternal(led)) {
            return;
        }
        leds.push_back(led);
        xSemaphoreGive(mutex);

        led->blinkRegistered = true;
    }

    /**
     * @brief Un-Register the passed LED from the blink task
     *
     * @param led The LED object to un-register
     */
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
        led->blinkRegistered = false;

        // Stop the task if there are no more LEDs in the list
        if (leds.size() == 0) {
            stop();
        }
    }

    /**
     * @brief Starts the LED Blink task
     */
    void start(void) {
        if (led_blink_task_handle == nullptr) {
            xTaskCreate(blinkTaskHandler, "BlinkManager", 2048, this, 2, &led_blink_task_handle);
        }
    }

    /**
     * @brief Stops the LED Blink task
     * @attention DO NOT CALL THIS FROM WITHIN THE BLINK TASK
     */
    void stop(void) {
        if (led_blink_task_handle != nullptr) {
            vTaskDelete(led_blink_task_handle);
            led_blink_task_handle = NULL;
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
                led->updateLED(now);
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

/* --------------------  Setup Functions  -------------------- */

/**
 * @brief Construct a new LED::LED object
 * This object is used to control the external LEDs
 * @param pinNum The pin number the LED is attached to
 * @param is_RGB Set to True if the LED is an addressable RGB LED
 */
LED::LED(const uint8_t pinNum, const bool is_RGB) {
    this->pin = (gpio_num_t)pinNum;
    this->is_RGB = is_RGB;

    pinMode(this->pin, OUTPUT);
}

/**
 * @brief Destroy the LED::LED object
 * Resets pin to Input
 */
LED::~LED() {
    stop_blinking();
    pinMode(this->pin, INPUT);
}


/* --------------------  Blink Functions  -------------------- */

/**
 * @brief Start blinking the LED at a specified period and phase offset from the other LEDs
 *
 * @param period The period to blink the LEDs at
 * @param phaseOffset The phase offset to blink this led compared to the other LEDs
 */
void LED::start_blinking(const int period, const int phaseOffset) {
    this->period = pdMS_TO_TICKS(period);
    this->phaseOffset = pdMS_TO_TICKS(phaseOffset);
    BlinkManager::getInstance().registerLED(this);
}

/**
 * @brief Stops blinking the LED
 */
void LED::stop_blinking(void) {
    BlinkManager::getInstance().unregisterLED(this);
    gpio_set_level(pin, LOW);
}

/**
 * @brief Set the LED to a specific state
 *
 * @param state The state to set the LED
 */
void LED::set_state(const bool state) {
    // Stop blinking the led if it is already
    if (this->blinkRegistered) {
        this->stop_blinking();
    }

    // Set the LED to a specific state
    gpio_set_level(pin, state);
}

/**
 * @brief Internal function used to update the LED from the LED blink task
 *
 * @param now The current time in ticks
 */
void LED::updateLED(TickType_t now) {
    TickType_t elapsed = (now + phaseOffset) % period;
    bool newState = elapsed < (period / 2);
    if (newState != state) {
        gpio_set_level(pin, newState);
        state = newState;
    }
}


/* ====================  LED Initializers  ==================== */

LED red_led(IO_LED_1);
LED green_led(IO_LED_2);
//LED rgb_led(IO_LED_RGB);