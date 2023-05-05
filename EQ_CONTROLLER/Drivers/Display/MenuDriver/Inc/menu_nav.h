//
// Created by paulo on 02/05/2023.
//

#ifndef EQ_CONTROLLER_MENU_NAV_H
#define EQ_CONTROLLER_MENU_NAV_H

#include "menu_infra.h"
#include "rotary_events.h"

#define MENU_ROWS 6


/**
 * @brief Navega no menu de acordo com a direção indicada.
 *
 * @param[in,out] navigator Referência para o navegador atual.
 * @param direction Direção da navegação.
 */
void update_selection(navigator_t* navigator, int8_t direction);

/**
 * @brief Altera a configuração atual de acordo com a direção indicada.
 *
 * @param[in,out] navigator Referência para o navegador atual.
 * @param direction Direção da navegação.
 */
void update_setting(navigator_t* navigator, int8_t direction, eqm_settings_t* setting);


void handle_rotary_event(navigator_t* navigator, eqm_settings_t* settings);

/**
 * @brief Configura um callback de config.
 *
 * @param[in,out] navigator Navegador a ser configurado.
 */
inline void update_setting_callback(navigator_t* navigator) {
	navigator->ctrl.setting_handler = navigator->handler_table[navigator->current_screen->details.id];
}

/**
 * @brief Configura um fluxo de navegação.
 *
 * @param[in,out] navigator Navegador a ser configurado.
 */
inline void update_screen_targets(navigator_t* navigator) {
	navigator->next_screens = navigator->screen_flow[navigator->current_screen->details.id].flow;
}

/**
 * @brief Atualiza os dados de um conteúdo.
 *
 * @param[inout] navigator Navegador de controle.
 * @param index Índice do conteúdo a ter o dado atualizado.
 * @param[in] data Novo dado.
 */
inline void update_content(navigator_t* navigator, uint8_t index, uint8_t* data) {
	navigator->current_screen->contents[index].data = data;
}

#endif//EQ_CONTROLLER_MENU_NAV_H