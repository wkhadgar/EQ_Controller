/**
 * Created by paulo on 02/05/2023.
 */

#ifndef DEBUG_MENU_INFRA_H
#define DEBUG_MENU_INFRA_H

#include "eqm_settings.h"
#include "fonts.h"
#include "sh1106.h"
#include <stdio.h>
#include <string.h>

#define STR_CONTENT_INIT(_data, _x, _y, _is_visible, _fnt) \
    {                                                      \
        .data = (uint8_t*) (_data),                        \
        .pos = {                                           \
                .x = _x,                                   \
                .y = _y,                                   \
        },                                                 \
        .opt = {                                           \
                .fnt = _fnt,                               \
                .is_bitmap = false,                        \
                .is_visible = _is_visible,                 \
        },                                                 \
    }

#define BMP_CONTENT_INIT(_data, _x, _y, _w, _h, _is_visible) \
    {                                                        \
        .data = (uint8_t*) (_data),                          \
        .pos = {                                             \
                .x = _x,                                     \
                .y = _y,                                     \
        },                                                   \
        .dim = {                                             \
                .width = _w,                                 \
                .height = _h,                                \
        },                                                   \
        .opt = {                                             \
                .fnt = NULL,                                 \
                .is_bitmap = true,                           \
                .is_visible = _is_visible,                   \
        },                                                   \
    }

typedef void (* const post_draw_t)(void);

typedef void (* const setting_callback_t)(int8_t, eqm_settings_t*);

typedef void (* const confirm_callback_t)(bool, int8_t, eqm_settings_t*);

typedef void (* const update_buffers_callback_t)(eqm_settings_t const*);

/**
 * @brief Enumera os tipos de tela.
 */
typedef enum screen_modes {
    MONITOR_SCREEN = 0, /**< Tipo de tela cuja finalidade é mostrar informações. */
    SETTING_SCREEN,     /**< Tipo de tela cuja finalidade é modificar um atributo. */
    OPTIONS_SCREEN,     /**< Tipo de tela onde novas opções são navegáveis e selecionáveis. */
    CONFIRM_SCREEN,     /**< Tipo de tela cuja finalidade é confirmar uma ação. */
    POPUP_SCREEN,       /**< Tipo de tela sobreponível que indica um evento. */
} screen_modes_t;

/**
 * @brief Enumera as telas.
 */
typedef enum screens {
    SCR_M_HOME = 0,
    SCR_O_MAIN_MENU,
    SCR_S_DECLINATION,
    SCR_S_RIGHT_ASCENSION,
    SCR_O_TARGET_SELECTOR,
    SCR_S_CONTRAST_VAL,
    SCR_S_CONTRAST_TIME,
    SCR_S_HEMISPHERE,
    SCR_O_EQM_MODE,

    SCR_CONFIRM_TGT,
    SCR_CONFIRM_UPDATE_HOME,
    SCR_CONFIRM_MODE,

    SCR_POP_UP,
    SCR_AMOUNT,
} screens_t;

/**
 * @brief Descreve um conteúdo.
 */
typedef struct content {
    uint8_t* data; /**< Ponteiro para o conteúdo propriamente dito. */

    struct position {
        uint8_t x; /**< Posição horizontal do conteúdo na tela. */
        uint8_t y; /**< Posição vertical do conteúdo na tela. */
    } pos;         /**< Posições do conteúdo na tela. */

    struct dimensions {
        uint8_t width;  /**< Largura horizontal do conteúdo na tela. */
        uint8_t height; /**< Altura vertical do conteúdo na tela. */
    } dim;              /**< Detalha as informações de dimensões do conteúdo, usado para bitmaps. */

    struct options {
        const font_t* fnt;      /**< Fonte do conteúdo, caso seja uma string. */
        uint8_t is_bitmap: 1;  /**< Indica o conteúdo é um bitmap. */
        uint8_t is_visible: 1; /**< Indica o conteúdo é visível atualmente. */
        uint8_t padding: 6;    /**< Padding. */
    } opt;                      /**< Opções do conteúdo. */
} content_t;

/**
 * @brief Descreve uma tela.
 */
typedef struct screen_style {
    const struct screen_info {
        const screen_modes_t type;    /**< Tipo de tela atual. */
        const screens_t id;           /** ID da tela atual. */
        const uint8_t content_amount; /**< Quantidade de conteúdos na página. */
    } details;

    const screens_t* const next_screens;

    update_buffers_callback_t update_buffers;

    union {
        setting_callback_t setting_callback;
        confirm_callback_t confirm_callback;
    };

    post_draw_t post_draw_callback;

    content_t* cursor_bitmap;
    content_t* contents;
} screen_properties_t;

/**
 * @brief Estrutura de controle do menu.
 */
typedef struct navigator {
    screen_properties_t* const* const screens; /**< Tabela de telas por id. */
    screen_properties_t* current_screen; /**< Ponteiro para a tela atual. */

    union control {

        struct monitor_ctrl {
            uint8_t update_threshold; /**< Limite onde a tela deve ser atualizada.*/
            uint8_t update_counter; /**< Contador para atualização da tela. */
        } monitor;

        struct menu_ctrl {
            uint8_t head;      /**< Inicio atual do menu na tela. */
            uint8_t selection; /**< Seleção atual do menu na tela. */
        } menu;

        struct confirm_screen {
            uint8_t previous_screen_selection; /**< Identificador genérico da seleção precedente. */
            bool is_confirmed;
        } confirm;
    } ctrl;

    bool has_changes; /**< Indica se houve mudanças no menu. */

} navigator_t;

/**
 * @brief Imprime um conteúdo na tela.
 *
 * @param cnt Conteúdo a ser impresso.
 */
inline void print_content(content_t cnt) {
    if (cnt.opt.is_bitmap) {
        SH1106_drawBitmap(cnt.pos.x, cnt.pos.y, cnt.dim.width, cnt.dim.height, cnt.data);
    } else {
        SH1106_printStr(cnt.pos.x, cnt.pos.y, (const char*) cnt.data, cnt.opt.fnt);
    }
}

/**
 * @brief Imprime um conteúdo na tela.
 *
 * @param cnt Conteúdo a ser impresso.
 */
inline void print_content_rows(content_t cnt, uint8_t head_y) {
    if (cnt.opt.is_bitmap) {
        SH1106_drawBitmap(cnt.pos.x, cnt.pos.y - head_y, cnt.dim.width, cnt.dim.height, cnt.data);
    } else {
        SH1106_printStr(cnt.pos.x, cnt.pos.y - head_y, (const char*) cnt.data, cnt.opt.fnt);
    }
}

/**
 * @brief Imprime um array de conteúdos na tela.
 *
 * @param[in] contents Conteúdos a serem impressos.
 * @param amount Número de conteúdos.
 */
inline void print_contents(content_t* contents, uint8_t amount) {
    for (uint8_t i = 0; i < amount; i++) {
        if (contents[i].opt.is_visible) {
            print_content(contents[i]);
        }
    }
}

/**
 * @brief Imprime um array de conteúdos na tela.
 *
 * @param[in] contents Conteúdos a serem impressos.
 * @param amount Número de conteúdos.
 */
inline void print_contents_rows(content_t* contents, uint8_t head_y, uint8_t amount) {
    for (uint8_t i = 0; i < amount; i++) {
        if (contents[i].opt.is_visible) {
            print_content_rows(contents[i], head_y);
        }
    }
}

#endif//DEBUG_MENU_INFRA_H