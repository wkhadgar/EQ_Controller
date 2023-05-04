/**
 * Created by paulo on 03/05/2023.
 */

#ifndef DEBUG_MENU_FLOW_H
#define DEBUG_MENU_FLOW_H

#include "screen_declination.h"
#include "screen_main_menu.h"
#include "screen_monitor.h"

screen_style_t* screen_table[SCR_AMOUNT] = {
        [SCR_O_MAIN_MENU] = &main_menu_screen,
        [SCR_M_HOME] = &monitor_screen,
        [SCR_S_DECLINATION] = &declination_screen,
};

setting_callback_t settings_handlers_table[] = {
        [SCR_S_DECLINATION] = &declination_handler,
};

/** Screen Flows */
screens_t main_menu_flow_screens[] = {
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

screens_t monitor_flow_screens[] = {
        SCR_O_MAIN_MENU,
};

screens_t declination_flow_screens[] = {
        SCR_M_HOME,
};

/** Flow Table */
screens_t* flow_table[SCR_AMOUNT] = {
        [SCR_O_MAIN_MENU] = main_menu_flow_screens,
        [SCR_M_HOME] = monitor_flow_screens,
        [SCR_S_DECLINATION] = declination_flow_screens,
};

#endif//DEBUG_MENU_FLOW_H
