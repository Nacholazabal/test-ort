#ifndef LED_H
#define LED_H

#include <stdint.h>

typedef enum {
    LED_OK = 0,
    LED_ERR_PARAM,
    LED_ERR_STATE
} led_status_t;

typedef struct led led_t;   // tipo opaco

led_t *led_instancia(void);
led_status_t led_init(led_t *dev);
led_status_t led_prender(const led_t *dev);
led_status_t led_apagar(const led_t *dev);
led_status_t led_toggle(const led_t *dev);

#endif
