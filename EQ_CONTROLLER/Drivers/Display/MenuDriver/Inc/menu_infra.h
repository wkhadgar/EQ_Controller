/**
 * Created by paulo on 02/05/2023.
 */

#ifndef DEBUG_MENU_INFRA_H
#define DEBUG_MENU_INFRA_H

#define CONTENT_INIT(_data, _x, _y, _align_x, _align_y, _is_bitmap, _is_visible) \
    {                                                                            \
        .data = (uint8_t*) (_data),                                              \
        .pos = {                                                                 \
                .x = _x,                                                         \
                .y = _y,                                                         \
        },                                                                       \
        .opt = {                                                                 \
                .align_x = _align_x,                                             \
                .align_y = _align_y,                                             \
                .is_bitmap = _is_bitmap,                                         \
                .is_visible = _is_visible,                                       \
        },                                                                       \
    }

#include "Fonts.h"
#include "sh1106.h"
#include <stdint.h>

/**
 * @brief Enumera os tipos de tela.
 */
typedef enum screens {
    MONITOR = 0, /**< Tipo de tela cuja finalidade é mostrar informações. */
    SETTING,     /**< Tipo de tela cuja finalidade é modificar um atributo. */
    SUBMENU,     /**< Tipo de tela onde novas opções são navegáveis e selecionáveis. */
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
        uint8_t heigth; /**< Altura vertical do conteúdo na tela. */
    } dim;              /**< Detalha as informações de dimensões do conteúdo, usado para bitmaps. */

    struct options {
        uint8_t align_x : 1;    /**< Indica se a posição horizontal do conteúdo na tela é uma fração da tela. */
        uint8_t align_y : 1;    /**< Indica se a posição vertical do conteúdo na tela é uma fração da tela. */
        uint8_t is_bitmap : 1;  /**< Indica o conteúdo é um bitmap. */
        uint8_t is_visible : 1; /**< Indica o conteúdo é visível atualmente. */
        uint8_t padding : 4;    /**< Padding. */
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
    void (*const show_callback)(void);

    content_t* contents;
} screen_style_t;

/**
 * @brief Estrutura de controle do menu.
 */
typedef struct navigator {
    screen_style_t* current_screen;
} navigator_t;

void show_screen(navigator_t* navigator);

void print_str_content(content_t cnt, const Font_TypeDef* fnt);

#endif//DEBUG_MENU_INFRA_H