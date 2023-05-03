/**
 * Created by paulo on 02/05/2023.
 */

#ifndef DEBUG_MENU_INFRA_H
#define DEBUG_MENU_INFRA_H

#include "fonts.h"
#include "sh1106.h"

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


/**
 * @brief Enumera os tipos de tela.
 */
typedef enum screens {
    MONITOR_SCREEN = 0, /**< Tipo de tela cuja finalidade é mostrar informações. */
    SETTING_SCREEN,     /**< Tipo de tela cuja finalidade é modificar um atributo. */
    SUBMENU_SCREEN,     /**< Tipo de tela onde novas opções são navegáveis e selecionáveis. */
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
        uint8_t is_bitmap : 1;  /**< Indica o conteúdo é um bitmap. */
        uint8_t is_visible : 1; /**< Indica o conteúdo é visível atualmente. */
        uint8_t padding : 6;    /**< Padding. */
    } opt;                      /**< Opções do conteúdo. */
} content_t;

/**
 * @brief Descreve a identificação de uma tela.
 */
typedef struct screen_info {
    const screens_t type;         /**< Tipo de tela atual. */
    const uint8_t id;             /**< Identificador da tela atual. */
    const uint8_t content_amount; /**< Quantidade de conteúdos na página. */
} info_t;

/**
 * @brief Descreve uma tela.
 */
typedef struct screen_style {
    const info_t details;

    void (*const show)(void);

    content_t* contents;
} screen_style_t;

/**
 * @brief Estrutura de controle do menu.
 */
typedef struct navigator {
    screen_style_t* current_screen;
} navigator_t;

/**
 * @brief Desenha a tela atual no display.
 *
 * @param navigator Navegador responsável pela lógica do menu.
 */
void show_screen(navigator_t* navigator);

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
 * @brief Imprime um array de conteúdos na tela.
 *
 * @param[in] contents Conteúdos a serem impressos.
 * @param amount Número de conteúdos.
 */
inline void print_contents(content_t* contents, uint8_t amount) {
    for (uint8_t i = 0; i < amount; i++) {
        print_content(contents[i]);
    }
}

#endif//DEBUG_MENU_INFRA_H