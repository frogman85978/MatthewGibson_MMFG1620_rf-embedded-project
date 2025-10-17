/**
 * @file button.cpp
 * @author your name (you@domain.com)
 * @brief Touch button related functions
 * @version 0.1
 * @date 2025-10-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "config.h"
#ifdef CONFIG_TOUCH_EN
#include <Arduino.h>
#include "io.h"


 // namespace Button {
class Button {
    Button::Button(void) {}
    /**
     * @brief Initialize button interface and setup interrupts
     *
     * @return int Return Status
     * @retval 0 Success
     * @retval 1 Failed
     */
    int Button::init(void) {
        return 0;  // Success
    }

    /**
     * @brief De-Initialize button interface and detach interrupts
     *
     * @return int Return Status
     * @retval 0 Success
     * @retval 1 Failed
     */
    int Button::deinit(void) {
        return 0;  // Success
    }
};

// }

#endif  // CONFIG_TOUCH_EN