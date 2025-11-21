#include <Arduino.h>
#include <unity.h>
#include "user_tests.h"

int runUnityTests(void) {
    UNITY_BEGIN();

    /* --------------------  LED Tests  -------------------- */
    RUN_TEST(test_green_led_toggle);
    RUN_TEST(test_red_led_toggle);

    /* --------------------  Touch Tests  -------------------- */
    RUN_TEST(test_button_1);
    RUN_TEST(test_button_2);
    RUN_TEST(test_button_3);

    return UNITY_END();
}

/**
 * For native dev-platform or for some embedded frameworks
**/
int main(void) {}

/**
 * For Arduino framework
**/
void setup(void) {
    runUnityTests();
}

void loop(void) {}

/**
 * For ESP-IDF framework
 */
void app_main() {
    runUnityTests();
}