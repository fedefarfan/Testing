#ifndef _SHT1X_H 
#define _SHT1X_H

#include <stdint.h>
#include "errores.h"
#include <stdbool.h>

/*************************************************************************************************
	 *  @brief Funcion para configurar el pin GPIO (DATOS) como entrada
     *
     *  @details
     *   	Configura el pin GPIO como entrada para recibir del sensor paramatros de control
     *   	o la medida de temperatura y humedad
     *
	 *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void Gpio_DATA_In_Config(void);

/*************************************************************************************************
	 *  @brief Funcion para configurar el pin GPIO (DATOS) como salida
     *
     *  @details
     *   	Configura el pin GPIO como salida para indicar al sensor que funcion debe ejecutar
     *
	 *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void Gpio_DATA_Out_Config(void);

/*************************************************************************************************
	 *  @brief Funcion para configurar el pin GPIO (SCK) como salida
     *
     *  @details
     *   	Configura el pin GPIO como salida para sincronizar la comunicacion entre el sensor
     *   	y el microcontrolador
     *
	 *  @param		None.
	 *  @return     None.
***************************************************************************************************/
void Gpio_SCK_Out_Config(void);

/*************************************************************************************************
	 *  @brief Funcion para enviar ceros o unos por el pin DATA
     *
     *  @details
     *   	Esta función envia ceros o uno para indicar al sensor que tarea realizar
     *
	 *  @param		Num	El estado del pin DATA, alto o bajo
     *  @param      weight  Se utiliza para determinar el valor que se envia al sensor
     *      En el código final, este parametro no existe, solo tiene relevancia a los efectos
     *      del test
	 *  @return     None.
***************************************************************************************************/
uint8_t DATA_send_bit_to_sensor(bool Num,uint8_t weight);

/*************************************************************************************************
	 *  @brief Funcion para enviar ceros o unos por el pin SCK
     *
     *  @details
     *   	Esta función envia ceros o uno para indicar al sensor cuando interpretar ceros y uno
     *   	en el puerto DATA
     *
	 *  @param		Num	El estado del pin SCK, alto o bajo
	 *  @return     None.
***************************************************************************************************/
void SCK_send_bit_to_sensor(bool Num);

/*************************************************************************************************
	 *  @brief Funcion para inicializar el sensor sht1X
     *
     *  @details
     *   	En la función se pide configurar el puerto DATA y SCK como salida, para enviar las 
     *   	tramas de inicio del sht1X
     *      La siguiente configuracion inicializa el sensor  (ver hoja de dato)
     *   	          __     __
     *   CLOCK     __/  /___/  /___SCK
     *            ____       ____
     *   DATOS       /______/      DATA
     *
	 *  @param		data_in indica la secunencia de unos y ceros que se envia por el puerto DATA
     *  @param		sck_in  indica la secuencia de unos y ceros que se envia por el puerto SCK
	 *  @return     None.
***************************************************************************************************/
bool sht1X_Init(uint8_t data_in,uint8_t sck_in);

/*************************************************************************************************
	 *  @brief Funcion que envia un tren de pulso al sht1X para indicar que magnitud debe medir 
     *  el sensor
	 *
     *  @details
     *   	La funcion envia un tren de pulso para medir tempeartura o humedad
     *      Se envia el 00000011 para medir temperatura y el 00000101 para medir humedad
     *      (ver hoja de dato)
     *
	 *  @param		value1		valor que indica si se va a medir temperatura o humedad
	 *  @return     error		indica si los valores enviados son correctos o no
***************************************************************************************************/
bool sht1X_Measure_Configure_Comand(uint8_t value);

/*************************************************************************************************
	 *  @brief Funcion que simula la lectura del puerto DATA
     *
     *  @details
     *  El sensor envia en las diferentes configuraciones un valor de ACK
     *  ACK = 1 indica configuración correcta
     *  ACK = 0 indica configuracion incorrecta
     *  (ver hoja de dato)
     *
	 *  @param		number_config_sensor	valor que se obtiene al enviar los datos de configuracion
	 *  @return     error		(ACK) indica si los valores enviados son correctos o no
***************************************************************************************************/
bool DATA_in_acknowledgment(uint8_t number_config_sensor);

/*************************************************************************************************
	 *  @brief Funcion que controla el tre de pulsos enviados al iniciar el sensor
     *
     *  @details
     *  El fabricante indica el siguiente tren de pulso para inicializar elsensor (ver hoja de dato):
     *       ____    ____  
     *    __/   /___/   /__ SCK
     *     0 1 1 0 0 1 1 0  ---> 102 
     *    _____        ____
     *        /_______/      DATA           
     *     1 1 0 0 0 0 1 1  ---> 195
     *    <--- 8 BITS --->
     *
	 *  @param		number_config_sensor	valor relacionado con eltren de pulso que se envia 
     *  por DATA (195 el correcto)
	 *  @return     error		indica si los valores enviados son correctos o no
***************************************************************************************************/
bool DATA_init(uint8_t number_config_sensor);


/*************************************************************************************************
	 *  @brief Funcion para el calculo de la humedad lineal
     *
     *  @details
     *   	El fabricante indica la funcion para calcuar la humedad, de forma independiente a la 
     *      temperatura
     *      (ver hoja de dato)
     *
	 *  @param		p_humedad	valor de humedad que se obtiene del ADC del sensor
	 *  @return     error		0 o 1, indica si el calculo de la humedad es correcto (0.1 al 100%)
***************************************************************************************************/
bool sht1X_linear_hum(uint16_t p_humedad);

/*************************************************************************************************
	 *  @brief Funcion para el calculo de la humedad, corregida por la temperatura
     *
     *  @details
     *   	El fabricante indica la funcion para calcuar la humedad dependiendo de la   
     *      temperatura ambiente
     *      (ver hoja de dato)
     *
	 *  @param		p_humedad	valor de humedad que se obtiene del ADC del sensor
	 *  			t_C         temperatura	ambiente medida por el sensor
	 *  @return     error		0 o 1, indica si el calculo de la humedad es correcto (0.1 al 100%)
***************************************************************************************************/
bool sht1X_true_linear_hum(uint16_t p_humedad,float t_C);

/*************************************************************************************************
	 *  @brief Funcion que implementa un delay simple de 1 milisegundo
     *
     *  @details
     *   	Esta funcion es especifica para el hardware utilizado.
     *
	 *  @param		millisecs	Los milisegundos a efectuar el delay.
	 *  @return     None.
	 *  @see		delay (implementacion de sAPI).
***************************************************************************************************/
void Queue_Time(uint32_t Time_e);

#endif