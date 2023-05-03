//
// Created by paulo on 02/05/2023.
//

#include "screen_monitor.h"

void monitor_draws(void) {
    SH1106_drawLine(18, 33, 108, 33);
}

const uint8_t* mode_bitmaps[] = {
        mode_manual,
        mode_tracking,
        mode_go_to,
        mode_off,
};

content_t monitor_cnts[MONITOR_CONTENTS_AMOUNT] = {
        [MONITOR_DEC_LABEL] = STR_CONTENT_INIT("DEC.:", 46, 4, true, &fnt5x7),
        [MONITOR_DEC] = STR_CONTENT_INIT("%02dd%02d\"%02d'", 20, 16, true, &fnt5x7),

        [MONITOR_RA_LABEL] = STR_CONTENT_INIT("R.A.:", 46, 36, true, &fnt5x7),
        [MONITOR_RA] = STR_CONTENT_INIT("%02dh%02dm%02ds", 25, 48, true, &fnt5x7),

        [MONITOR_BITMAP] = BMP_CONTENT_INIT(mode_manual, 101, 26, 28, 28, true),
};