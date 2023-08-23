/**
 * Created by paulo on 09/05/2023.
 */

#include "menu_drawer.h"

typedef enum __attribute__((packed)) tgt_sel_contents {
    TGT_SEL_RETURN = 0,
    TGT_SEL_JUPITER,
    TGT_SEL_MARS,
    TGT_SEL_SATURN,
    TGT_SEL_SIRIUS,
    TGT_SEL_RIGEL,
    TGT_SEL_VENUS,
    TGT_SEL_USER_TGT_ONE,
    TGT_SEL_USER_TGT_TWO,
    TGT_SEL_USER_TGT_THREE,
    TGT_SEL_USER_TGT_FOUR,
    TGT_SEL_USER_TGT_FIVE,
    TGT_SEL_RETURN_BITMAP,

    TGT_SEL_CONTENTS_AMOUNT,
} tgt_sel_contents_t;

extern astro_target_t astro_targets[];

static content_t arrow_cursor = {
        .data = arrow,
        .dim = {CUSTOM_CHAR_W, CUSTOM_CHAR_H},
        .pos = {2, 2},
        .opt = {
                .fnt = NULL,
                .is_visible = true,
                .is_bitmap = true,
        },
};

static content_t tgt_sel_cnts[TGT_SEL_CONTENTS_AMOUNT] = {
        [TGT_SEL_RETURN] = STR_CONTENT_INIT("Return", X_LEFT_PAD + 10, Y_BY_ENUM(TGT_SEL_RETURN), true, &fnt5x7),
        [TGT_SEL_JUPITER] = STR_CONTENT_INIT(astro_targets[JUPITER].name, X_LEFT_PAD, Y_BY_ENUM(TGT_SEL_JUPITER), true,
                                             &fnt5x7),
        [TGT_SEL_MARS] = STR_CONTENT_INIT(astro_targets[MARS].name, X_LEFT_PAD, Y_BY_ENUM(TGT_SEL_MARS), true, &fnt5x7),
        [TGT_SEL_SATURN] = STR_CONTENT_INIT(astro_targets[SATURN].name, X_LEFT_PAD, Y_BY_ENUM(TGT_SEL_SATURN), true,
                                            &fnt5x7),
        [TGT_SEL_SIRIUS] = STR_CONTENT_INIT(astro_targets[SIRIUS].name, X_LEFT_PAD, Y_BY_ENUM(TGT_SEL_SIRIUS), true,
                                            &fnt5x7),
        [TGT_SEL_RIGEL] = STR_CONTENT_INIT(astro_targets[RIGEL].name, X_LEFT_PAD, Y_BY_ENUM(TGT_SEL_RIGEL), true,
                                           &fnt5x7),
        [TGT_SEL_VENUS] = STR_CONTENT_INIT(astro_targets[VENUS].name, X_LEFT_PAD, Y_BY_ENUM(TGT_SEL_VENUS),
                                           true, &fnt5x7),
        [TGT_SEL_USER_TGT_ONE] = STR_CONTENT_INIT(astro_targets[USER_TGT_ONE].name, X_LEFT_PAD,
                                                  Y_BY_ENUM(TGT_SEL_USER_TGT_ONE),
                                                  false,
                                                  &fnt5x7),
        [TGT_SEL_USER_TGT_TWO] = STR_CONTENT_INIT(astro_targets[USER_TGT_TWO].name, X_LEFT_PAD,
                                                  Y_BY_ENUM(TGT_SEL_USER_TGT_TWO),
                                                  false,
                                                  &fnt5x7),
        [TGT_SEL_USER_TGT_THREE] = STR_CONTENT_INIT(astro_targets[USER_TGT_THREE].name, X_LEFT_PAD,
                                                    Y_BY_ENUM(TGT_SEL_USER_TGT_THREE),
                                                    false, &fnt5x7),
        [TGT_SEL_USER_TGT_FOUR] = STR_CONTENT_INIT(astro_targets[USER_TGT_FOUR].name, X_LEFT_PAD,
                                                   Y_BY_ENUM(TGT_SEL_USER_TGT_FOUR),
                                                   false, &fnt5x7),
        [TGT_SEL_USER_TGT_FIVE] = STR_CONTENT_INIT(astro_targets[USER_TGT_FIVE].name, X_LEFT_PAD,
                                                   Y_BY_ENUM(TGT_SEL_USER_TGT_FIVE),
                                                   false, &fnt5x7),
        [TGT_SEL_RETURN_BITMAP] = BMP_CONTENT_INIT(return_bmp, X_LEFT_PAD, Y_BY_ENUM(TGT_SEL_RETURN), CUSTOM_CHAR_W,
                                                   CUSTOM_CHAR_H, true),
};

/**
 * @brief Fluxo de destino da tela de seleção de alvo.
 */
static const screens_t tgt_sel_flow_screens[TGT_SEL_CONTENTS_AMOUNT] = {
        [TGT_SEL_RETURN]         = SCR_O_MAIN_MENU,
        [TGT_SEL_JUPITER]        = SCR_CONFIRM_TGT,
        [TGT_SEL_MARS]           = SCR_CONFIRM_TGT,
        [TGT_SEL_SATURN]         = SCR_CONFIRM_TGT,
        [TGT_SEL_SIRIUS]         = SCR_CONFIRM_TGT,
        [TGT_SEL_RIGEL]          = SCR_CONFIRM_TGT,
        [TGT_SEL_VENUS]          = SCR_CONFIRM_TGT,
        [TGT_SEL_USER_TGT_ONE]   = SCR_CONFIRM_TGT,
        [TGT_SEL_USER_TGT_TWO]   = SCR_CONFIRM_TGT,
        [TGT_SEL_USER_TGT_THREE] = SCR_CONFIRM_TGT,
        [TGT_SEL_USER_TGT_FOUR]  = SCR_CONFIRM_TGT,
        [TGT_SEL_USER_TGT_FIVE]  = SCR_CONFIRM_TGT,
};

screen_properties_t tgt_sel_screen = {
        .details = {
                .id = SCR_O_TARGET_SELECTOR,
                .type = OPTIONS_SCREEN,
                .content_amount = _TARGET_AMOUNT,
        },
        .next_screens = tgt_sel_flow_screens,
        .contents = tgt_sel_cnts,
        .cursor_bitmap = &arrow_cursor,
        .post_draw_callback = NULL,
        .update_buffers = NULL,
        .setting_callback = NULL,
};