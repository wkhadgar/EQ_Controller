/**
* @file rotary_events.c
* @author Paulo Santos (pauloxrms@gmail.com)
* @brief Defines rotary encoder behaviour.
* @version 0.1
* @date 15-06-2023
*
* @copyright Copyright (c) 2023
*
*/

#include "rotary_events.h"

/**
 * @brief Estrutura que representa o pino trigger.
 */
static const struct gpio_dt_spec rotary_trigger =
        GPIO_DT_SPEC_GET(DT_NODELABEL(rot_trig), gpios);

/**
 * @brief Estrutura que representa o pino de direção de rotação.
 */
static const struct gpio_dt_spec rotary_clockwise =
        GPIO_DT_SPEC_GET(DT_NODELABEL(rot_clkw), gpios);

/**
 * @brief Estrutura que representa o pino do botão.
 */
static const struct gpio_dt_spec rotary_button =
        GPIO_DT_SPEC_GET(DT_NODELABEL(rot_but), gpios);

/**
 * @brief Callback de IRQ para o botão.
 */
static struct gpio_callback button_cb;

/**
 * @brief Callback de IRQ para a rotação do encoder.
 */
static struct gpio_callback spin_cb;

/**
 * @brief ISR para os eventos de press/release.
 *
 * @param[in] dev Botão associado.
 * @param[in] cb Callback desta ISR.
 * @param pins Máscara para os pinos desta ISR.
 */
static void rotary_button_isr(const struct device* dev, struct gpio_callback* cb,
                              uint32_t pins);

/**
 * @brief ISR para os eventos de rotação.
 *
 * @param[in] dev Trigger associado.
 * @param[in] cb Callback desta ISR.
 * @param pins Máscara para os pinos desta ISR.
 */
static void rotary_spin_isr(const struct device* dev, struct gpio_callback* cb,
                            uint32_t pins);

volatile static struct {
    dir_t dir;
    bool is_press;
    bool is_release;
} rotary_data;

int rotary_init(void) {
    if (!gpio_is_ready_dt(&rotary_trigger) || !gpio_is_ready_dt(&rotary_clockwise) || !gpio_is_ready_dt(&rotary_button)) {
        return -EBUSY;
    }

    if (gpio_pin_configure_dt(&rotary_button, GPIO_INT_EDGE) || gpio_pin_configure_dt(&rotary_trigger, GPIO_INT_EDGE_RISING) || gpio_pin_configure_dt(&rotary_clockwise, GPIO_INPUT)) {
        return -ENODEV;
    }

    gpio_init_callback(&button_cb, rotary_button_isr, BIT(rotary_button.pin));
    gpio_init_callback(&spin_cb, rotary_spin_isr, BIT(rotary_trigger.pin));

    gpio_add_callback(rotary_button.port, &button_cb);
    gpio_add_callback(rotary_trigger.port, &spin_cb);

    return 0;
}

dir_t rotary_pop_dir(void) {
    dir_t direction;

    if (rotary_data.dir) {
        direction = rotary_data.dir;
        rotary_data.dir = NOT_MOVING;
        k_msleep(SPIN_DEBOUNCE_DELAY);
        return direction;
    }

    return NOT_MOVING;
}

bool rotary_pop_release(void) {
    if (rotary_data.is_release) {
        rotary_data.is_release = false;
        k_msleep(BUTTON_DEBOUNCE_DELAY);
        return true;
    }

    return false;
}

bool rotary_pop_press(void) {
    if (rotary_data.is_press) {
        rotary_data.is_press = false;
        k_msleep(BUTTON_DEBOUNCE_DELAY);
        return true;
    }

    return false;
}

dir_t rotary_peek_dir(void) {
    return rotary_data.dir;
}

bool rotary_peek_press(void) {
    return rotary_data.is_press;
}

bool rotary_peek_release(void) {
    return rotary_data.is_press;
}

static void rotary_button_isr(struct device const* dev, struct gpio_callback* cb,
                              uint32_t pins) {
    ARG_UNUSED(dev);
    ARG_UNUSED(cb);
    ARG_UNUSED(pins);

    if (gpio_pin_get_dt(&rotary_button)) {
        rotary_data.is_press = true;
    } else {
        rotary_data.is_release = true;
    }
}

static void rotary_spin_isr(const struct device* dev, struct gpio_callback* cb,
                            uint32_t pins) {
    ARG_UNUSED(dev);
    ARG_UNUSED(cb);
    ARG_UNUSED(pins);

    if (gpio_pin_get_dt(&rotary_clockwise)) {
        rotary_data.dir = CW;
    } else {
        rotary_data.dir = CCW;
    }
}