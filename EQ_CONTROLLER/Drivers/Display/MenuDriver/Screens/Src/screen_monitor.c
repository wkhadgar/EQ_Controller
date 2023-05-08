//
// Created by paulo on 02/05/2023.
//

#include "screen_monitor.h"
#include "eqm_settings.h"

const uint8_t* mode_bitmaps[] = {
        [MANUAL_MODE] = mode_manual,
        [TRACKING_MODE] = mode_tracking,
        [GOTO_MODE] = mode_go_to,
        [OFF_MODE] = mode_off,
};

static uint8_t dec_buffer[] = "000`00\"00'";
static uint8_t ra_buffer[] = "00h00m00s";
static uint8_t mode_buffer[32];

void monitor_draws(void) {
    SH1106_drawLine(18, 33, 108, 33);
}

static void update_buffers(eqm_settings_t* settings) {
    sprintf((char*) dec_buffer, "%03d`%02d\"%02d'",
            settings->DEC.degrees, settings->DEC.arc_minutes, settings->DEC.arc_seconds);
    sprintf((char*) ra_buffer, "%02dh%02dm%02ds",
            settings->RA.hours, settings->RA.minutes, settings->RA.seconds);
    memcpy(mode_buffer, mode_bitmaps[settings->mode], sizeof(mode_buffer));
}

static content_t monitor_cnts[MONITOR_CONTENTS_AMOUNT] = {
        [MONITOR_DEC_LABEL] = STR_CONTENT_INIT("DEC.:", 50, 4, true, &fnt5x7),
        [MONITOR_DEC] = STR_CONTENT_INIT(dec_buffer, 22, 16, true, &fnt7x10),

        [MONITOR_RA_LABEL] = STR_CONTENT_INIT("R.A.:", 50, 38, true, &fnt5x7),
        [MONITOR_RA] = STR_CONTENT_INIT(ra_buffer, 25, 50, true, &fnt7x10),

        [MONITOR_BITMAP] = BMP_CONTENT_INIT(mode_buffer, 111, 26, MODE_BITMAP_W, MODE_BITMAP_H, true),
};

screen_properties_t monitor_screen = {
        .details = {
                .id = SCR_M_HOME,
                .type = MONITOR_SCREEN,
                .content_amount = MONITOR_CONTENTS_AMOUNT,
        },
        .contents = monitor_cnts,
        .setting_callback = NULL,
        .cursor_bitmap = NULL,
        .update_buffers = &update_buffers,
        .post_draw = &monitor_draws,
};