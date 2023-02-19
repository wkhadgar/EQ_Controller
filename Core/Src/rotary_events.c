/**
 * Created by paulo on 12/12/2022.
 */

#include "rotary_events.h"

typedef struct {
    dir_t dir;
    bool is_pressed;
} rotary_data_t;

volatile static rotary_data_t rotary_data;

void rotary_set_dir(void) {
    rotary_data.dir = (HAL_GPIO_ReadPin(ROT_CLKW_GPIO_Port, ROT_CLKW_Pin) == GPIO_PIN_SET) ? CW : CCW;
}


void rotary_set_press(void) {
    rotary_data.is_pressed = true;
}

dir_t rotary_pop_dir(void) {
    dir_t status = NOT_MOVING;

    if (rotary_data.dir) {
        status = rotary_data.dir;
        rotary_data.dir = NOT_MOVING;
        HAL_Delay(SPIN_DEBOUNCE_DELAY);
    }

    return status;
}

bool rotary_pop_press(void) {
    bool status = false;

    if (rotary_data.is_pressed) {
        status = true;
        rotary_data.is_pressed = false;
        HAL_Delay(BUTTON_DEBOUNCE_DELAY);
    }

    return status;
}

dir_t rotary_peek_dir(void) {

    return rotary_data.dir;
}

bool rotary_peek_press(void) {

    return rotary_data.is_pressed;
}