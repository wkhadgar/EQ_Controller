/**
 * Created by paulo on 03/05/2023.
 */

#include "screen_main_menu.h"
#include "menu_drawer.h"

content_t main_menu_cnts[MAIN_MENU_CONTENTS_AMOUNT] = {
        [MAIN_MENU_MONITOR] = STR_CONTENT_INIT("Go to Monitor", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_MONITOR) + 2, false, &fnt5x7),
        [MAIN_MENU_DEC] = STR_CONTENT_INIT("Declination", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_DEC) + 2, false, &fnt5x7),
        [MAIN_MENU_RA] = STR_CONTENT_INIT("Right Ascension", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_RA) + 2, false, &fnt5x7),
        [MAIN_MENU_TGT] = STR_CONTENT_INIT("Target Selection", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_TGT) + 2, false, &fnt5x7),
        [MAIN_MENU_UPDATE] = STR_CONTENT_INIT("Update Home", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_UPDATE) + 2, false, &fnt5x7),
        [MAIN_MENU_CONT_VALUE] = STR_CONTENT_INIT("Display Contrast", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_CONT_VALUE) + 2, false, &fnt5x7),
        [MAIN_MENU_CONT_TIME] = STR_CONTENT_INIT("Sleep Timeout", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_CONT_TIME) + 2, false, &fnt5x7),
        [MAIN_MENU_HEM] = STR_CONTENT_INIT("Hemisphere", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_HEM) + 2, false, &fnt5x7),
        [MAIN_MENU_EQMODE] = STR_CONTENT_INIT("Mode", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_EQMODE) + 2, false, &fnt5x7),
};