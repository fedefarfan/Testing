#include "src/errores.h"
#include "src/leds.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


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





void test_Leds0ffAfterCreate(void ){

    uint16_t ledsVirtuales=0xFFFF;

    LedsInit(&ledsVirtuales, RegistrarError);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOnOneLed(void){

    LedTurnOn(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1<<4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOffOneLed(void){

    LedTurnOn(5);

    LedTurnOff(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOnAndOffManyLeds(void){

    LedTurnOn(5);

    LedTurnOn(11);

    LedTurnOff(3);

    LedTurnOff(11);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1<<4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_HEX16);

}





void test_InvalidUpperLimitTurnOnLed (void){

    LedTurnOn (17);

    UnityAssertEqualNumber((UNITY_INT)((ALERTA)), (UNITY_INT)((gravedad_informada)), (

   ((void *)0)

   ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_INT);

   }





void test_TurnAllOn(void){

   LedsAllOn();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnAllOff(void){

   LedsAllOn();

   LedsAllOff();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_HEX16);

}





void test_LedStateOff(void){

   UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((LedState(4))), (

  ((void *)0)

  ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

}





void test_LedStateOn(void){

   LedTurnOn(3);

   UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((LedState(3))), (

  ((void *)0)

  ), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);

}
