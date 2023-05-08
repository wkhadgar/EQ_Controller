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

extern screen_properties_t declination_screen;

#endif//DEBUG_SCREEN_DECLINATION_H