#include "unity.h"
#include "sht1X.h"
#include "mock_communication.h"

/*************************************************************************************************
	 *  @brief Ensayo donde se simula el envio del parametro para la funcion encargada de enviar 
     *el tren de pulsos al sensor para configurar la medida de temperatura
     *  @details
     *      Se envia el valor 0x03 (Configuration_Value) para indicar la medida de temperatura (ver hoja de dato)
     *                                    ________  
     *    _______________________________/       /__ 
     *      0    0    0    0    0    0    1   1      ---> 3   
     *      __   __   __   __   __   __   __   __   __
     *   __/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__
     *      1    2    3    4    5   6    7    8    ACK
     *    <------------- 8 BITS --------------->
     *    Se espera un 0 en la lectura del ACK (variable actual_ACK)
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_Configuration_Temperature_Measurement(void){
    uint8_t Configuration_Value_T=0x03;
    bool expected_ACK=0x00;
    //Se indica que funcion se llamara: definimos el parametro que enviamos y el que se espera
	communication_ConfigurationTempMeasurement_ExpectAndReturn(Configuration_Value_T, expected_ACK);

    //simulamos la recepcion del valor ACK enviado por el sht1x
    bool actual_ACK=AckSht1x_getAck_Temp();
    TEST_ASSERT_EQUAL_HEX8(actual_ACK,expected_ACK);
}

/*************************************************************************************************
	 *  @brief Ensayo donde se simula el envio del parametro para la funcion encargada de enviar 
     *el tren de pulsos al sensor para configurar la medida de humedad
     *
     *  @details
     *      Se envia el valor 0x05 (Configuration_Value) para indicar la medida de humedad (ver hoja de dato).
     *                                ___      ___  
     *    ___________________________/  /_____/  /______ 
     *      0    0    0    0    0    1    0   1      ---> 5   
     *      __   __   __   __   __   __   __   __   __
     *   __/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__
     *      1    2    3    4    5   6    7    8    ACK
     *    <--------------  8 BITS ------------->
     *    Se espera un 0 en la lectura del ACK (variable actual_ACK)
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_Configuration_Humidity_Measurement(void){
    uint8_t Configuration_Value_H=0x05;
    bool expected_ACK=0x00;
    //Se indica que funcion se llamara: definimos el parametro que enviamos y el que se espera
    communication_ConfigurationHumMeasurement_ExpectAndReturn(Configuration_Value_H, expected_ACK);

    //simulamos la recepcion del valor ACK enviado por el sht1x
    bool actual_ACK=AckSht1x_getAck_Hum();
    TEST_ASSERT_EQUAL_HEX8(actual_ACK,expected_ACK);
}

/*************************************************************************************************
	 *  @brief Ensayo donde se simula el envio de un parametro erroneo para la funcion encargada  
     *de enviar el tren de pulsos al sensor para configurar una medida
     *
     *  @details
     *      Se envia el valor 0x08 (Configuration_Value) para indicar una configuracion erronea (ver hoja de dato).
     *                           ___                ___
     *    ______________________/  /_______________/  /__ 
     *      0    0    0    0    1    0    0    0      ---> 3   
     *      __   __   __   __   __   __   __   __   __
     *   __/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__
     *      1    2    3    4    5   6    7    8    ACK
     *    <-----------  8 BITS (CRC)  ---------->
     *    Se espera un 1 en la lectura del ACK (variable actual_ACK)
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_Error_Configuration_Measurement(void){
    uint8_t Configuration_Value=0x08;
    bool expected_ACK=0x01;
    //Se indica que funcion se llamara: definimos el parametro que enviamos y el que se espera
    communication_ConfigurationErrorMeasurement_ExpectAndReturn(Configuration_Value, expected_ACK);

    //simulamos la recepcion del valor ACK enviado por el sht1x
    bool actual_ACK=AckSht1x_getAck_Error();
    TEST_ASSERT_EQUAL_HEX8(actual_ACK,expected_ACK);
}

/*************************************************************************************************
	 *  @brief Ensayo donde se simula el envio del parametro que indica lectura de temperatura del sensor
     *
     *  @details
     *      Se envia el parametro (0x08) para indicar la lectura de temperatura.
     *      Se calcula el valor de temperatura de acuerdo a la expresion que indica el fabricante
     *      (ver hoja de dato)
     *      Se espera que el valor de temperatura esperdo sea de 43.1 °C
     *       
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_linear_Temperature_ESTIMATE(void ){
    uint8_t number_to_read= 0x08;//indica la lectura de temperatura
    uint16_t humObtainedADC= 0x2080;
	float expectedTemperature=43.1;
	float tolerance = 0.1f;//Tolerancia para comparar valor esperado con el valor actual

    //Se indica que funcion se llamara: definimos el parametro que enviamos y el que se espera
	communication_ReadTempSht1x_ExpectAndReturn(number_to_read, humObtainedADC);

	//simulamos la recepcion del valor Temperatura que envio el sht1x
	float actualTemperature = ReadSht1x_Temperature();
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expectedTemperature, actualTemperature);
}

/*************************************************************************************************
	 *  @brief Ensayo donde se simula el envio del parametro que indica lectura de humedad del sensor 
     *
     *  @details
     *      Se envia el parametro (0x07) para indicar la lectura de humedad.
     *      Se calcula elvalor de humedad de acuerdo a la expresion que indica el fabricante
     *      (ver hoja de dato)
     *      Se espera que el valor de temperatura esperdo sea de 57.5 %
     *       
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_linear_Humidity_ESTIMATE(void ){
    uint8_t number_to_read= 0x07;//indica la lectura de humedad
    uint16_t humObtainedADC= 0x728;
	float expectedHumidity=57.5;
	float tolerance = 0.1f;//Tolerancia para comparar valor esperado con el valor actual

	//Se indica que funcion se llamara: definimos el parametro que enviamos y el que se espera
	communication_ReadHumSht1x_ExpectAndReturn(number_to_read, humObtainedADC);

	//simulamos la recepcion del valor Humedad que envio el sht1x
	float actualHunidity = ReadSht1x_Humidity();
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expectedHumidity, actualHunidity);
}


/*************************************************************************************************
	 *  @brief Ensayo del calculo de la humedad lineal de forma correcta 
     *      (INDEPENDIENTE DE LA TEMPERATURA)
     *
     *  @details
     *      Se calcula elvalor de humedad de acuerdo a la expresion que indica el fabricante
     *      (ver hoja de dato)
     *      Si su valor se encuentra entre 0.1 y 100, es correcto 
	 *      Se espera que el valor de result=sht1X_linear_hum(value_h) sea 0, ya que el calculo
     *      de humedad indica 51.4
     *      value_h representa elvalor del ADC del sensor
     *       
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_linear_hum_ESTIMATE(void ){
    uint16_t value_h=1635;
    bool result;
    result=sht1X_linear_hum(value_h);
    TEST_ASSERT_EQUAL_HEX8(0x0000,result);
}

/*************************************************************************************************
	 *  @brief Ensayo del calculo de la humedad lineal para un valor incorrecto  
     *      (INDEPENDIENTE DE LA TEMPERATURA)
     *
     *  @details
     *      Se calcula elvalor de humedad de acuerdo a la expresion que indica el fabricante
     *      (ver hoja de dato)
     *      Si su valor se encuentra entre 0.1 y 100, es correcto 
	 *      Se espera que el valor de result=sht1X_linear_hum(value_h) sea 1, ya que el calculo
     *      de humedad indica 192.8
     *      value_h representa el valor del ADC del sensor
     *       
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_ERROR_linear_hum_ESTIMATE(void ){
    uint16_t value_h=8546;
    bool result;
    result=sht1X_linear_hum(value_h);
    TEST_ASSERT_EQUAL_HEX8(0x0001,result);
}

/*************************************************************************************************
	 *  @brief Ensayo del calculo de la humedad real para un valor correcto  
     *      (DEPENDIENTE DE LA TEMPERATURA)
     *
     *  @details
     *      Se calcula elvalor de humedad real de acuerdo a la expresion que indica el fabricante
     *      (ver hoja de dato)
     *      Si su valor se encuentra entre 0.1 y 100, es correcto 
	 *      Se espera que el valor de result=sht1X_linear_hum(value_h) sea 0, ya que el calculo
     *      de humedad indica 57.5
     *      value_h representa el valor del ADC del sensor
     *       
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_True_linear_hum_ESTIMATE(void ){
    uint16_t value_h=1832;
    float temp_a=40.2;
    bool result;
    result=sht1X_true_linear_hum(value_h,temp_a);
    TEST_ASSERT_EQUAL_HEX8(0x0000,result);
}