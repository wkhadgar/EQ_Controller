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
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usb.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>

#include "bitmaps.h"
#include "eqm_settings.h"
#include "menu_drawer.h"
#include "menu_flow.h"
#include "message_manager.h"
#include "rotary_events.h"
#include "sh1106.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MENU_SCREEN_ROWS 6
#define ROW_SPACE_PX 10
#define SELECTION_ARROW_DELAY 20
#define DEG_TO_RAD_CONST (M_PI / 180)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

char* mode_menu_strings[EQM_MODES_AMOUNT] = {
        [MANUAL_MODE] = "Manual Mode",
        [TRACKING_MODE] = "Start Tracking",
        [GOTO_MODE] = "Go to Target",
        [OFF_MODE] = "Free Movement"};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void menu_process(navigator_t* navigator, eqm_settings_t const* settings) {
    switch (navigator->current_screen->details.type) {

        case MONITOR_SCREEN:
            navigator->ctrl.monitor.update_counter++;
            if (navigator->ctrl.monitor.update_counter >=
                navigator->ctrl.monitor.update_threshold) {
                navigator->ctrl.monitor.update_counter = 0;
                navigator->has_changes = true;
            }
            break;
        default:
            break;
    }

    if (navigator->has_changes) {
        update_screen(navigator, settings);
    }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#ifdef USE_NRF24L01
void nRF24_TX_ESB_setup(const uint8_t* addr) {

    // Do the initial configurations.
    nRF24_init(addr, EQM_RF_CHANNEL);
    nRF24_StopListening();
}
#endif

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

    eqm_settings_t settings = {
            .DEC.decimal_degrees = 0,
            .RA.decimal_hours = 0,
            .screen_contrast = 100,
            .screen_contrast_time = 100,
            .mode = OFF_MODE,
            .hemisphere = SOUTH,
    };

    navigator_t navigator = {
            .screens = screens_adresses,
            .current_screen = &monitor_screen,
            .ctrl = {
                    .menu = {
                            .head = 0,
                            .selection = 0,
                    },
            },
            .has_changes = true,
    };


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
  MX_TIM3_Init();
  MX_RTC_Init();
  MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */

    astro_targets_init();
    sh1106_init();
    sh1106_draw_bitmap(eqmount_logo, 0, 0, EQM_LOGO_W, EQM_LOGO_H);
    sh1106_flush();
    HAL_Delay(2000);

#if MSG_MNG_TEST_CARRIER
    uint16_t channel_offset = 0;
    while (true) {
        /** Keep sending the carrier */
        nRF24_StartCarrier(nRF24_TXPWR_0dBm,
                           (uint8_t) ((MSG_MNG_EQM_RF_CHANNEL + channel_offset) % 128));
        HAL_Delay(1);
        channel_offset++;
        if (channel_offset > MSG_MNG_CARRIER_ITERATIONS) {
            channel_offset = 0;
        }
    }
#endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        if (rotary_peek_dir() || rotary_peek_press()) {
            handle_rotary_event(&navigator, &settings);
        }

        menu_process(&navigator, &settings);
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//static void update_home_handler() {
//    nrf24_data_t out_msg;
//    nrf24_data_t in_msg;
//    transf_t t;
//    uint8_t pld_len;
//
//    nRF24_PrepareData("GET_DEC_RA_HOME", 15, REQUEST, &out_msg);
//    while (!nRF24_Talk(out_msg, &in_msg, nRF24_MODE_TX))
//        ;
//    nRF24_RetrieveData(in_msg, &settings_values.RA);
//}

//static void target_menu_select_handler(target_t selected) {
//    astro_target_t tgt;
//
//    if (selected > _TARGET_AMOUNT) {
//        return;
//    }
//
//    tgt = astro_target_get(selected);
//    settings_values.RA = tgt.position.right_ascension;
//    settings_values.DEC = tgt.position.declination;
//}

//static void mode_menu_select_handler(settings_t* settings, eqm_mode_t select) {
//    nrf24_data_t mode_set_msg;
//
//    if (select > EQM_MODES_AMOUNT) {
//        return;
//    }
//
//    settings.mode = select;
//    switch (select) {
//
//        case MANUAL_MODE:
//            nRF24_PrepareData("MANUAL", 7, COMMAND, &mode_set_msg);
//            break;
//        case TRACKING_MODE:
//            nRF24_PrepareData("TRACK", 6, COMMAND, &mode_set_msg);
//            break;
//        case GOTO_MODE:
//            nRF24_PrepareData("GOTO", 5, COMMAND, &mode_set_msg);
//            break;
//        case OFF_MODE:
//            nRF24_PrepareData("RELEASE", 8, COMMAND, &mode_set_msg);
//            break;
//        default:
//            nRF24_PrepareData("NOP", 4, COMMAND, &mode_set_msg);
//            break;
//    }
//
//    while (!nRF24_Talk(mode_set_msg, NULL, nRF24_MODE_TX)) {
//        HAL_Delay(10);
//    }
//}

/*
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
            break;
        case RA_SETTINGS:
            show_right_ascension(buffer, X_OFFSET + 6, Y_OFFSET - 10);
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

*/

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
