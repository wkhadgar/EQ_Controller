/**
 * Created by paulo on 04/05/2023.
 */

#ifndef DEBUG_SCREEN_RIGHT_ASCENSION_H
#define DEBUG_SCREEN_RIGHT_ASCENSION_H

#include "menu_nav.h"

typedef enum __attribute__((packed)) ra_contents {
    RA_HEADER,
    RA_VALUE,
    RA_BITMAP,

    RA_CONTENTS_AMOUNT,
} ra_contents_t;

void ra_draws(void);

void right_ascension_handler(int8_t dir, eqm_settings_t* setting);

extern content_t ra_cnts[];

static screen_style_t right_ascension_screen = {
        .details = {
                .id = SCR_S_RIGHT_ASCENSION,
                .type = SETTING_SCREEN,
                .content_amount = RA_CONTENTS_AMOUNT,
        },
        .contents = ra_cnts,
        .post_draw = &ra_draws,
};

#endif//DEBUG_SCREEN_RIGHT_ASCENSION_H