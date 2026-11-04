#ifndef POTENCIOMETRO_H
#define POTENCIOMETRO_H

#include <stdint.h>

typedef enum {
    POT_OK = 0,
    POT_ERR_PARAM,
    POT_ERR_STATE,
    POT_ERR_BUS
} pot_status_t;

typedef struct potenciometro potenciometro_t;   // tipo opaco

potenciometro_t *pot_instancia(void);
pot_status_t pot_init(potenciometro_t *dev);
pot_status_t pot_leer(const potenciometro_t *dev, uint8_t *out_porcentaje);

#endif
