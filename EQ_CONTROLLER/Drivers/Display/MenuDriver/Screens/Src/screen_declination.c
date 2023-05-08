/**
 * Created by paulo on 03/05/2023.
 */

#include "screen_declination.h"

static uint8_t dec_buffer[] = "000`00\"00'";

static void dec_draws(void) {
    SH1106_drawHLine(0, SCR_W - 20, 11);
}

static void update_buffers(eqm_settings_t* settings) {
    sprintf((char*) dec_buffer, "%03d`%02d\"%02d'",
            settings->DEC.degrees, settings->DEC.arc_minutes, settings->DEC.arc_seconds);
}

static void declination_handler(int8_t dir, eqm_settings_t* setting) {
    setting->DEC.decimal_degrees += (dir * MINUTE_IN_DEGREES);

    if (setting->DEC.decimal_degrees >= 360) {
        setting->DEC.decimal_degrees = 0;
    } else if (setting->DEC.decimal_degrees < 0) {
        setting->DEC.decimal_degrees = (360 - MINUTE_IN_DEGREES);
    }

    update_angle_fields(&setting->DEC);
}

static content_t dec_cnts[] = {
        [DEC_HEADER] = STR_CONTENT_INIT("Declination:", 2, 2, true, &fnt5x7),
        [DEC_VALUE] = STR_CONTENT_INIT(dec_buffer, 22, 30, true, &fnt7x10),
        [DEC_BITMAP] = STR_CONTENT_INIT("DEG", 60, 50, true, &fnt5x7),
};

screen_properties_t declination_screen = {
        .details = {
                .id = SCR_S_DECLINATION,
                .type = SETTING_SCREEN,
                .content_amount = DEC_CONTENTS_AMOUNT,
        },
        .contents = dec_cnts,
        .cursor_bitmap = NULL,
        .setting_callback = &declination_handler,
        .update_buffers = &update_buffers,
        .post_draw = &dec_draws,
};