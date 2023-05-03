/**
 * Created by paulo on 02/05/2023.
 */

#ifndef DEBUG_SCREEN_MONITOR_H
#define DEBUG_SCREEN_MONITOR_H

#include "bitmaps.h"
#include "menu_infra.h"

typedef enum __attribute__((packed)) monitor_contents {
    MONITOR_DEC_LABEL,
    MONITOR_DEC,
    MONITOR_RA_LABEL,
    MONITOR_RA,
    MONITOR_BITMAP,

    MONITOR_CONTENTS_AMOUNT,
} monitor_contents_t;

void show_monitor(void);

extern content_t monitor_contents[];

static screen_style_t monitor_screen = {
        .details = {
                .id = 0,
                .type = MONITOR_SCREEN,
                .content_amount = MONITOR_CONTENTS_AMOUNT,
        },
        .contents = monitor_contents,
        .show = &show_monitor,
};

#endif//DEBUG_SCREEN_MONITOR_H