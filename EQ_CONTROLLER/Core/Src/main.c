/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "spi.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "astro_targets.h"
#include "flags.h"
#include "math.h"
#include "menu_nav.h"
#include "nrf24l01p.h"
#include "rotary_events.h"
#include "sh1106.h"
#include <memory.h>
#include <stdio.h>
#include "menu_flow.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum {
    NORTH = 0,
    SOUTH,
} hemisphere_t;

typedef enum {
    MANUAL_MODE = 0,
    TRACKING_MODE,
    GOTO_MODE,
    OFF_MODE,
    _EQM_MODES_AMOUNT,
} eqm_mode_t;

typedef enum {
    NONE = 0,
    DEC_SETTINGS,
    RA_SETTINGS,
    CONTRAST_SETTINGS,
    CONTRAST_TIME_SETTINGS,
    HEMISPHERE_SETTINGS,
    _SETTINGS_AMOUNT,
} settings_t;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MENU_SCREEN_ROWS 6
#define ROW_SPACE_PX 10
#define SELECTION_ARROW_DELAY 20
#define DEG_TO_RAD_CONST (M_PI / 180)

#define EQM_RF_CHANNEL 0
#define TEST_CARRIER 0

#if TEST_CARRIER == 1
#define ITERATIONS 300
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint32_t packets_lost = 0;// global counter of lost packets

char* setting_strings[_SETTINGS_AMOUNT] = {
        [NONE] = "",
        [DEC_SETTINGS] = "Declination:",
        [RA_SETTINGS] = "Right Ascension:",
        [CONTRAST_SETTINGS] = "Adjust the contrast:",
        [CONTRAST_TIME_SETTINGS] = "Screen timeout:",
        [HEMISPHERE_SETTINGS] = "Choose the hemisphere:",
};

char* mode_menu_strings[_EQM_MODES_AMOUNT] = {
        [MANUAL_MODE] = "Manual Mode",
        [TRACKING_MODE] = "Start Tracking",
        [GOTO_MODE] = "Go to Target",
        [OFF_MODE] = "Free Movement"};

struct {
    angle_t DEC;
    time__t RA;
    uint8_t screen_contrast;      /**< relative brightness */
    uint8_t screen_contrast_time; /**< time to auto reduce the brightness, in seconds */
    hemisphere_t hemisphere;      /**< at telescope location */
    eqm_mode_t mode;
} settings_values;

struct {

    uint8_t size;
    union {
        struct {
            uint8_t head;
            uint8_t selection;
        } raw;
        struct {
            main_menu_selection_t head;
            main_menu_selection_t selection;
        } main_menu;
        struct {
            target_t head;
            target_t selection;

        } target_menu;
        struct {
            eqm_mode_t head;
            eqm_mode_t selection;
        } mode_menu;
    };
} menu_data = {
        .size = _MAIN_MENU_AMOUNT,
};

