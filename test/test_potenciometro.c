#include "unity.h"

/* Se incluye el .c y no el .h: asi la prueba ve la variable static del
   driver y la puede volver a cero antes de cada prueba. */
#include "potenciometro.c"

#define CRUDO_MINIMO 0U
#define CRUDO_MAXIMO 4095U
#define CRUDO_MITAD 2048U

/* Stub del port: en lugar de leer el ADC, devuelve lo que pide la prueba */
static uint32_t stub_crudo;
static pot_status_t stub_resultado;

pot_status_t port_adc_leer_crudo(uint32_t *out_crudo) {
    *out_crudo = stub_crudo;
    return stub_resultado;
}

void setUp(void) {
    s_pot.state = ST_UNINIT;
    stub_crudo = CRUDO_MINIMO;
    stub_resultado = POT_OK;
}

void tearDown(void) {
}

void test_init_con_null_devuelve_error_de_parametro(void) {
    TEST_ASSERT_EQUAL(POT_ERR_PARAM, pot_init(NULL));
}

void test_init_dos_veces_devuelve_error_de_estado(void) {
    potenciometro_t *pot = pot_instancia();

    pot_init(pot);

    TEST_ASSERT_EQUAL(POT_ERR_STATE, pot_init(pot));
}

void test_leer_con_null_devuelve_error_de_parametro(void) {
    potenciometro_t *pot = pot_instancia();
    uint8_t porcentaje;
    pot_init(pot);

    TEST_ASSERT_EQUAL(POT_ERR_PARAM, pot_leer(NULL, &porcentaje));
    TEST_ASSERT_EQUAL(POT_ERR_PARAM, pot_leer(pot, NULL));
}

void test_leer_sin_init_devuelve_error_de_estado(void) {
    uint8_t porcentaje;

    TEST_ASSERT_EQUAL(POT_ERR_STATE, pot_leer(pot_instancia(), &porcentaje));
}

void test_lectura_minima_da_cero_por_ciento(void) {
    potenciometro_t *pot = pot_instancia();
    uint8_t porcentaje;
    pot_init(pot);
    stub_crudo = CRUDO_MINIMO;

    TEST_ASSERT_EQUAL(POT_OK, pot_leer(pot, &porcentaje));
    TEST_ASSERT_EQUAL_UINT8(0, porcentaje);
}

void test_lectura_maxima_da_cien_por_ciento(void) {
    potenciometro_t *pot = pot_instancia();
    uint8_t porcentaje;
    pot_init(pot);
    stub_crudo = CRUDO_MAXIMO;

    TEST_ASSERT_EQUAL(POT_OK, pot_leer(pot, &porcentaje));
    TEST_ASSERT_EQUAL_UINT8(100, porcentaje);
}

void test_lectura_a_mitad_da_cincuenta_por_ciento(void) {
    potenciometro_t *pot = pot_instancia();
    uint8_t porcentaje;
    pot_init(pot);
    stub_crudo = CRUDO_MITAD;

    TEST_ASSERT_EQUAL(POT_OK, pot_leer(pot, &porcentaje));
    TEST_ASSERT_EQUAL_UINT8(51, porcentaje);
}

void test_error_del_port_llega_al_que_llama(void) {
    potenciometro_t *pot = pot_instancia();
    uint8_t porcentaje;
    pot_init(pot);
    stub_resultado = POT_ERR_BUS;

    TEST_ASSERT_EQUAL(POT_ERR_BUS, pot_leer(pot, &porcentaje));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init_con_null_devuelve_error_de_parametro);
    RUN_TEST(test_init_dos_veces_devuelve_error_de_estado);
    RUN_TEST(test_leer_con_null_devuelve_error_de_parametro);
    RUN_TEST(test_leer_sin_init_devuelve_error_de_estado);
    RUN_TEST(test_lectura_minima_da_cero_por_ciento);
    RUN_TEST(test_lectura_maxima_da_cien_por_ciento);
    RUN_TEST(test_lectura_a_mitad_da_cincuenta_por_ciento);
    RUN_TEST(test_error_del_port_llega_al_que_llama);
    return UNITY_END();
}
