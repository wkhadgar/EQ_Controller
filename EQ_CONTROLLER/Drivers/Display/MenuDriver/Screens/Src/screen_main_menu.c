/**
 * Created by paulo on 03/05/2023.
 */

#include "screen_main_menu.h"
#include "menu_drawer.h"

static content_t arrow_cursor = {
        .data = arrow,
        .dim = {CUSTOM_CHAR_W, CUSTOM_CHAR_H},
        .pos = {2, 2},
        .opt = {
                .fnt = NULL,
                .is_visible = true,
                .is_bitmap = true,
        },
};

static content_t main_menu_cnts[MAIN_MENU_CONTENTS_AMOUNT] = {
        [MAIN_MENU_MONITOR] = STR_CONTENT_INIT("Go to Monitor", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_MONITOR) + 2, false,
                                               &fnt5x7),
        [MAIN_MENU_DEC] = STR_CONTENT_INIT("Declination", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_DEC) + 2, false, &fnt5x7),
        [MAIN_MENU_RA] = STR_CONTENT_INIT("Right Ascension", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_RA) + 2, false, &fnt5x7),
        [MAIN_MENU_TGT] = STR_CONTENT_INIT("Target Selection", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_TGT) + 2, false,
                                           &fnt5x7),
        [MAIN_MENU_UPDATE] = STR_CONTENT_INIT("Update Home", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_UPDATE) + 2, false,
                                              &fnt5x7),
        [MAIN_MENU_CONT_VALUE] = STR_CONTENT_INIT("Display Contrast", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_CONT_VALUE) + 2,
                                                  false, &fnt5x7),
        [MAIN_MENU_CONT_TIME] = STR_CONTENT_INIT("Sleep Timeout", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_CONT_TIME) + 2, false,
                                                 &fnt5x7),
        [MAIN_MENU_HEM] = STR_CONTENT_INIT("Hemisphere", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_HEM) + 2, false, &fnt5x7),
        [MAIN_MENU_EQMODE] = STR_CONTENT_INIT("Mode", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_EQMODE) + 2, false, &fnt5x7),
};

screen_properties_t main_menu_screen = {
        .details = {
                .id = SCR_O_MAIN_MENU,
                .type = OPTIONS_SCREEN,
                .content_amount = MAIN_MENU_CONTENTS_AMOUNT,
        },
        .contents = main_menu_cnts,
        .cursor_bitmap = &arrow_cursor,
        .post_draw = NULL,
        .update_buffers = NULL,
        .setting_callback = NULL,
};