#include "potenciometro.h"
#include "port_potenciometro.h"
#include <stddef.h>

#define PORCENTAJE_MAXIMO 100UL

typedef enum {
    ST_UNINIT = 0,
    ST_IDLE
} pot_state_t;

struct potenciometro {
    pot_state_t state;
};

static struct potenciometro s_pot;

potenciometro_t *pot_instancia(void) {
    return &s_pot;
}

pot_status_t pot_init(potenciometro_t *dev) {
    if (dev == NULL) return POT_ERR_PARAM;
    if (dev->state != ST_UNINIT) return POT_ERR_STATE;
    dev->state = ST_IDLE;
    return POT_OK;
}

pot_status_t pot_leer(const potenciometro_t *dev, uint8_t *out_porcentaje) {
    if (dev == NULL || out_porcentaje == NULL) return POT_ERR_PARAM;
    if (dev->state != ST_IDLE) return POT_ERR_STATE;

    uint32_t crudo;
    pot_status_t st = port_adc_leer_crudo(&crudo);
    if (st != POT_OK) return st;

    *out_porcentaje = (uint8_t)((crudo * PORCENTAJE_MAXIMO) / PORT_ADC_VALOR_MAXIMO);
    return POT_OK;
}
