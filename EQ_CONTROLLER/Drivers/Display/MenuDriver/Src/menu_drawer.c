/**
 * Created by paulo on 03/05/2023.
 */

#include "menu_drawer.h"

#define HAS_PAGINATED_OPTIONS 0

void update_screen(navigator_t* navigator, eqm_settings_t const* settings) {
    SH1106_clear();


    if (navigator->current_screen->update_buffers != NULL) {
        navigator->current_screen->update_buffers(settings);
    }

    switch (navigator->current_screen->details.type) {
        case MONITOR_SCREEN:
        case SETTING_SCREEN:
        case CONFIRM_SCREEN:
            print_contents(navigator->current_screen->contents,
                           navigator->current_screen->details.content_amount);
            break;
        case OPTIONS_SCREEN:
            navigator->current_screen->cursor_bitmap->pos.y =
                    (navigator->ctrl.menu.selection - navigator->ctrl.menu.head) * Y_ROW_PAD;
            print_content(*navigator->current_screen->cursor_bitmap);

#if HAS_PAGINATED_OPTIONS == 1
            if (navigator->ctrl.menu.head + MENU_ROWS < navigator->current_screen->details.content_amount) {
#endif
            print_contents_rows(
                    navigator->current_screen->contents + navigator->ctrl.menu.head,
                    navigator->current_screen->contents[navigator->ctrl.menu.head].pos.y,
                    MENU_ROWS);
#if HAS_PAGINATED_OPTIONS == 1
            } else {
                print_contents_rows(
                        navigator->current_screen->contents + navigator->ctrl.menu.head,
                        navigator->current_screen->contents[navigator->ctrl.menu.head].pos.y,
                        navigator->current_screen->details.content_amount -
                        navigator->ctrl.menu.head);
            }
#endif
            break;
        default:
            break;
    }

    if (navigator->current_screen->post_draw_callback != NULL) {
        navigator->current_screen->post_draw_callback();
    }

    navigator->has_changes = false;

    SH1106_flush();
}