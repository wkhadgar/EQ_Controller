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
    CCW = -1,
    NOT_MOVING = 0,
    CW = 1,
} dir_t;

/**
 * @brief This function should be called every time the rotary encoder is rotated, via IRQ or polling.
 */
void rotary_set_dir(void);

/**
 * @brief This function should be called every time the rotary encoder is pressed, via IRQ or polling.
 */
void rotary_set_press(void);

/**
 * @brief This function should be called every time the rotary encoder is released, via IRQ or polling.
 */
void rotary_set_release(void);

/**
 * @brief Checks if there has been any recent rotation of the rotary encoder, also resets its status to no movement.
 *
 * @return dir_t Latest movement direction.
 */
dir_t rotary_pop_dir(void);

/**
 * @brief Checks if there has been any recent pressing of the rotary encoder, also resets its status to unpressed.
 *
 * @retval true The rotary was pressed.
 * @retval false The rotary was not pressed.
 */
bool rotary_pop_press(void);

/**
 * @brief Checks if there has been any recent releasing of the rotary encoder, also resets its status to unreleased.
 *
 * @retval true The rotary was released.
 * @retval false The rotary was not released.
 */
bool rotary_pop_release(void);

/**
 * @brief Checks if there has been any recent rotation of the rotary encoder.
 *
 * @return dir_t Latest movement direction.
 */
dir_t rotary_peek_dir(void);

/**
 * @brief Checks if there has been any recent pressing of the rotary encoder.
 *
 * @retval true The rotary was pressed.
 * @retval false The rotary was not pressed.
 */
bool rotary_peek_press(void);

/**
 * @brief Checks if there has been any recent releasing of the rotary encoder.
 *
 * @retval true The rotary was released.
 * @retval false The rotary was not released.
 */
bool rotary_peek_release(void);

#endif /* EQ_CONTROLLER_ROTARY_EVENTS_H */