/**
 * Created by paulo on 04/05/2023.
 */

#include "screen_right_ascension.h"


void ra_draws(void) {
    SH1106_drawHLine(0, SCR_W - 20, 11);
}

void right_ascension_handler(int8_t dir, eqm_settings_t* setting) {
    setting->RA.decimal_hours += (dir * MINUTE_IN_HOURS);

    if (setting->RA.decimal_hours >= 24) {
        setting->RA.decimal_hours = 0;
    } else if (setting->RA.decimal_hours < 0) {
        setting->RA.decimal_hours = (24 - MINUTE_IN_HOURS);
    }

    update_time_fields(&setting->RA);
    sprintf((char*) ra_cnts[RA_VALUE].data, "%02dh%02dm%02ds",
            setting->RA.hours, setting->RA.minutes, setting->RA.seconds);
}

content_t ra_cnts[RA_CONTENTS_AMOUNT] = {
        [RA_HEADER] = STR_CONTENT_INIT("Right Ascension:", 2, 2, true, &fnt5x7),
        [RA_VALUE] = STR_CONTENT_INIT("00h00m00s", 20, 30, true, &fnt5x7),
        [RA_BITMAP] = STR_CONTENT_INIT("HRS", 60, 50, true, &fnt5x7),
};