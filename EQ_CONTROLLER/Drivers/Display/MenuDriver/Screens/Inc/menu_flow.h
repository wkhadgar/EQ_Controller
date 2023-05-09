/**
 * Created by paulo on 03/05/2023.
 */

#ifndef DEBUG_MENU_FLOW_H
#define DEBUG_MENU_FLOW_H

extern screen_properties_t monitor_screen;
extern screen_properties_t main_menu_screen;
extern screen_properties_t declination_screen;
extern screen_properties_t right_ascension_screen;
extern screen_properties_t tgt_sel_screen;
extern screen_properties_t tgt_conf_screen;
extern screen_properties_t mode_menu_screen;
/**
 * @brief Tabela endereços de todas as telas.
 */
static screen_properties_t* const screens_adresses[SCR_AMOUNT] = {
        [SCR_M_HOME] = &monitor_screen,
        [SCR_O_MAIN_MENU] = &main_menu_screen,
        [SCR_S_DECLINATION] = &declination_screen,
        [SCR_S_RIGHT_ASCENSION] = &right_ascension_screen,
        [SCR_O_TARGET_SELECTOR] = &tgt_sel_screen,
        [SCR_O_EQM_MODE] = &mode_menu_screen,
        [SCR_CONFIRM_TGT] = &tgt_conf_screen,
};
#endif//DEBUG_MENU_FLOW_H