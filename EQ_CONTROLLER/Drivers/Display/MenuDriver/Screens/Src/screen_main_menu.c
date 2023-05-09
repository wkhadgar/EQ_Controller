/**
 * Created by paulo on 03/05/2023.
 */

#include "menu_drawer.h"

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
        [MAIN_MENU_MONITOR] = STR_CONTENT_INIT("Go to Monitor", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_MONITOR), true,
                                               &fnt5x7),
        [MAIN_MENU_DEC] = STR_CONTENT_INIT("Declination", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_DEC), true, &fnt5x7),
        [MAIN_MENU_RA] = STR_CONTENT_INIT("Right Ascension", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_RA), true, &fnt5x7),
        [MAIN_MENU_TGT] = STR_CONTENT_INIT("Target Selection", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_TGT), true,
                                           &fnt5x7),
        [MAIN_MENU_UPDATE] = STR_CONTENT_INIT("Update Home", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_UPDATE), true,
                                              &fnt5x7),
        [MAIN_MENU_CONT_VALUE] = STR_CONTENT_INIT("Display Contrast", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_CONT_VALUE),
                                                  true, &fnt5x7),
        [MAIN_MENU_CONT_TIME] = STR_CONTENT_INIT("Sleep Timeout", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_CONT_TIME), true,
                                                 &fnt5x7),
        [MAIN_MENU_HEM] = STR_CONTENT_INIT("Hemisphere", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_HEM), true, &fnt5x7),
        [MAIN_MENU_EQMODE] = STR_CONTENT_INIT("Mode", X_LEFT_PAD, Y_BY_ENUM(MAIN_MENU_EQMODE), true, &fnt5x7),
};

/**
 * @brief Fluxo de destino da tela menu principal.
 */
static const screens_t main_menu_flow_screens[MAIN_MENU_CONTENTS_AMOUNT] = {
        [MAIN_MENU_MONITOR] = SCR_M_HOME,
        [MAIN_MENU_DEC] = SCR_S_DECLINATION,
        [MAIN_MENU_RA] = SCR_S_RIGHT_ASCENSION,
        [MAIN_MENU_TGT] = SCR_O_TARGET_SELECTOR,
        [MAIN_MENU_UPDATE] = SCR_CONFIRM_UPDATE_HOME,
        [MAIN_MENU_CONT_VALUE] = SCR_S_CONTRAST_VAL,
        [MAIN_MENU_CONT_TIME] = SCR_S_CONTRAST_TIME,
        [MAIN_MENU_HEM] = SCR_S_HEMISPHERE,
        [MAIN_MENU_EQMODE] = SCR_O_EQM_MODE,
};

screen_properties_t main_menu_screen = {
        .details = {
                .id = SCR_O_MAIN_MENU,
                .type = OPTIONS_SCREEN,
                .content_amount = MAIN_MENU_CONTENTS_AMOUNT,
        },
        .next_screens = main_menu_flow_screens,
        .contents = main_menu_cnts,
        .cursor_bitmap = &arrow_cursor,
        .post_draw_callback = NULL,
        .update_buffers = NULL,
        .setting_callback = NULL,
};