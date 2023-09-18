/**
 * Created by paulo on 03/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) mode_menu_contents {
    MODE_MENU_RETURN = 0,
    MODE_MENU_MANUAL,
    MODE_MENU_TRACKING,
    MODE_MENU_GOTO,
    MODE_MENU_OFF,
    MODE_MENU_RETURN_BITMAP,

    MODE_MENU_CONTENTS_AMOUNT,
} mode_menu_contents_t;

static content_t arrow_cursor = {
    .data = arrow,
    .dim  = {CUSTOM_CHAR_W, CUSTOM_CHAR_H},
    .pos  = {2, 2},
    .opt =
        {
            .fnt        = NULL,
            .is_visible = true,
            .is_bitmap  = true,
        },
};

static content_t mode_menu_cnts[MODE_MENU_CONTENTS_AMOUNT] = {
    [MODE_MENU_RETURN]   = STR_CONTENT_INIT("Return", X_LEFT_PAD + 10,
                                            Y_BY_ENUM(MODE_MENU_RETURN), true, &fnt5x7),
    [MODE_MENU_MANUAL]   = STR_CONTENT_INIT("Manual mode", X_LEFT_PAD,
                                            Y_BY_ENUM(MODE_MENU_MANUAL), true, &fnt5x7),
    [MODE_MENU_TRACKING] = STR_CONTENT_INIT("Start tracking", X_LEFT_PAD,
                                            Y_BY_ENUM(MODE_MENU_TRACKING), true, &fnt5x7),
    [MODE_MENU_GOTO]     = STR_CONTENT_INIT("Go to target", X_LEFT_PAD,
                                            Y_BY_ENUM(MODE_MENU_GOTO), true, &fnt5x7),
    [MODE_MENU_OFF]      = STR_CONTENT_INIT("Turn motors off", X_LEFT_PAD,
                                            Y_BY_ENUM(MODE_MENU_OFF), true, &fnt5x7),
    [MODE_MENU_RETURN_BITMAP] =
        BMP_CONTENT_INIT(return_bmp, X_LEFT_PAD, Y_BY_ENUM(MODE_MENU_RETURN),
                         CUSTOM_CHAR_W, CUSTOM_CHAR_H, true),
};

/**
 * @brief Fluxo de destino da tela menu principal.
 */
static const screens_t mode_menu_flow_s_screens[MODE_MENU_CONTENTS_AMOUNT] = {
    [MODE_MENU_RETURN] = SCR_O_MAIN_MENU,    [MODE_MENU_MANUAL] = SCR_CONFIRM_MODE,
    [MODE_MENU_TRACKING] = SCR_CONFIRM_MODE, [MODE_MENU_GOTO] = SCR_CONFIRM_MODE,
    [MODE_MENU_OFF] = SCR_CONFIRM_MODE,
};

/**
 * @brief Fluxo de destino da tela menu principal.
 */
static const screens_t mode_menu_flow_l_screens[] = {
    SCR_O_MAIN_MENU,
};

screen_properties_t mode_menu_screen = {
    .details =
        {
            .id             = SCR_O_EQM_MODE,
            .type           = OPTIONS_SCREEN,
            .content_amount = MODE_MENU_CONTENTS_AMOUNT,
        },
    .short_press_next_screens = mode_menu_flow_s_screens,
    .long_press_next_screens  = mode_menu_flow_l_screens,
    .contents                 = mode_menu_cnts,
    .cursor_bitmap            = &arrow_cursor,
    .post_draw_callback       = NULL,
    .update_buffers           = NULL,
    .setting_callback         = NULL,
}; /**
    * Created by paulo on 09/05/2023.
    */