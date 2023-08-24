/**
 * Created by paulo on 04/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) ra_contents {
    RA_HEADER,
    RA_VALUE,
    RA_BITMAP,

    RA_CONTENTS_AMOUNT,
} ra_contents_t;

static uint8_t ra_buffer[] = "00h00m00s";

static void ra_draws(void) {
    SH1106_drawHLine(0, SCR_W - 20, 11);
}

static void update_buffers(eqm_settings_t const* settings) {
    sprintf((char*) ra_buffer, "%02dh%02dm%02ds",
            settings->RA.hours, settings->RA.minutes, settings->RA.seconds);
}

static void right_ascension_handler(int8_t dir, eqm_settings_t* setting) {
    setting->RA.decimal_hours += (dir * MINUTE_IN_HOURS);

    if (setting->RA.decimal_hours >= 24) {
        setting->RA.decimal_hours = 0;
    } else if (setting->RA.decimal_hours < 0) {
        setting->RA.decimal_hours = (24 - MINUTE_IN_HOURS);
    }

    update_time_fields(&setting->RA);
}

static content_t ra_cnts[RA_CONTENTS_AMOUNT] = {
        [RA_HEADER] = STR_CONTENT_INIT("Right Ascension:", 2, 2, true, &fnt5x7),
        [RA_VALUE] = STR_CONTENT_INIT(ra_buffer, 25, 30, true, &fnt7x10),
        [RA_BITMAP] = STR_CONTENT_INIT("HRS", 60, 50, true, &fnt5x7),
};

/**
 * @brief Fluxo de destino da tela de configuração de ascensão reta.
 */
static const screens_t right_ascension_flow_screens[] = {
        SCR_M_HOME,
};

screen_properties_t right_ascension_screen = {
        .details = {
                .id = SCR_S_RIGHT_ASCENSION,
                .type = SETTING_SCREEN,
                .content_amount = RA_CONTENTS_AMOUNT,
        },
        .next_screens = right_ascension_flow_screens,
        .contents = ra_cnts,
        .cursor_bitmap = NULL,
        .setting_callback = &right_ascension_handler,
        .update_buffers = &update_buffers,
        .post_draw_callback = &ra_draws,
};