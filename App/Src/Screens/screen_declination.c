/**
 * Created by paulo on 03/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) dec_contents {
    DEC_HEADER,
    DEC_VALUE,
    DEC_BITMAP,

    DEC_CONTENTS_AMOUNT,
} dec_contents_t;

static uint8_t dec_buffer[] = "000`00\"00'";

static void dec_draws(void) {
    sh1106_draw_h_line(0, SCR_W - 20, 11);
}

static void update_buffers(eqm_settings_t const* settings) {
    sprintf((char*) dec_buffer, "%03d`%02d\"%02d'", settings->DEC.degrees,
            settings->DEC.arc_minutes, settings->DEC.arc_seconds);
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
    [DEC_VALUE]  = STR_CONTENT_INIT(dec_buffer, 22, 30, true, &fnt7x10),
    [DEC_BITMAP] = STR_CONTENT_INIT("DEG", 60, 50, true, &fnt5x7),
};

/**
 * @brief Fluxo de destino da tela de configuração de declinação.
 */
static const screens_t declination_flow_s_screens[] = {
    SCR_M_HOME,
};

/**
 * @brief Fluxo de destino da tela de configuração de declinação.
 */
static const screens_t declination_flow_l_screens[] = {
    SCR_O_MAIN_MENU,
};

screen_properties_t declination_screen = {
    .details =
        {
            .id             = SCR_S_DECLINATION,
            .type           = SETTING_SCREEN,
            .content_amount = DEC_CONTENTS_AMOUNT,
        },
    .short_press_next_screens = declination_flow_s_screens,
    .long_press_next_screens  = declination_flow_l_screens,
    .contents                 = dec_cnts,
    .cursor_bitmap            = NULL,
    .setting_callback         = &declination_handler,
    .update_buffers           = &update_buffers,
    .post_draw_callback       = &dec_draws,
};