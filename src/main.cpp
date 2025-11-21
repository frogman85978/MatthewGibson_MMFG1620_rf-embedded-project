#include <Arduino.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/touch_sensor.h>
// #include "sdkconfig.h"
#include "io.h"

#define IO_LED_1 0
bool t1 = false;
bool t2 = false;
bool t3 = false;

static void IRAM_ATTR touch_isr(void * arg) {
    uint32_t pad_intr = touch_pad_get_status();
    touch_pad_clear_status();
    for (int i = 0; i < TOUCH_PAD_MAX; i++) {
        if (pad_intr & (1UL << i)) {
            // Handle individual pad event here
            switch (i) {
                case TOUCH_PAD_NUM5:
                    t1 = true;
                    break;
                case TOUCH_PAD_NUM6:
                    t2 = true;
                    break;
                case TOUCH_PAD_NUM7:
                    t3 = true;
                    break;
                default:
                    break;
            }
        }
    }
}
void setup(void) {
    // Install the IO interrupt service
    gpio_install_isr_service(0);
}

void loop(void) {

}

// extern "C" void app_main() {
    /* --------------------  Setup Display  --------------------*/
    /* --------------------  Setup Sensors  --------------------*/
    /* --------------------  Setup LEDs  --------------------*/

    // gpio_set_direction((gpio_num_t)IO_LED_1, GPIO_MODE_OUTPUT);
    // gpio_set_direction((gpio_num_t)IO_BUTTON_1, GPIO_MODE_INPUT);
    // gpio_set_direction((gpio_num_t)IO_BUTTON_2, GPIO_MODE_INPUT);
    // gpio_set_direction((gpio_num_t)IO_BUTTON_3, GPIO_MODE_INPUT);

    // ESP_ERROR_CHECK(touch_pad_init());
    // touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    // touch_pad_set_voltage(TOUCH_HVOLT_MAX, TOUCH_LVOLT_MAX, TOUCH_HVOLT_ATTEN_MAX);
    // ESP_ERROR_CHECK(touch_pad_config(TOUCH_PAD_NUM5, 0));
    // ESP_ERROR_CHECK(touch_pad_config(TOUCH_PAD_NUM6, 0));
    // ESP_ERROR_CHECK(touch_pad_config(TOUCH_PAD_NUM7, 0));

    // touch_pad_filter_start(10);

    // touch_pad_t touch_pads[3] = {
    //     TOUCH_PAD_NUM5,
    //     TOUCH_PAD_NUM6,
    //     TOUCH_PAD_NUM7
    // };

    // // Calibrate pads
    // uint16_t base;
    // for (int i = 0; i < 3; i++) {
    //     touch_pad_read_filtered(touch_pads[i], &base);
    //     uint32_t thresh = base * 0.8;
    //     touch_pad_set_thresh(touch_pads[i], thresh);
    //     printf("Pad %d base=%d threshold=%lu\n", i, base, thresh);
    // }

    // touch_pad_isr_register(touch_isr, NULL);
    // touch_pad_intr_enable();

    //     ESP_ERROR_CHECK(touch_pad_filter_start(10));



    //     for (;;) {
    //         if (t1) {
    //             t1 = false;
    //             printf("t1 pressed\n");
    //         }

    //         if (t2) {
    //             t2 = false;
    //             printf("t2 pressed\n");
    //         }

    //         if (t3) {
    //             t3 = false;
    //             printf("t3 pressed\n");
    //         }

    //         vTaskDelay(100 / portTICK_PERIOD_MS);
    //         // uint16_t touch_value_1 = 0;
    //         // uint16_t touch_value_2 = 0;
    //         // uint16_t touch_value_3 = 0;
    //         // touch_pad_read_filtered(TOUCH_PAD_NUM5, &touch_value_1);
    //         // touch_pad_read_filtered(TOUCH_PAD_NUM6, &touch_value_2);
    //         // touch_pad_read_filtered(TOUCH_PAD_NUM7, &touch_value_3);
    //         // printf("%d, %d, %d\r", touch_value_1, touch_value_2, touch_value_3);
    //         // ESP_LOGI("MAIN", "%d", touch_value);

    //         // gpio_set_level((gpio_num_t)IO_LED_1, 1);
    //         // vTaskDelay(500 / portTICK_PERIOD_MS);
    //         // gpio_set_level((gpio_num_t)IO_LED_1, 0);
    //         // vTaskDelay(500 / portTICK_PERIOD_MS);
    //     }
    // }