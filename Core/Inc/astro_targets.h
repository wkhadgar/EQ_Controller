//
// Created by paulo on 11/11/2022.
//

#ifndef DEBUG_ASTRO_TARGETS_H
#define DEBUG_ASTRO_TARGETS_H

#include "main.h"

/**
 * @brief Time position struct.
 */
typedef struct {
    double decimal_hours;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} time__t;

/**
 * @brief Angle storing struct.
 */
typedef struct {
    double decimal_degrees;
    int16_t degrees;
    uint8_t arc_minutes;
    uint8_t arc_seconds;
} angle_t;

/**
 * @brief Standardized position struct.
 */
typedef struct astro_pos {
    time__t right_ascension;
    angle_t declination;
} astro_pos_t;

/**
 * @brief Target struct.
 */
typedef struct astro_target {
    char name[22];
    astro_pos_t position;
} astro_target_t;

typedef enum {
    JUPITER = 0,
    MARS,
    SATURN,
	SIRIUS,
	RIGEL,
    VENUS,
    USER_TGT_ONE,
    USER_TGT_TWO,
    USER_TGT_THREE,
    USER_TGT_FOUR,
    USER_TGT_FIVE,
    _TARGET_AMOUNT,
} target_t;

void astro_targets_init(void);

void astro_user_target_set(astro_target_t tgt, target_t pos);

astro_target_t astro_target_get(target_t pos);

#endif //DEBUG_ASTRO_TARGETS_H