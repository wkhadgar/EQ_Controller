/**
 * Created by paulo on 03/05/2023.
 */

#include "menu_drawer.h"

#define HAS_PAGINATED_OPTIONS 0

void update_screen(navigator_t* navigator, eqm_settings_t* settings) {
    SH1106_clear();

    screen_properties_t* curr_screen = navigator->current_screen;

    if (curr_screen->update_buffers != NULL) {
        curr_screen->update_buffers(settings);
    }

    switch (curr_screen->details.type) {
        case MONITOR_SCREEN:
        case SETTING_SCREEN:
            print_contents(curr_screen->contents,
                           curr_screen->details.content_amount);
            break;
        case OPTIONS_SCREEN:
            curr_screen->cursor_bitmap->pos.y =
                    (navigator->ctrl.menu.selection - navigator->ctrl.menu.head) * Y_ROW_PAD;
            print_content(*curr_screen->cursor_bitmap);

#if HAS_PAGINATED_OPTIONS == 1
            if (navigator->ctrl.menu.head + MENU_ROWS >=
                    curr_screen->details.content_amount) {
                print_contents_rows(
                        curr_screen->contents + navigator->ctrl.menu.head,
                        curr_screen->contents[navigator->ctrl.menu.head].pos.y,
                        curr_screen->details.content_amount -
                                navigator->ctrl.menu.head);
            } else {
#endif
            print_contents_rows(
                    curr_screen->contents + navigator->ctrl.menu.head,
                    curr_screen->contents[navigator->ctrl.menu.head].pos.y,
                    MENU_ROWS);
#if HAS_PAGINATED_OPTIONS == 1
            }
#endif
            break;
    }

    if (curr_screen->post_draw != NULL) {
        curr_screen->post_draw();
    }

    navigator->has_changes = false;

    SH1106_flush();
}