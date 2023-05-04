/**
 * Created by paulo on 03/05/2023.
 */

#include "screen_declination.h"

void dec_draws(void) {
    SH1106_drawHLine(0, SCR_W - 20, 11);
}

void declination_handler(int8_t dir, eqm_settings_t* setting) {
    setting->DEC.decimal_degrees += (dir * MINUTE_IN_DEGREES);

    if (setting->DEC.decimal_degrees >= 360) {
        setting->DEC.decimal_degrees = 0;
    } else if (setting->DEC.decimal_degrees < 0) {
        setting->DEC.decimal_degrees = (360 - MINUTE_IN_DEGREES);
    }

    update_angle_fields(&setting->DEC);
    sprintf((char*) dec_cnts[DEC_VALUE].data, "%02dd%02d\"%02d'",
            setting->DEC.degrees, setting->DEC.arc_minutes, setting->DEC.arc_seconds);
}

content_t dec_cnts[] = {
        [DEC_HEADER] = STR_CONTENT_INIT("Declination:", 2, 2, true, &fnt5x7),
        [DEC_VALUE] = STR_CONTENT_INIT("00d00\"00'", 20, 30, true, &fnt5x7),
        [DEC_BITMAP] = STR_CONTENT_INIT("DEG", 60, 50, true, &fnt5x7),
};
