/**
 * Created by paulo on 02/05/2023.
 */

#include "menu_infra.h"

void show_screen(navigator_t* navigator) {
    navigator->current_screen->show_callback();
}

void print_str_content(content_t cnt, const Font_TypeDef* fnt) {
    SH1106_printStr(cnt.pos.x, cnt.pos.y, cnt.data, fnt);
}