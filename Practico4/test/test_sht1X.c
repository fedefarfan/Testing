#include "unity.h"
#include "sht1X.h"
#include "errores.h"

/*************************************************************************************************
	 *  @brief Ensayo donde inicializamos el sensor sht1X de forma correcta
     *
     *  @details
     *      Se envia el tren de pulso que indica el fabricante para inicializar el sensor
     *      (ver hoja de dato)
     *       ____    ____  
     *    __/   /___/   /__ SCK
     *     0 1 1 0 0 1 1 0  ---> 102 
     *    _____        ____
     *        /_______/     DATA            
     *     1 1 0 0 0 0 1 1  ---> 195
     *    <--- 8 BITS --->
     *      Se espera un 0 en result=sht1X_Init(value_data,value_sck);
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_Sht1X_Configure_Init(void ){
    uint8_t value_data=195;
    uint8_t value_sck=102;
    bool result;
    result=sht1X_Init(value_data,value_sck);
    TEST_ASSERT_EQUAL_HEX8(0x0000,result);
}

/*************************************************************************************************
	 *  @brief Ensayo donde inicializamos el sensor sht1X de forma incorrecta
     *
     *  @details
     *      Se envia el tren de pulso diferente al que indica el fabricante
     *      (ver hoja de dato)
     *       ____    ____  
     *    __/   /___/   /____ SCK
     *     0 1 1 0 0 1 1 0  ---> 102   
     *       ____     __
     *    __/   /____/ /___    DATA           
     *     0 1 1 0 0 1 0 0  ---> 100
     *    <--- 8 BITS --->
     *      Se espera un 1 en result=sht1X_Init(value_data,value_sck);
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_ERROR_Sht1X_Configure_Init(void ){
    uint8_t value_data=100;
    uint8_t value_sck=102;
    bool result;
    result=sht1X_Init(value_data,value_sck);
    TEST_ASSERT_EQUAL_HEX8(0x0001,result);
}

/*************************************************************************************************
	 *  @brief Ensayo donde se envia al sensor los pulsos adecuados para medir temperatura
     *
     *  @details
     *      Se envia el tren de pulso por medio de la variable value para indicar la medida de 
     *      temperatura (3) (ver hoja de dato)
     *                                    ________  
     *    _______________________________/       /__ 
     *      0    0    0    0    0    0    1   1      ---> 3   
     *      __   __   __   __   __   __   __   __   __
     *   __/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__
     *      1    2    3    4    5   6    7    8    ACK
     *    <------------- 8 BITS --------------->
     *    Se espera un 0 en result=sht1X_Init(value_data,value_sck);
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_TEMP_Configure_Measure(void ){
    uint8_t value=3;
    bool result;
    result=sht1X_Measure_Configure_Comand(value);
    TEST_ASSERT_EQUAL_HEX8(0x0000,result);
}



/*************************************************************************************************
	 *  @brief Ensayo donde se envia al sensor los pulsos adecuados para medir humedad
     *
     *  @details
     *      Se envia el tren de pulso por medio de la variable value para indicar la medida de 
     *      humedad (5) (ver hoja de dato)
     *                                ___      ___  
     *    ___________________________/  /_____/  /______ 
     *      0    0    0    0    0    1    0   1      ---> 3   
     *      __   __   __   __   __   __   __   __   __
     *   __/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__
     *      1    2    3    4    5   6    7    8    ACK
     *    <--------------  8 BITS ------------->
     *    Se espera un 0 en result=sht1X_Init(value_data,value_sck);
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_HUM_Configure_Measure(void ){
    uint8_t value=5;
    bool result;
    result=sht1X_Measure_Configure_Comand(value);
    TEST_ASSERT_EQUAL_HEX8(0x0000,result);
}

/*************************************************************************************************
	 *  @brief Ensayo donde se envia al sensor los pulsos incorrectos para medir temperatura 
     *      o humedad
     *
     *  @details
     *      Se envia el tren de pulso por medio de la variable value, para indicar un error por medio 
     *      del ACK (8) (ver hoja de dato)
     *                           ___                ___
     *    ______________________/  /_______________/  /__ 
     *      0    0    0    0    1    0    0    0      ---> 3   
     *      __   __   __   __   __   __   __   __   __
     *   __/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__
     *      1    2    3    4    5   6    7    8    ACK
     *    <-----------  8 BITS (CRC)  ---------->
     *    Se espera un 1 en result=sht1X_Init(value_data,value_sck);
	 *
     *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void test_ERROR_Configure_Measure(void ){
    uint8_t value=8;
    bool result;
    result=sht1X_Measure_Configure_Comand(value);
    TEST_ASSERT_EQUAL_HEX8(0x0001,result);
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
