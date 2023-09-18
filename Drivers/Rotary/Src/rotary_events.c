/**
 * @file rotary_events.c
 * @author Paulo Santos (pauloxrms@gmail.com)
 * @brief Defines rotary encoder behaviour.
 * @version 0.1
 * @date 15-06-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "rotary_events.h"

/*
 * @brief Maximum threshold for short press, in milliseconds.
 */
#define SHORT_PRESS_THRESHOLD 1000

typedef struct {
    dir_t dir;
    press_t press;
} rotary_data_t;

volatile static rotary_data_t rotary_data;

void rotary_set_dir(void) {
    rotary_data.dir = (HAL_GPIO_ReadPin(ROT_CLKW_GPIO_Port, ROT_CLKW_Pin) == GPIO_PIN_SET)
                          ? ROTARY_CW
                          : ROTARY_CCW;
}

void rotary_set_press(void) {
    TIM3->CNT = 0;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void rotary_set_release(void) {
    if (TIM3->CNT <= SHORT_PRESS_THRESHOLD) {
        rotary_data.press = ROTARY_SHORT_PRESS;
    } else {
        rotary_data.press = ROTARY_LONG_PRESS;
    }
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

dir_t rotary_pop_dir(void) {
    dir_t direction;

    if (rotary_data.dir) {
        direction       = rotary_data.dir;
        rotary_data.dir = ROTARY_NOT_MOVING;
        HAL_Delay(SPIN_DEBOUNCE_DELAY);
        return direction;
    }

    return ROTARY_NOT_MOVING;
}

press_t rotary_pop_press(void) {
    press_t press;

    if (rotary_data.press) {
        press             = rotary_data.press;
        rotary_data.press = ROTARY_NOT_PRESSED;
        HAL_Delay(BUTTON_DEBOUNCE_DELAY);
        return press;
    }

    return ROTARY_NOT_PRESSED;
}

dir_t rotary_peek_dir(void) {
    return rotary_data.dir;
}

press_t rotary_peek_press(void) {
    return rotary_data.press;
}