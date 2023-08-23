/**
 * Created by paulo on 12/12/2022.
 */

#include "rotary_events.h"

typedef struct {
	dir_t dir;
	bool is_press;
} rotary_data_t;

volatile static rotary_data_t rotary_data;

void rotary_set_dir(void) {
	rotary_data.dir = (HAL_GPIO_ReadPin(ROT_CLKW_GPIO_Port, ROT_CLKW_Pin) == GPIO_PIN_SET) ? CW : CCW;
}


void rotary_set_press(void) {
	rotary_data.is_press = true;
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