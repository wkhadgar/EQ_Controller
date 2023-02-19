/**
 * Created by paulo on 12/12/2022.
 */

#ifndef EQ_CONTROLLER_ROTARY_EVENTS_H
#define EQ_CONTROLLER_ROTARY_EVENTS_H

#include "main.h"

#define SPIN_DEBOUNCE_DELAY 25
#define BUTTON_DEBOUNCE_DELAY 50

typedef enum {
    CCW = -1,
    NOT_MOVING = 0,
    CW = 1,
} dir_t;

void rotary_set_dir(void);

void rotary_set_press(void);

dir_t rotary_pop_dir(void);

bool rotary_pop_press(void);

dir_t rotary_peek_dir(void);

bool rotary_peek_press(void);

#endif //EQ_CONTROLLER_ROTARY_EVENTS_H