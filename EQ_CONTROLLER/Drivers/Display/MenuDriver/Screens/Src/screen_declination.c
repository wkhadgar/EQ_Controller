/**
 * Created by paulo on 03/05/2023.
 */

#include "screen_declination.h"

void dec_draws(void) {
    SH1106_drawHLine(0, SCR_W - 20, 11);
}

void declination_handler(int8_t dir) {
}

content_t dec_cnts[] = {
        [DEC_HEADER] = STR_CONTENT_INIT("Declination", 2, 2, true, &fnt5x7),
};