/**
 * Created by paulo on 03/05/2023.
 */

#ifndef DEBUG_MENU_FLOW_H
#define DEBUG_MENU_FLOW_H

#include "screen_declination.h"
#include "screen_main_menu.h"
#include "screen_monitor.h"
#include "screen_right_ascension.h"

/**
 * @brief Fluxo de destino da tela menu principal.
 */
screens_t main_menu_flow_screens[MAIN_MENU_CONTENTS_AMOUNT] = {
        [MAIN_MENU_MONITOR] = SCR_M_HOME,
        [MAIN_MENU_DEC] = SCR_S_DECLINATION,
        [MAIN_MENU_RA] = SCR_NONE,
        [MAIN_MENU_TGT] = SCR_NONE,
        [MAIN_MENU_UPDATE] = SCR_NONE,
        [MAIN_MENU_CONT_VALUE] = SCR_NONE,
        [MAIN_MENU_CONT_TIME] = SCR_NONE,
        [MAIN_MENU_HEM] = SCR_NONE,
        [MAIN_MENU_EQMODE] = SCR_NONE,
};

/**
 * @brief Fluxo de destino da tela do monitor.
 */
screens_t monitor_flow_screens[] = {
        SCR_O_MAIN_MENU,
};

/**
 * @brief Fluxo de destino da tela de configuração de declinação.
 */
screens_t declination_flow_screens[] = {
        SCR_M_HOME,
};

/**
 * @brief Fluxo de destino da tela de configuração de ascensão reta.
 */
screens_t right_ascension_flow_screens[] = {
        SCR_M_HOME,
};

/**
 * @brief Tabela de fluxos de destino de todas as telas.
 */
screen_flow_t scr_flow[SCR_AMOUNT] = {
        [SCR_M_HOME] = {
                .screen = &monitor_screen,
                .flow = monitor_flow_screens,
        },
        [SCR_O_MAIN_MENU] = {
                .screen = &main_menu_screen,
                .flow = main_menu_flow_screens,
        },
        [SCR_S_DECLINATION] = {
                .screen = &declination_screen,
                .flow = declination_flow_screens,
        },
        [SCR_S_RIGHT_ASCENSION] = {
                .screen = &right_ascension_screen,
                .flow = right_ascension_flow_screens,
        },
};

/**
 * @brief Tabela de callbacks das settings.
 */
setting_callback_t settings_handlers_table[] = {
        [SCR_S_DECLINATION] = &declination_handler,
        [SCR_S_RIGHT_ASCENSION] = &right_ascension_handler,
};

#endif//DEBUG_MENU_FLOW_H