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
#include "config.h"
#ifndef CONFIG_TOUCH_EN
#include <Arduino.h>
#include "io.h"

 // class Button {
 // public:

/**
 * @brief Initialize button interface and setup interrupts
 *
 * @return int Return Status
 * @retval 0 Success
 * @retval 1 Failed
 */
int init(void) {
    return 0;  // Success
}

/**
 * @brief De-Initialize button interface and detach interrupts
 *
 * @return int Return Status
 * @retval 0 Success
 * @retval 1 Failed
 */
int deinit(void) {
    return 0;  // Success
}

// }

#endif  // CONFIG_BUTTON_EN