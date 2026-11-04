#include "led.h"
#include "port_led.h"
#include <stddef.h>

typedef enum {
    ST_UNINIT = 0,
    ST_IDLE
} led_state_t;

struct led {
    led_state_t state;
};

static struct led s_led;

led_t *led_instancia(void) {
    return &s_led;
}

led_status_t led_init(led_t *dev) {
    if (dev == NULL) {
        return LED_ERR_PARAM;
    }
    if (dev->state != ST_UNINIT) {
        return LED_ERR_STATE;   // ya estaba inicializado
    }
    dev->state = ST_IDLE;
    return LED_OK;
}

led_status_t led_prender(const led_t *dev) {
    if (dev == NULL) return LED_ERR_PARAM;
    if (dev->state != ST_IDLE) return LED_ERR_STATE;
    port_led_write(true);
    return LED_OK;
}

led_status_t led_apagar(const led_t *dev) {
    if (dev == NULL) return LED_ERR_PARAM;
    if (dev->state != ST_IDLE) return LED_ERR_STATE;
    port_led_write(false);
    return LED_OK;
}

led_status_t led_toggle(const led_t *dev) {
    if (dev == NULL) return LED_ERR_PARAM;
    if (dev->state != ST_IDLE) return LED_ERR_STATE;
    port_led_toggle();
    return LED_OK;
}
