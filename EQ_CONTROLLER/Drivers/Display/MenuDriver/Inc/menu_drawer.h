/**
 * Created by paulo on 03/05/2023.
 */

#ifndef DEBUG_MENU_DRAWER_H
#define DEBUG_MENU_DRAWER_H

#include "menu_infra.h"
#include "menu_nav.h"

#define X_LEFT_PAD 30
#define Y_ROW_PAD 10
#define Y_BY_ENUM(enum_val) ((enum_val) * (Y_ROW_PAD))

/**
 * @brief Desenha a tela atual no display.
 *
 * @param navigator Navegador responsável pela lógica do menu.
 */
void update_screen(navigator_t* navigator);

#endif//DEBUG_MENU_DRAWER_H