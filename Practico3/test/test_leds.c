#include "unity.h"
#include "leds.h"
#include "errores.h"

static uint16_t ledsVirtuales;
static gravedad_t gravedad_informada;


void RegistrarError (gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...){
    gravedad_informada = gravedad;
}


void setUp(void){
    LedsInit(&ledsVirtuales, RegistrarError);
}

void tearDown(void){
    gravedad_informada = 0xFFFF;
}

//Despues de la inicialización todos los LEDs deben quedar apagados
void test_Leds0ffAfterCreate(void ){
    uint16_t ledsVirtuales=0xFFFF; 
    LedsInit(&ledsVirtuales, RegistrarError);
    TEST_ASSERT_EQUAL_HEX16(0x0000,ledsVirtuales);
}

//Se puede prender un LED individual
void test_TurnOnOneLed(void){
    LedTurnOn(5);//solo maneja un puerto, indico el número de led (prendo)
    TEST_ASSERT_EQUAL_HEX16(1<<4,ledsVirtuales);
}

//Se puede apagar un LED individual
void test_TurnOffOneLed(void){
    LedTurnOn(5);//solo maneja un puerto, indico el numero de led (prendo)
    LedTurnOff(5);//solo maneja un puerto, indico el numero de led (apago)
    TEST_ASSERT_EQUAL_HEX16(0x0000,ledsVirtuales);
}

//Se pueden prender y apagar múltiples LED’s
void test_TurnOnAndOffManyLeds(void){
    LedTurnOn(5);
    LedTurnOn(11);
    LedTurnOff(3);
    LedTurnOff(11);
    TEST_ASSERT_EQUAL_HEX16(1<<4,ledsVirtuales);
}

//Revisar parámetros fuera de los limites
void test_InvalidUpperLimitTurnOnLed (void){
    LedTurnOn (17);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_informada);
   }

//Se pueden prender todos los LEDs de una vez
void test_TurnAllOn(void){
   LedsAllOn();
   TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);   
}

//Se pueden apagar todos los LEDs de una vez
void test_TurnAllOff(void){
   LedsAllOn();
   LedsAllOff();
   TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

//Se puede consultar el estado de un LED apagado
void test_LedStateOff(void){
   TEST_ASSERT_EQUAL(0, LedState(4));
}

//Se puede consultar el estado de un LED prendido
void test_LedStateOn(void){
   LedTurnOn(3);
   TEST_ASSERT_EQUAL(1, LedState(3));
}