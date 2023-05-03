/**
 * Created by paulo on 03/05/2023.
 */

#include "menu_drawer.h"

void update_screen(navigator_t* navigator) {
    SH1106_clear();

    switch (navigator->current_screen->details.type) {
        case MONITOR_SCREEN:
        case SETTING_SCREEN:
            print_contents(navigator->current_screen->contents, navigator->current_screen->details.content_amount);
            break;
        case MENU_SCREEN:
            if (navigator->ctrl.menu.head + MENU_ROWS >= navigator->current_screen->details.content_amount) {
                print_contents_rows(navigator->current_screen->contents,
                                    navigator->current_screen->contents[navigator->ctrl.menu.head].pos.y,
                                    navigator->current_screen->details.content_amount - navigator->ctrl.menu.head);
            } else {
                print_contents_rows(navigator->current_screen->contents,
                                    navigator->current_screen->contents[navigator->ctrl.menu.head].pos.y,
                                    MENU_ROWS);
            }

            navigator->ctrl.menu.cursor_bmp.pos.y = (navigator->ctrl.menu.head - navigator->ctrl.menu.selection) * Y_ROW_PAD;
            print_content(navigator->ctrl.menu.cursor_bmp);
            break;
    }

    if (navigator->current_screen->post_draw != NULL) {
        navigator->current_screen->post_draw();
    }

    SH1106_flush();
}