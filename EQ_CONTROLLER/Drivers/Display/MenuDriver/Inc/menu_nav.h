//
// Created by paulo on 02/05/2023.
//

#ifndef EQ_CONTROLLER_MENU_NAV_H
#define EQ_CONTROLLER_MENU_NAV_H

#include "menu_infra.h"

#define MENU_ROWS 6

void handle_press(navigator_t* navigator);

/**
 * @brief Atualiza os dados de um conteúdo.
 *
 * @param[inout] navigator Navegador de controle.
 * @param index Índice do conteúdo a ter o dado atualizado.
 * @param[in] data Novo dado.
 */
void update_content(navigator_t* navigator, uint8_t index, uint8_t* data);

/**
 * @brief Navega no menu de acordo com a direção indicada.
 *
 * @param[in,out] navigator Referência para o navegador atual.
 * @param direction Direção da navegação.
 */
void update_selection(navigator_t* navigator, int8_t direction);

void update_setting(navigator_t* navigator);

/**
 * @brief Configura um fluxo de navegação.
 *
 * @param[in,out] navigator Navegador a ser configurado.
 */
inline void update_screen_targets(navigator_t* navigator) {
    navigator->screen_flow = navigator->flow_table[navigator->current_screen->details.id];
}

#endif//EQ_CONTROLLER_MENU_NAV_H