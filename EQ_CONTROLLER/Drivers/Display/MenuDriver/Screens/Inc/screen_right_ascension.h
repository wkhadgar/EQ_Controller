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

extern screen_properties_t right_ascension_screen;

#endif//DEBUG_SCREEN_RIGHT_ASCENSION_H