/**
 * Created by paulo on 09/05/2023.
 */
#include "menu_drawer.h"

typedef enum tgt_confirm_contents {
    TGT_CONF_HEADER = 0,
    TGT_CONF_SUB_HEADER,
    TGT_CONF_NO,
    TGT_CONF_YES,
    TGT_INDICATOR_BITMAP,

    TGT_CONF_CONTENTS_AMOUNT,
} tgt_confirm_contents_t;

extern astro_target_t astro_targets[];

static content_t tgt_conf_cnts[TGT_CONF_CONTENTS_AMOUNT] = {
        [TGT_CONF_HEADER] = STR_CONTENT_INIT("(!) Are you sure to", 2, 2, true, &fnt5x7),
        [TGT_CONF_SUB_HEADER] = STR_CONTENT_INIT("    switch target?", 2, 10, true, &fnt5x7),
        [TGT_CONF_NO] = STR_CONTENT_INIT("No", 22, 30, true, &fnt7x10),
        [TGT_CONF_YES] = STR_CONTENT_INIT("Yes", 82, 30, true, &fnt7x10),
        [TGT_INDICATOR_BITMAP] = BMP_CONTENT_INIT(arrow, 14, 33, CUSTOM_CHAR_W, CUSTOM_CHAR_H, true),
};

static void confirm_cb(bool is_confirm, int8_t dir, eqm_settings_t* settings) {
    if (is_confirm) {
        settings->DEC = astro_targets[dir - 1].position.declination;
        settings->RA = astro_targets[dir - 1].position.right_ascension;
        return;
    }

    if (dir > 0) {
        tgt_conf_cnts[TGT_INDICATOR_BITMAP].pos.x = 76;
    } else {
        tgt_conf_cnts[TGT_INDICATOR_BITMAP].pos.x = 14;
    }
}

static const screens_t tgt_conf_flow_screens[2] = {
        [false] = SCR_O_TARGET_SELECTOR,
        [true] = SCR_M_HOME,
};

screen_properties_t tgt_conf_screen = {
        .details = {
                .id = SCR_CONFIRM_TGT,
                .type = CONFIRM_SCREEN,
                .content_amount = TGT_CONF_CONTENTS_AMOUNT,
        },
        .next_screens = tgt_conf_flow_screens,
        .contents = tgt_conf_cnts,
        .cursor_bitmap = NULL,
        .confirm_callback = &confirm_cb,
        .update_buffers = NULL,
        .post_draw_callback = NULL,
};