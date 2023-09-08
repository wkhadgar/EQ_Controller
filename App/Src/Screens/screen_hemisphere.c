/**
 * Created by paulo on 04/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) hemisphere_contents {
    HEMISPHERE_HEADER,
    HEMISPHERE_VALUE,
    HEMISPHERE_BITMAP,

    HEMISPHERE_CONTENTS_AMOUNT,
} hemisphere_contents_t;

static uint8_t hemisphere_buffer[] = "_____";
static uint8_t hemisphere_bmp_buffer[72];

static void hemisphere_draws(void) {
    sh1106_draw_h_line(0, SCR_W - 20, 11);
}

static content_t hemisphere_cnts[HEMISPHERE_CONTENTS_AMOUNT] = {
        [HEMISPHERE_HEADER] = STR_CONTENT_INIT("Hemisphere:", 2, 2, true, &fnt5x7),
        [HEMISPHERE_VALUE] = STR_CONTENT_INIT(hemisphere_buffer, 25, 30, true, &fnt7x10),
        [HEMISPHERE_BITMAP] = BMP_CONTENT_INIT(hemisphere_bmp_buffer, 80, 20, SETTINGS_BITMAP_W, SETTINGS_BITMAP_H,
                                               true),
};

static void update_buffers(eqm_settings_t const* settings) {
    if (settings->hemisphere == NORTH) {
        sprintf((char*) hemisphere_buffer, "North");
        memcpy(hemisphere_bmp_buffer, north_hemisphere, sizeof(hemisphere_bmp_buffer));
        hemisphere_cnts[HEMISPHERE_BITMAP].pos.y = 20;
    } else {
        sprintf((char*) hemisphere_buffer, "South");
        memcpy(hemisphere_bmp_buffer, south_hemisphere, sizeof(hemisphere_bmp_buffer));
        hemisphere_cnts[HEMISPHERE_BITMAP].pos.y = 25;
    }

}

static void hemisphere_handler(int8_t dir, eqm_settings_t* setting) {
    setting->hemisphere = dir > 0 ? NORTH : SOUTH;
}

/**
 * @brief Fluxo de destino da tela de configuração de ascensão reta.
 */
static const screens_t hemisphere_flow_screens[] = {
        SCR_O_MAIN_MENU,
};

screen_properties_t hemisphere_screen = {
        .details = {
                .id = SCR_S_CONTRAST_VAL,
                .type = SETTING_SCREEN,
                .content_amount = HEMISPHERE_CONTENTS_AMOUNT,
        },
        .next_screens = hemisphere_flow_screens,
        .contents = hemisphere_cnts,
        .cursor_bitmap = NULL,
        .setting_callback = &hemisphere_handler,
        .update_buffers = &update_buffers,
        .post_draw_callback = &hemisphere_draws,
};