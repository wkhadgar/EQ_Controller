/**
 * Created by paulo on 03/05/2023.
 */

#ifndef DEBUG_SCREEN_DECLINATION_H
#define DEBUG_SCREEN_DECLINATION_H

#include "menu_nav.h"

typedef enum __attribute__((packed)) dec_contents {
    DEC_HEADER,
    DEC_VALUE,
    DEC_BITMAP,

    DEC_CONTENTS_AMOUNT,
} dec_contents_t;

void dec_draws(void);

void declination_handler(int8_t dir);

extern content_t dec_cnts[];

static screen_style_t declination_screen = {
        .details = {
                .id = SCR_S_DECLINATION,
                .type = SETTING_SCREEN,
                .content_amount = DEC_CONTENTS_AMOUNT,
        },
        .contents = dec_cnts,
        .post_draw = &dec_draws,
};

#endif//DEBUG_SCREEN_DECLINATION_H