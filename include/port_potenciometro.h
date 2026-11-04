#ifndef PORT_POTENCIOMETRO_H
#define PORT_POTENCIOMETRO_H

#include "potenciometro.h"   // para pot_status_t

#define PORT_ADC_VALOR_MAXIMO 4095UL   // ADC de 12 bits: 2^12 - 1

pot_status_t port_adc_leer_crudo(uint32_t *out_crudo);

#endif
