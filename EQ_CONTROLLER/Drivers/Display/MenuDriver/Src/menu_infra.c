/**
 * Created by paulo on 02/05/2023.
 */

#include "menu_infra.h"
#include "sh1106.h"

void show_screen(navigator_t* navigator) {
	navigator->current_screen->show();
}

void update_content(navigator_t* navigator, uint8_t index, void* value) {
	navigator->current_screen->contents[index].data = value;
}