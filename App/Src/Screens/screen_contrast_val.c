/**
 * Created by paulo on 04/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) cont_val_contents {
    CONT_VAL_HEADER,
    CONT_VAL_VALUE,
    CONT_VAL_BITMAP,

    CONT_VAL_CONTENTS_AMOUNT,
} cont_val_contents_t;

static uint8_t cont_val_buffer[] = "000%";

static void cont_val_draws(void) {
    SH1106_drawHLine(0, SCR_W - 20, 11);
    SH1106_fillRect(0, SCR_H - 20, SCR_W, SCR_H);
}

static void update_buffers(eqm_settings_t const* settings) {
    sprintf((char*) cont_val_buffer, "%03d%%", (uint8_t) ((settings->screen_contrast / 255.0) * 100.0));
}

static void contrast_handler(int8_t dir, eqm_settings_t* setting) {
    int16_t new_contrast = (int16_t) (setting->screen_contrast + dir);

    if (new_contrast >= 255) {
        new_contrast = 255;
    } else if (new_contrast < 0) {
        new_contrast = 0;
    }

    setting->screen_contrast = (uint8_t) new_contrast;
}

static content_t cont_val_cnts[CONT_VAL_CONTENTS_AMOUNT] = {
        [CONT_VAL_HEADER] = STR_CONTENT_INIT("Contrast Factor:", 2, 2, true, &fnt5x7),
        [CONT_VAL_VALUE] = STR_CONTENT_INIT(cont_val_buffer, 47, 30, true, &fnt7x10),
};

/**
 * @brief Fluxo de destino da tela de configuração de ascensão reta.
 */
static const screens_t contrast_flow_screens[] = {
        SCR_O_MAIN_MENU,
};

screen_properties_t contrast_val_screen = {
        .details = {
                .id = SCR_S_CONTRAST_VAL,
                .type = SETTING_SCREEN,
                .content_amount = CONT_VAL_CONTENTS_AMOUNT,
        },
        .next_screens = contrast_flow_screens,
        .contents = cont_val_cnts,
        .cursor_bitmap = NULL,
        .setting_callback = &contrast_handler,
        .update_buffers = &update_buffers,
        .post_draw_callback = &cont_val_draws,
};