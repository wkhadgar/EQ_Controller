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

typedef struct {
	dir_t dir;
	bool is_press;
	bool is_release;
} rotary_data_t;

volatile static rotary_data_t rotary_data;

void rotary_set_dir(void) {
	rotary_data.dir = (HAL_GPIO_ReadPin(ROT_CLKW_GPIO_Port, ROT_CLKW_Pin) == GPIO_PIN_SET) ? CW : CCW;
}

void rotary_set_press(void) {
	rotary_data.is_press = true;
}

void rotary_set_release(void) {
    rotary_data.is_release = true;
}

dir_t rotary_pop_dir(void) {
	dir_t direction;
	
	if (rotary_data.dir) {
		direction = rotary_data.dir;
		rotary_data.dir = NOT_MOVING;
		HAL_Delay(SPIN_DEBOUNCE_DELAY);
		return direction;
	}
	
	return NOT_MOVING;
}

bool rotary_pop_release(void) {
    if (rotary_data.is_release) {
        rotary_data.is_release = false;
        HAL_Delay(BUTTON_DEBOUNCE_DELAY);
        return true;
    }

    return false;
}

bool rotary_pop_press(void) {
	if (rotary_data.is_press) {
		rotary_data.is_press = false;
		HAL_Delay(BUTTON_DEBOUNCE_DELAY);
		return true;
	}
	
	return false;
}

dir_t rotary_peek_dir(void) {
	return rotary_data.dir;
}

bool rotary_peek_press(void) {
	return rotary_data.is_press;
}

bool rotary_peek_release(void) {
    return rotary_data.is_press;
}