struct {
    screen_t curr_screen;
    union {
        nav_menu_t menu;
        settings_t setting;
        uint8_t raw;
    } kind;
} screen = {
        .curr_screen = MENU__SCREEN,
        .kind = {
                .menu = MAIN_MENU,
        },
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void nRF24_TX_ESB_setup(const uint8_t* addr);

/**
 * @brief Deals with the list menu arithmetic, should always be called before actually showing the menu.
 */
void load_list_menu_changes(void);

void load_settings_changes(void);

void handle_nav_menu_select(uint8_t current_selection);

void handle_monitor_select(void);

void handle_settings_select(void);

void show_settings_adjust(settings_t setting);

void show_main_menu();

void show_target_menu();

void show_mode_menu();

void monitor_draws();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

static void update_home_handler();

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_I2C2_Init();
    MX_SPI2_Init();
    /* USER CODE BEGIN 2 */

    bool was_selected[_SCREEN_AMOUNT] = {false};
    static const uint8_t nRF24_ADDR[] = "EQM0";

    nrf24_data_t recv_data = {0};

    const nrf24_data_t init_msg = {
            .kind = COMMAND,
            .size = {
                    .data = 7,
                    .payload = PLD_LEN,
            },
            .data = "Connect",
    };

    astro_targets_init();
    nRF24_TX_ESB_setup(nRF24_ADDR);
    SH1106_cleanInit();
    //SH1106_drawBitmapFullscreen(eqmount_logo);
    SH1106_drawBitmapFullscreen(tury_hmi);
    SH1106_flush();
    while (1)
        ; /** Test screen only*/
    HAL_Delay(2000);

#if TEST_CARRIER == 1
    uint16_t channel_offset = 0;
    while (true) {
        /** Keep sending the carrier */
        nRF24_StartCarrier(nRF24_TXPWR_0dBm,
                           (uint8_t) (EQM_RF_CHANNEL + 64 * cos((channel_offset / (double) ITERATIONS) * 2 * 3.1415)));
        HAL_Delay(1);
        channel_offset++;
        if (channel_offset > ITERATIONS) {
            channel_offset = 0;
        }
    }
#endif

#ifdef USE_NRF24L01
    uint16_t retries = 0;
    char* loading_points[] = {"", ".", "..", "..."};
    char str_buff[32] = {0};

    while (!nRF24_check(nRF24_ADDR)) {
        retries++;
        nRF24_TX_ESB_setup(nRF24_ADDR);
        SH1106_clear();
        SH1106_printStr(20, (SCR_H / 2) - 8, "ERRO - NRF24", &fnt7x10);
        sprintf(str_buff, "Retries: %d", retries);
        SH1106_printStr(20, (3 * SCR_H / 4) - 8, str_buff, &fnt7x10);
        SH1106_flush();
        HAL_Delay(100);
    }

    retries = 0;
    nRF24_StopListening();
    while (!nRF24_Talk(init_msg, NULL, nRF24_MODE_TX)) {
        retries++;
        SH1106_clear();
        SH1106_printStr(3, (SCR_H / 2) - 12, "Mount not found", &fnt7x10);
        sprintf(str_buff, "Searching %s", loading_points[retries % 4]);
        SH1106_printStr(15, (3 * SCR_H / 4) - 12, str_buff, &fnt7x10);
        SH1106_flush();
        HAL_Delay(100);
    }

#endif

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        switch (screen.curr_screen) {

            case MENU__SCREEN:
                load_list_menu_changes();
                switch (screen.kind.menu) {

                    case MAIN_MENU:
                        show_main_menu();
                        break;
                    case TARGET_MENU:
                        show_target_menu();
                        break;
                    case EQM_MODE_MENU:
                        show_mode_menu();
                        break;
                }
                break;
            case SETTINGS__SCREEN:
                load_settings_changes();
                show_settings_adjust(screen.kind.setting);
                break;
            case MONITOR__SCREEN:
                monitor_draws();
                break;
            default:
                break;
        }

        was_selected[screen.curr_screen] = rotary_peek_press();

        if (was_selected[MENU__SCREEN]) {
            handle_nav_menu_select(menu_data.raw.selection);
            was_selected[MENU__SCREEN] = false;
        } else if (was_selected[MONITOR__SCREEN]) {
            handle_monitor_select();
            was_selected[MONITOR__SCREEN] = false;
        } else if (was_selected[SETTINGS__SCREEN]) {
            handle_settings_select();
            was_selected[SETTINGS__SCREEN] = false;
        }
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void nRF24_TX_ESB_setup(const uint8_t* addr) {

    // Do the initial configurations.
    nRF24_init(addr, EQM_RF_CHANNEL);
    nRF24_StopListening();
}

static void handle_list_menu_changes(uint8_t max_index, void* current_selection, void* current_head) {
    int8_t tmp_sel;

    tmp_sel = *(uint8_t*) current_selection;
    tmp_sel += rotary_pop_dir() == CCW ? -1 : 1;
    if (tmp_sel >= max_index) {
        tmp_sel = max_index - 1;
    } else if (tmp_sel < 0) {
        tmp_sel = 0;
    }
    *(uint8_t*) current_selection = (uint8_t) tmp_sel;

    if (tmp_sel >= (*(uint8_t*) current_head + MENU_SCREEN_ROWS)) {
        (*(uint8_t*) current_head)++;
    } else if (tmp_sel < *(uint8_t*) current_head) {
        (*(uint8_t*) current_head)--;
    }
}

static void
handle_settings_menu_changes(void* settings_value, int32_t min_value, int32_t max_value, uint8_t decrement) {
    int32_t tmp_val;

    tmp_val = *(int32_t*) settings_value;
    tmp_val += rotary_pop_dir() == CCW ? -decrement : decrement * 10;
    if (tmp_val > max_value) {
        tmp_val = max_value;
    } else if (tmp_val < min_value) {
        tmp_val = min_value;
    }
    *(int32_t*) settings_value = tmp_val;
}

static void handle_menu_list_arrow(bool is_pressed, void* current_selection, void* current_head) {

    SH1106_drawBitmap(2 + (is_pressed * 4),
                      2 + (((*(uint8_t*) current_selection) - (*(uint8_t*) current_head)) * ROW_SPACE_PX),
                      CUSTOM_CHAR_W,
                      CUSTOM_CHAR_H, arrow);
}

static void main_menu_select_handler(main_menu_selection_t selected) {
    switch (selected) {
        case DECLINATION:
            screen.kind.setting = DEC_SETTINGS;
            break;
        case RIGHT_ASCENSION:
            screen.kind.setting = RA_SETTINGS;
            break;
        case CONTRAST:
            screen.kind.setting = CONTRAST_SETTINGS;
            break;
        case CONTRAST_TIME:
            screen.kind.setting = CONTRAST_TIME_SETTINGS;
            break;
        case HEMISPHERE:
            screen.kind.setting = HEMISPHERE_SETTINGS;
            break;
        case TGT_SELECTION:
            screen.curr_screen = MENU__SCREEN;
            screen.kind.menu = TARGET_MENU;
            break;
        case UPDT_HOME:
            screen.curr_screen = MONITOR__SCREEN;
            screen.kind.setting = NONE;
            update_home_handler();
            break;
        case EQM_MODE:
            screen.curr_screen = MENU__SCREEN;
            screen.kind.menu = EQM_MODE_MENU;
            break;
        case MONITOR:
        default:
            screen.curr_screen = MONITOR__SCREEN;
            screen.kind.setting = NONE;
            break;
    }
}

static void update_home_handler() {
    nrf24_data_t out_msg;
    nrf24_data_t in_msg;
    transf_t t;
    uint8_t pld_len;

    nRF24_PrepareData("GET_DEC_RA_HOME", 15, REQUEST, &out_msg);
    while (!nRF24_Talk(out_msg, &in_msg, nRF24_MODE_TX))
        ;
    nRF24_RetrieveData(in_msg, &settings_values.RA);
}

static void target_menu_select_handler(target_t selected) {
    astro_target_t tgt;

    if (selected > _TARGET_AMOUNT) {
        return;
    }

    tgt = astro_target_get(selected);
    settings_values.RA = tgt.position.right_ascension;
    settings_values.DEC = tgt.position.declination;
}

static void mode_menu_select_handler(eqm_mode_t select) {
    nrf24_data_t mode_set_msg;

    if (select > _EQM_MODES_AMOUNT) {
        return;
    }

    settings_values.mode = select;
    switch (select) {

        case MANUAL_MODE:
            nRF24_PrepareData("MANUAL", 7, COMMAND, &mode_set_msg);
            break;
        case TRACKING_MODE:
            nRF24_PrepareData("TRACK", 6, COMMAND, &mode_set_msg);
            break;
        case GOTO_MODE:
            nRF24_PrepareData("GOTO", 5, COMMAND, &mode_set_msg);
            break;
        case OFF_MODE:
            nRF24_PrepareData("RELEASE", 8, COMMAND, &mode_set_msg);
            break;
        default:
            nRF24_PrepareData("NOP", 4, COMMAND, &mode_set_msg);
            break;
    }

    while (!nRF24_Talk(mode_set_msg, NULL, nRF24_MODE_TX)) {
        HAL_Delay(10);
    }
}

void handle_nav_menu_select(uint8_t current_selection) {
    menu_data.raw.selection = 0;
    menu_data.raw.head = 0;

    switch (screen.kind.menu) {

        case MAIN_MENU:
            screen.curr_screen = SETTINGS__SCREEN;
            main_menu_select_handler((main_menu_selection_t) current_selection);
            break;
        case TARGET_MENU:
            screen.curr_screen = MONITOR__SCREEN;
            screen.kind.setting = NONE;
            target_menu_select_handler((target_t) current_selection);
            break;
        case EQM_MODE_MENU:
            screen.curr_screen = MONITOR__SCREEN;
            screen.kind.setting = NONE;
            mode_menu_select_handler((eqm_mode_t) current_selection);
            break;
        default:
            break;
    }

    rotary_pop_press();
}

void handle_monitor_select(void) {
    if (rotary_pop_press()) {
        screen.curr_screen = MENU__SCREEN;
        screen.kind.menu = MAIN_MENU;
    }
}

void handle_settings_select(void) {
    switch (screen.kind.setting) {
        //TODO
        case DEC_SETTINGS:
            break;
        case RA_SETTINGS:
            break;
        case CONTRAST_SETTINGS:
            break;
        case CONTRAST_TIME_SETTINGS:
            break;
        case HEMISPHERE_SETTINGS:
            break;
        case NONE:
        default:
            break;
    }

    if (rotary_pop_press()) {
        screen.curr_screen = MENU__SCREEN;
        screen.kind.menu = MAIN_MENU;
    }
}

void load_list_menu_changes(void) {
    uint8_t menu_size = 0;
    uint8_t* menu_selection = 0;
    uint8_t* menu_head = 0;

    switch (screen.kind.menu) {
        case MAIN_MENU:
            menu_size = _MAIN_MENU_AMOUNT;
            menu_selection = (uint8_t*) &menu_data.main_menu.selection;
            menu_head = (uint8_t*) &menu_data.main_menu.head;
            break;
        case TARGET_MENU:
            menu_size = _TARGET_AMOUNT;
            menu_selection = (uint8_t*) &menu_data.target_menu.selection;
            menu_head = (uint8_t*) &menu_data.target_menu.head;
            break;
        case EQM_MODE_MENU:
            menu_size = _EQM_MODES_AMOUNT;
            menu_selection = (uint8_t*) &menu_data.mode_menu.selection;
            menu_head = (uint8_t*) &menu_data.mode_menu.head;
            break;
        default:
            break;
    }

    if (rotary_peek_dir() != NOT_MOVING) {
        handle_list_menu_changes(menu_size, menu_selection, menu_head);
    }
}

static void show_declination(char* buffer, uint8_t x_offset, uint8_t y_offset) {
    uint8_t x_shift = x_offset;

    sprintf(buffer, "%c", (settings_values.DEC.decimal_degrees > 0) ? 'N' : 'S');
    SH1106_printStr(SCR_W - 30, y_offset, buffer, &fnt7x10);
    sprintf(buffer, "%02d", settings_values.DEC.degrees);
    x_shift += SH1106_printStr(x_offset, y_offset, buffer, &fnt7x10);
    x_shift += SH1106_printStr(x_shift, y_offset - 3, "o", &fnt7x10);
    sprintf(buffer, "%02d'%02d\"", settings_values.DEC.arc_minutes, settings_values.DEC.arc_seconds);
    SH1106_printStr(x_shift + 2, y_offset, buffer, &fnt7x10);
}

static void show_right_ascension(char* buffer, uint8_t x_offset, uint8_t y_offset) {

    sprintf(buffer, "%02dh%02dm%02ds", settings_values.RA.hours, settings_values.RA.minutes,
            settings_values.RA.seconds);
    SH1106_printStr(x_offset, y_offset, buffer, &fnt7x10);
}

void show_target_menu() {
    uint8_t str_sel = 0;
    bool is_pressed = rotary_peek_press();

    SH1106_clear();

    for (uint8_t current_str_y = 0; current_str_y < MENU_SCREEN_ROWS; current_str_y++) {
        if (str_sel + menu_data.target_menu.head == _TARGET_AMOUNT) {
            break;
        }
        SH1106_printStr(4 + CUSTOM_CHAR_W, 2 + current_str_y * ROW_SPACE_PX,
                        astro_target_get(str_sel + menu_data.target_menu.head).name,
                        &fnt5x7);
        str_sel++;
    }

    handle_menu_list_arrow(is_pressed, &menu_data.target_menu.selection,
                           &menu_data.target_menu.head);

    SH1106_flush();
    if (is_pressed) {
        HAL_Delay(SELECTION_ARROW_DELAY);
    }
}

void show_mode_menu() {
    uint8_t str_sel = 0;
    bool is_pressed = rotary_peek_press();

    SH1106_clear();

    for (uint8_t current_str_y = 0; current_str_y < MENU_SCREEN_ROWS; current_str_y++) {
        if (str_sel + menu_data.mode_menu.head == _EQM_MODES_AMOUNT) {
            break;
        }
        SH1106_printStr(4 + CUSTOM_CHAR_W, 2 + current_str_y * ROW_SPACE_PX,
                        mode_menu_strings[str_sel + menu_data.mode_menu.head],
                        &fnt5x7);
        str_sel++;
    }

    handle_menu_list_arrow(is_pressed, &menu_data.mode_menu.selection,
                           &menu_data.mode_menu.head);

    SH1106_flush();
    if (is_pressed) {
        HAL_Delay(SELECTION_ARROW_DELAY);
    }
}

void show_settings_adjust(settings_t setting) {
    static const uint8_t X_OFFSET = 20;
    static const uint8_t Y_OFFSET = 30;
    static const uint8_t CENTER_X = 64;
    static const uint8_t CENTER_Y = 44;
    static const uint8_t RADIUS = 10;
    static const uint8_t INNER_RADIUS = RADIUS - 3;
    static const uint8_t OUTER_RADIUS = RADIUS + 4;
    const double dec_in_radians = settings_values.DEC.decimal_degrees * DEG_TO_RAD_CONST;
    double curr_cos;
    double curr_sin;
    char buffer[11] = {0};

    SH1106_clear();

    SH1106_printStr(2, 2, setting_strings[setting], &fnt5x7);
    SH1106_drawHLine(0, SCR_W - 20, 11);

    switch (setting) {

        case DEC_SETTINGS:
            show_declination(buffer, X_OFFSET, Y_OFFSET - 10);

            SH1106_drawCircle(CENTER_X, CENTER_Y, RADIUS);
            curr_cos = cos(dec_in_radians);
            curr_sin = sin(dec_in_radians);
            SH1106_drawLine(CENTER_X + (curr_cos * INNER_RADIUS), CENTER_Y + (curr_sin * INNER_RADIUS),
                            CENTER_X + (curr_cos * OUTER_RADIUS), CENTER_Y + (curr_sin * OUTER_RADIUS));
            break;
        case RA_SETTINGS:
            show_right_ascension(buffer, X_OFFSET + 6, Y_OFFSET - 10);
            SH1106_drawCircle(CENTER_X, CENTER_Y, RADIUS);//TODO: colocar indicador de visibilidade
            break;
        case CONTRAST_SETTINGS:
            sprintf(buffer, "%d%%", settings_values.screen_contrast);
            SH1106_printStr(X_OFFSET + 26, Y_OFFSET, buffer, &fnt7x10);
            break;
        case CONTRAST_TIME_SETTINGS:
            sprintf(buffer, "%ds", settings_values.screen_contrast_time);
            SH1106_printStr(X_OFFSET + 26, Y_OFFSET, buffer, &fnt7x10);
            break;
        case HEMISPHERE_SETTINGS:
            sprintf(buffer, "%s", (settings_values.hemisphere == NORTH) ? "North" : "South");
            SH1106_printStr(X_OFFSET + 6, Y_OFFSET, buffer, &fnt7x10);
            SH1106_drawBitmap(80, Y_OFFSET - 6, SETTINGS_BITMAP_W, SETTINGS_BITMAP_H,
                              settings_values.hemisphere == NORTH ? north_hemisphere : south_hemisphere);
            break;
        case NONE:
        default:
            break;
    }

    SH1106_flush();
}

void load_settings_changes(void) {
    int32_t min;
    int32_t max;
    uint8_t decrement;
    int32_t tmp_value;
    void* setting = NULL;


    switch (screen.kind.setting) {

        case DEC_SETTINGS:
            setting = &settings_values.DEC;
            min = -90 * 3600;
            max = 90 * 3600;
            decrement = 10;
            tmp_value = settings_values.DEC.decimal_degrees * 3600;
            break;
        case RA_SETTINGS:
            setting = &settings_values.RA;
            min = 0;
            max = (24 * 3600) - 1;
            decrement = 10;
            tmp_value = settings_values.RA.decimal_hours * 3600;
            break;
        case CONTRAST_SETTINGS:
            setting = &settings_values.screen_contrast;
            min = 0;
            max = 100;
            decrement = 5;
            tmp_value = settings_values.screen_contrast;
            break;
        case CONTRAST_TIME_SETTINGS:
            setting = &settings_values.screen_contrast_time;
            min = 0;
            max = 255;
            decrement = 5;
            tmp_value = settings_values.screen_contrast_time;
            break;
        case HEMISPHERE_SETTINGS:
            setting = &settings_values.hemisphere;
            min = NORTH;
            max = SOUTH;
            decrement = 1;
            tmp_value = settings_values.hemisphere;
            break;
        case NONE:
        default:
            return;
    }

    if (rotary_peek_dir() != NOT_MOVING) {
        handle_settings_menu_changes(&tmp_value, min, max, decrement);
        switch (screen.kind.setting) {
            case DEC_SETTINGS:
                ((angle_t*) setting)->decimal_degrees = tmp_value / 3600.0;
                tmp_value = tmp_value >= 0 ? tmp_value : -tmp_value;//Correcting signedness;
                ((angle_t*) setting)->degrees = (int16_t) ((tmp_value / 3600) % 360);
                ((angle_t*) setting)->arc_minutes = (tmp_value / 60) % 60;
                ((angle_t*) setting)->arc_seconds = tmp_value % 60;
                break;
            case RA_SETTINGS:
                ((time__t*) setting)->decimal_hours = tmp_value / 3600.0;
                tmp_value = tmp_value >= 0 ? tmp_value : -tmp_value;//Correcting signedness;
                ((time__t*) setting)->hours = (tmp_value / 3600) % 24;
                ((time__t*) setting)->minutes = (tmp_value / 60) % 60;
                ((time__t*) setting)->seconds = tmp_value % 60;
                break;
            default:
                *((int32_t*) setting) = tmp_value;
        }
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */