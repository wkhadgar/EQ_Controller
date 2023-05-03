/**
 * Created by paulo on 02/05/2023.
 */

#ifndef DEBUG_SCREEN_MONITOR_H
#define DEBUG_SCREEN_MONITOR_H

#include "bitmaps.h"
#include "menu_infra.h"

typedef enum monitor_contents {
    MONITOR_HEADER,
    MONITOR_RA,
    MONITOR_DEC,
    MONITOR_BITMAP,

    MONITOR_CONTENTS_AMOUNT,
} monitor_contents_t;

static content_t monitor_contents[MONITOR_CONTENTS_AMOUNT] = {
        [MONITOR_HEADER] = CONTENT_INIT("Monitor", 2, 1, true, false, false, true),
        [MONITOR_RA] = CONTENT_INIT("00h00m00s", 2, 20, false, false, false, true),
        [MONITOR_DEC] = CONTENT_INIT("00d00\"00s'", 2, 40, false, false, false, true),
        [MONITOR_BITMAP] = CONTENT_INIT(mode_off, 100, 30, false, false, true, true),
};

static void show_monitor(void) {
    print_str_content(monitor_contents[MONITOR_HEADER], fnt5x7);
}

static screen_style_t monitor_screen = {
        .details = {
                .id = 0,
                .type = MONITOR,
                .content_amount = MONITOR_CONTENTS_AMOUNT,
        },
        .contents = monitor_contents,
        .show_callback = &show_monitor,
};

#endif//DEBUG_SCREEN_MONITOR_H