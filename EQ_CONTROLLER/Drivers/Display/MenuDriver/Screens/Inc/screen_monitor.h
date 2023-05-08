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

extern screen_properties_t monitor_screen;

#endif//DEBUG_SCREEN_MONITOR_H