/**
 * @file rotary_events.h
 * @author Paulo Santos (pauloxrms@gmail.com)
 * @brief Declares rotary encoder behaviour.
 * @version 0.1
 * @date 15-06-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef EQ_CONTROLLER_ROTARY_EVENTS_H
#define EQ_CONTROLLER_ROTARY_EVENTS_H

#include "main.h"
#include "tim.h"

/**
 * @brief Debounce delay to consider the next rotation event.
 */
#define SPIN_DEBOUNCE_DELAY 25

/**
 * @brief Debounce delay to consider the next press/release event.
 */
#define BUTTON_DEBOUNCE_DELAY 75

/**
 * @brief Enumerates the possible movement statuses.
 */
typedef enum {
    ROTARY_CCW        = -1,
    ROTARY_NOT_MOVING = 0,
    ROTARY_CW         = 1,
} dir_t;

/*
 * @brief Enumerates the possible press statuses.
 */
typedef enum {
    ROTARY_NOT_PRESSED = 0,
    ROTARY_SHORT_PRESS,
    ROTARY_LONG_PRESS,
} press_t;

/**
 * @brief This function should be called every time the rotary encoder is rotated, via IRQ
 * or polling.
 */
void rotary_set_dir(void);

/**
 * @brief This function should be called every time the rotary encoder is pressed, via IRQ
 * or polling.
 */
void rotary_set_press(void);

/**
 * @brief This function should be called every time the rotary encoder is released, via
 * IRQ or polling.
 */
void rotary_set_release(void);

/**
 * @brief Checks if there has been any recent rotation of the rotary encoder, also resets
 * its status to no movement.
 *
 * @return dir_t Latest movement direction.
 */
dir_t rotary_pop_dir(void);

/**
 * @brief Checks if there has been any recent pressing of the rotary encoder, also resets
 * its status to unpressed.
 *
 * @return press_t Latest press type.
 */
press_t rotary_pop_press(void);

/**
 * @brief Checks if there has been any recent rotation of the rotary encoder.
 *
 * @return dir_t Latest movement direction.
 */
dir_t rotary_peek_dir(void);

/**
 * @brief Checks if there has been any recent pressing of the rotary encoder.
 *
 * @return press_t Latest press type.
 */
press_t rotary_peek_press(void);

#endif /* EQ_CONTROLLER_ROTARY_EVENTS_H */