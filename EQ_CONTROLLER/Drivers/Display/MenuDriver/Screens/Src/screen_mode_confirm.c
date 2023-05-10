/**
 * Created by paulo on 09/05/2023.
 */
#include "menu_drawer.h"

typedef enum mode_confirm_contents {
    MODE_CONF_HEADER = 0,
    MODE_CONF_SUB_HEADER,
    MODE_CONF_NO,
    MODE_CONF_YES,
    MODE_INDICATOR_BITMAP,

    MODE_CONF_CONTENTS_AMOUNT,
} mode_confirm_contents_t;

static content_t mode_conf_cnts[MODE_CONF_CONTENTS_AMOUNT] = {
        [MODE_CONF_HEADER] = STR_CONTENT_INIT("(!) Are you sure to", 2, 2, true, &fnt5x7),
        [MODE_CONF_SUB_HEADER] = STR_CONTENT_INIT("    switch mode?", 2, 10, true, &fnt5x7),
        [MODE_CONF_NO] = STR_CONTENT_INIT("No", 22, 30, true, &fnt7x10),
        [MODE_CONF_YES] = STR_CONTENT_INIT("Yes", 82, 30, true, &fnt7x10),
        [MODE_INDICATOR_BITMAP] = BMP_CONTENT_INIT(arrow, 14, 33, CUSTOM_CHAR_W, CUSTOM_CHAR_H, true),
};

static void confirm_cb(bool is_confirm, int8_t dir, eqm_settings_t* settings) {
    if (is_confirm) {
        settings->mode = dir-1;
        return;
    }

    if (dir > 0) {
        mode_conf_cnts[MODE_INDICATOR_BITMAP].pos.x = 76;
    } else {
        mode_conf_cnts[MODE_INDICATOR_BITMAP].pos.x = 14;
    }
}

static const screens_t mode_conf_flow_screens[2] = {
        [false] = SCR_O_EQM_MODE,
        [true] = SCR_M_HOME,
};

screen_properties_t mode_conf_screen = {
        .details = {
                .id = SCR_CONFIRM_MODE,
                .type = CONFIRM_SCREEN,
                .content_amount = MODE_CONF_CONTENTS_AMOUNT,
        },
        .next_screens = mode_conf_flow_screens,
        .contents = mode_conf_cnts,
        .cursor_bitmap = NULL,
        .confirm_callback = &confirm_cb,
        .update_buffers = NULL,
        .post_draw_callback = NULL,
};