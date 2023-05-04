/**
 * Created by paulo on 03/05/2023.
 */

#ifndef DEBUG_SCREEN_MAIN_MENU_H
#define DEBUG_SCREEN_MAIN_MENU_H

#include "menu_nav.h"

typedef enum __attribute__((packed)) main_menu_contents {
    MAIN_MENU_MONITOR,
    MAIN_MENU_DEC,
    MAIN_MENU_RA,
    MAIN_MENU_TGT,
    MAIN_MENU_UPDATE,
    MAIN_MENU_CONT_VALUE,
    MAIN_MENU_CONT_TIME,
    MAIN_MENU_HEM,
    MAIN_MENU_EQMODE,

    MAIN_MENU_CONTENTS_AMOUNT,
} main_menu_contents_t;

extern content_t main_menu_arrow;

extern content_t main_menu_cnts[];

static screen_style_t main_menu_screen = {
        .details = {
                .id = SCR_O_MAIN_MENU,
                .type = OPTIONS_SCREEN,
                .content_amount = MAIN_MENU_CONTENTS_AMOUNT,
        },
        .contents = main_menu_cnts,
        .post_draw = NULL,
};

#endif//DEBUG_SCREEN_MAIN_MENU_H