/**
 * Created by paulo on 04/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) cont_time_contents {
    CONT_TIME_HEADER,
    CONT_TIME_VALUE,
    CONT_TIME_BITMAP,

    CONT_TIME_CONTENTS_AMOUNT,
} cont_time_contents_t;

static uint8_t cont_time_buffer[] = "000s";

static void cont_time_draws(void) {
    sh1106_draw_h_line(0, SCR_W - 20, 11);
}

static void update_buffers(eqm_settings_t const* settings) {
    sprintf((char*) cont_time_buffer, "%03ds", settings->screen_contrast_time);
}

static void contrast_time_handler(int8_t dir, eqm_settings_t* setting) {
    int16_t new_contrast_time = (int16_t) (setting->screen_contrast_time + dir);

    if (new_contrast_time >= 240) {
        new_contrast_time = 240;
    } else if (new_contrast_time < 0) {
        new_contrast_time = 0;
    }

    setting->screen_contrast_time = (uint8_t) new_contrast_time;
}

static content_t cont_time_cnts[CONT_TIME_CONTENTS_AMOUNT] = {
    [CONT_TIME_HEADER] = STR_CONTENT_INIT("Contrasted Time:", 2, 2, true, &fnt5x7),
    [CONT_TIME_VALUE]  = STR_CONTENT_INIT(cont_time_buffer, 47, 30, true, &fnt7x10),
};

/**
 * @brief Fluxo de destino da tela de configuração de ascensão reta.
 */
static const screens_t contrast_time_flow_s_screens[] = {
    SCR_M_HOME,
};

/**
 * @brief Fluxo de destino da tela de configuração de ascensão reta.
 */
static const screens_t contrast_time_flow_l_screens[] = {
    SCR_O_MAIN_MENU,
};

screen_properties_t contrast_time_screen = {
    .details =
        {
            .id             = SCR_S_CONTRAST_VAL,
            .type           = SETTING_SCREEN,
            .content_amount = CONT_TIME_CONTENTS_AMOUNT,
        },
    .short_press_next_screens = contrast_time_flow_s_screens,
    .long_press_next_screens  = contrast_time_flow_l_screens,
    .contents                 = cont_time_cnts,
    .cursor_bitmap            = NULL,
    .setting_callback         = &contrast_time_handler,
    .update_buffers           = &update_buffers,
    .post_draw_callback       = &cont_time_draws,
};