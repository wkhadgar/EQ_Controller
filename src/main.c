/**
* @file main.c
* @author Paulo Santos (pauloroberto.santos@edge.ufal.br)
* @brief Ponto de entrada da aplicação.
* @version 0.1
* @date 15-09-2023
*
* @copyright Copyright (c) 2023
*
*/

#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include "driver/rotary/rotary_events.h"

int main(void) {

    rotary_init();

    printk("Waiting one second.\n");

    k_sleep(K_MSEC(1000));

    while (1) {
        rotary_pop_dir();

        k_sleep(K_MSEC(1000));
    }

    return 0;
}