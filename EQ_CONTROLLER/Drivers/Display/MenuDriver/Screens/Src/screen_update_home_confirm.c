/**
 * Created by paulo on 09/05/2023.
 */
#include "menu_drawer.h"

typedef enum update_home_confirm_contents {
    UPDT_HOME_CONF_HEADER = 0,
    UPDT_HOME_CONF_SUB_HEADER,
    UPDT_HOME_CONF_NO,
    UPDT_HOME_CONF_YES,
    UPDT_HOME_INDICATOR_BITMAP,

    UPDT_HOME_CONF_CONTENTS_AMOUNT,
} update_home_confirm_contents_t;

static content_t updt_home_conf_cnts[UPDT_HOME_CONF_CONTENTS_AMOUNT] = {
        [UPDT_HOME_CONF_HEADER] = STR_CONTENT_INIT("(!) Are you sure to", 2, 2, true, &fnt5x7),
        [UPDT_HOME_CONF_SUB_HEADER] = STR_CONTENT_INIT("    update home?", 2, 10, true, &fnt5x7),
        [UPDT_HOME_CONF_NO] = STR_CONTENT_INIT("No", 22, 30, true, &fnt7x10),
        [UPDT_HOME_CONF_YES] = STR_CONTENT_INIT("Yes", 82, 30, true, &fnt7x10),
        [UPDT_HOME_INDICATOR_BITMAP] = BMP_CONTENT_INIT(arrow, 14, 33, CUSTOM_CHAR_W, CUSTOM_CHAR_H, true),
};

static void confirm_cb(bool is_confirm, int8_t dir, eqm_settings_t* settings) {
    if (is_confirm) { //TODO
        settings->DEC;
        settings->RA;
        return;
    }

    if (dir > 0) {
        updt_home_conf_cnts[UPDT_HOME_INDICATOR_BITMAP].pos.x = 76;
    } else {
        updt_home_conf_cnts[UPDT_HOME_INDICATOR_BITMAP].pos.x = 14;
    }
}

static const screens_t updt_home_conf_flow_screens[2] = {
        [false] = SCR_O_MAIN_MENU,
        [true] = SCR_M_HOME,
};

screen_properties_t updt_home_conf_screen = {
        .details = {
                .id = SCR_CONFIRM_UPDATE_HOME,
                .type = CONFIRM_SCREEN,
                .content_amount = UPDT_HOME_CONF_CONTENTS_AMOUNT,
        },
        .next_screens = updt_home_conf_flow_screens,
        .contents = updt_home_conf_cnts,
        .cursor_bitmap = NULL,
        .confirm_callback = &confirm_cb,
        .update_buffers = NULL,
        .post_draw_callback = NULL,
};