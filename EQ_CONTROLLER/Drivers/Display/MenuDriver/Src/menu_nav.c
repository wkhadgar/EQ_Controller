//
// Created by paulo on 02/05/2023.
//

#include "menu_nav.h"

/**
 * @brief Configura o novo estado do menu após um evento de press.
 *
 * @param[in,out] navigator Referência para o navegador atual.
 */
static void handle_press(navigator_t* navigator) {
	switch (navigator->current_screen->details.type) {
		case MONITOR_SCREEN:
		case SETTING_SCREEN:
			navigator->current_screen = navigator->screen_flow[navigator->next_screens[0]].screen;
			break;
		case OPTIONS_SCREEN:
			navigator->current_screen = navigator->screen_flow[navigator->next_screens[navigator->ctrl.menu.selection]].screen;
			break;
	}
	
	switch (navigator->current_screen->details.type) {
		case SETTING_SCREEN:
			update_setting_callback(navigator);
			break;
		case OPTIONS_SCREEN:
			navigator->ctrl.menu.head = 0;
			navigator->ctrl.menu.selection = 0;
			break;
		default:
			break;
	}
	
	update_screen_targets(navigator);
}

static void handle_rotation(navigator_t* navigator, int8_t direction, eqm_settings_t* settings) {
	switch (navigator->current_screen->details.type) {
		case SETTING_SCREEN:
			update_setting(navigator, direction, settings);
			break;
		case OPTIONS_SCREEN:
			update_selection(navigator, direction);
			break;
		default:
			break;
	}
}

void handle_rotary_event(navigator_t* navigator, eqm_settings_t* settings) {
	if (rotary_pop_press()) {
		handle_press(navigator);
	} else {
		switch (rotary_pop_dir()) {
			case CW:
				handle_rotation(navigator, 5, settings);
				break;
			case CCW:
				handle_rotation(navigator, -1, settings);
				break;
			default:
				break;
		}
	}
}

void update_selection(navigator_t* navigator, int8_t direction) {
	int16_t new_selection = (int16_t) (navigator->ctrl.menu.selection + direction);
	
	if (new_selection < 0) {
		new_selection = 0;
	} else if ((navigator->ctrl.menu.head) && (new_selection < navigator->ctrl.menu.head)) {
		navigator->ctrl.menu.head--;
	} else if (new_selection == navigator->ctrl.menu.head + MENU_ROWS) {
		navigator->ctrl.menu.head++;
	} else if (new_selection == navigator->current_screen->details.content_amount) {
		new_selection = (int16_t) (navigator->current_screen->details.content_amount - 1);
	}
	
	navigator->ctrl.menu.selection = (uint8_t) new_selection;
}

void update_setting(navigator_t* navigator, int8_t direction, eqm_settings_t* setting) {
	if (navigator->ctrl.setting_handler != NULL) {
		navigator->ctrl.setting_handler(direction, setting);
	}
}