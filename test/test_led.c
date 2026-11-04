#include "unity.h"

/* Se incluye el .c y no el .h: asi la prueba ve la variable static del
   driver y la puede volver a cero antes de cada prueba. */
#include "led.c"

/* Fake del port: en lugar de tocar el GPIO, cuenta las llamadas y guarda
   el ultimo valor escrito. */
static uint32_t llamadas_write;
static uint32_t llamadas_toggle;
static bool ultimo_encendido;

void port_led_write(bool encendido) {
    llamadas_write++;
    ultimo_encendido = encendido;
}

void port_led_toggle(void) {
    llamadas_toggle++;
}

void setUp(void) {
    s_led.state = ST_UNINIT;
    llamadas_write = 0U;
    llamadas_toggle = 0U;
    ultimo_encendido = false;
}

void tearDown(void) {
}

void test_init_con_null_devuelve_error_de_parametro(void) {
    TEST_ASSERT_EQUAL(LED_ERR_PARAM, led_init(NULL));
}

void test_toggle_sin_init_no_toca_el_port(void) {
    TEST_ASSERT_EQUAL(LED_ERR_STATE, led_toggle(led_instancia()));
    TEST_ASSERT_EQUAL_UINT32(0, llamadas_toggle);
}

void test_toggle_llama_una_vez_al_port(void) {
    led_t *led = led_instancia();
    led_init(led);

    TEST_ASSERT_EQUAL(LED_OK, led_toggle(led));
    TEST_ASSERT_EQUAL_UINT32(1, llamadas_toggle);
}

void test_prender_escribe_encendido(void) {
    led_t *led = led_instancia();
    led_init(led);

    TEST_ASSERT_EQUAL(LED_OK, led_prender(led));
    TEST_ASSERT_EQUAL_UINT32(1, llamadas_write);
    TEST_ASSERT_TRUE(ultimo_encendido);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init_con_null_devuelve_error_de_parametro);
    RUN_TEST(test_toggle_sin_init_no_toca_el_port);
    RUN_TEST(test_toggle_llama_una_vez_al_port);
    RUN_TEST(test_prender_escribe_encendido);
    return UNITY_END();
}
