/**
 * Created by paulo on 03/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) cont_val_contents {
    CONT_VAL_HEADER,
    CONT_VAL_VALUE,

    CONT_VAL_CONTENTS_AMOUNT,
} cont_val_contents_t;

static uint8_t cont_val_buffer[] = "000`00\"00'";

static void cont_val_draws(void) {
    SH1106_drawHLine(0, SCR_W - 20, 11);
}

static void update_buffers(eqm_settings_t const* settings) {
    sprintf((char*) cont_val_buffer, "%03d`%02d\"%02d'",
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

static content_t cont_val_cnts[] = {
        [CONT_VAL_HEADER] = STR_CONTENT_INIT("Contrast:", 2, 2, true, &fnt5x7),
        [CONT_VAL_VALUE] = STR_CONTENT_INIT(cont_val_buffer, 22, 30, true, &fnt7x10),
};

/**
 * @brief Fluxo de destino da tela de configuração de declinação.
 */
static const screens_t declination_flow_screens[] = {
        SCR_M_HOME,
};

screen_properties_t declination_screen = {
        .details = {
                .id = SCR_S_DECLINATION,
                .type = SETTING_SCREEN,
                .content_amount = CONT_VAL_CONTENTS_AMOUNT,
        },
        .next_screens = declination_flow_screens,
        .contents = cont_val_cnts,
        .cursor_bitmap = NULL,
        .setting_callback = &declination_handler,
        .update_buffers = &update_buffers,
        .post_draw_callback = &cont_val_draws,
};