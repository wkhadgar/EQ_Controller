/**
 * Created by paulo on 04/05/2023.
 */

#ifndef DEBUG_EQM_SETTINGS_H
#define DEBUG_EQM_SETTINGS_H

#include "astro_targets.h"

#define MINUTE_IN_DEGREES (0.01666666)
#define MINUTE_IN_HOURS (0.01666666)


typedef enum hemisphere {
    NORTH = 0,
    SOUTH,
} hemisphere_t;

typedef enum ewm_mode {
    MANUAL_MODE = 0,
    TRACKING_MODE,
    GOTO_MODE,
    OFF_MODE,

    EQM_MODES_AMOUNT,
} eqm_mode_t;

typedef struct eqm_settings {
    angle_t DEC;
    time__t RA;
    uint8_t screen_contrast;      /**< relative brightness */
    uint8_t screen_contrast_time; /**< time to auto reduce the brightness, in seconds */
    hemisphere_t hemisphere;      /**< at telescope location */
    eqm_mode_t mode;
} eqm_settings_t;

/**
 * @brief Atualiza os campos de um tempo, baseado no seu tempo decimal salvo.
 *
 * @param time Tempo a ter seus campos atualizados.
 */
inline void update_time_fields(time__t* time) {
    time->hours = (uint8_t) time->decimal_hours;
    time->minutes = (uint8_t) ((time->decimal_hours - time->hours) * 60);
    time->seconds = (uint8_t) (((time->decimal_hours - time->hours) * 60 - time->minutes) * 60 + 0.5);
}

/**
 * @brief Atualiza os campos de um angulo, baseado no seu angulo decimal salvo.
 *
 * @param time Angulo a ter seus campos atualizados.
 */
inline void update_angle_fields(angle_t* angle) {
    angle->degrees = (uint8_t) angle->decimal_degrees;
    angle->arc_minutes = (uint8_t) ((angle->decimal_degrees - angle->degrees) * 60);
    angle->arc_seconds = (uint8_t) (((angle->decimal_degrees - angle->degrees) * 60 - angle->arc_minutes) * 60 + 0.5);
}

#endif//DEBUG_EQM_SETTINGS_H