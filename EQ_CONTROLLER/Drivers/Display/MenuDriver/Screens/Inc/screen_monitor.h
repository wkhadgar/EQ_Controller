/**
 * Created by paulo on 02/05/2023.
 */

#ifndef DEBUG_SCREEN_MONITOR_H
#define DEBUG_SCREEN_MONITOR_H

#include "bitmaps.h"
#include "menu_nav.h"

typedef enum __attribute__((packed)) monitor_contents {
    MONITOR_DEC_LABEL,
    MONITOR_DEC,
    MONITOR_RA_LABEL,
    MONITOR_RA,
    MONITOR_BITMAP,

    MONITOR_CONTENTS_AMOUNT,
} monitor_contents_t;

void monitor_draws(void);

extern content_t monitor_cnts[];

extern const uint8_t* mode_bitmaps[];

static screen_style_t monitor_screen = {
        .details = {
                .id = SCR_M_HOME,
                .type = MONITOR_SCREEN,
                .content_amount = MONITOR_CONTENTS_AMOUNT,
        },
        .contents = monitor_cnts,
        .post_draw = &monitor_draws,
};

#endif//DEBUG_SCREEN_MONITOR_H