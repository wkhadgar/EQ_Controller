/*
 * Fonts.h
 *
 *  Created on: Aug 24, 2022
 *      Author: paulo
 */

#ifndef DISPLAY_INC_FONTS_H_
#define DISPLAY_INC_FONTS_H_

#include <stdint.h>

/**
 * @brief  Font structure scan lines enumeration
 */
enum {
    FONT_V = 0, /**< Vertical font scan lines. */
    FONT_H = 1, /**< Horizontal font scan lines. */
};

/**
 * @brief Describes a font.
 */
typedef struct font {
    const uint8_t width;        /**< Width of character. */
    const uint8_t height;       /**< Height of character. */
    const uint8_t BPC;          /**< Bytes for one character. */
    const uint8_t scan;         /**< Font scan lines behavior. */
    const uint8_t min_char;     /**< Code of the first known symbol. */
    const uint8_t max_char;     /**< Code of the last known symbol. */
    const uint8_t unknown_char; /**< Code of the unknown symbol. */
    const uint8_t characters[]; /**< Font data. */
} font_t;


extern const font_t fnt5x7;
extern const font_t fnt7x10;


#endif /* DISPLAY_INC_FONTS_H_ */