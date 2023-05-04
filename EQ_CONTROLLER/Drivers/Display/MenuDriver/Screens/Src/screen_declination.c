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
        [DEC_HEADER] = STR_CONTENT_INIT("Declination:", 2, 2, true, &fnt5x7),
        [DEC_VALUE] = STR_CONTENT_INIT("%02dd%02d\"%02d'", 20, 30, true, &fnt5x7),
        [DEC_BITMAP] = STR_CONTENT_INIT("DEG", 60, 50, true, &fnt5x7),
};