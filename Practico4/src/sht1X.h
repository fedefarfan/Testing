#ifndef _SHT1X_H 
#define _SHT1X_H

#include <stdint.h>
#include <stdbool.h>

/*************************************************************************************************
	 *  @brief Funcion que simula el envio del parametro para la lectura del ACK, en la configuracion  
     *para la medida de temperatura
     *  @details
     *  El sensor envia como respuesta a la configuracion de temperatura, un valor de ACK
     *  ACK = 0 indica configuración correcta
     *  ACK = 1 indica configuracion incorrecta
     *  (ver hoja de dato)
     *
	 *  @return     ACK		indica si los valores enviados son correctos o no
***************************************************************************************************/
bool AckSht1x_getAck_Temp(void);

/*************************************************************************************************
	 *  @brief Funcion que simula el envio del parametro para la lectura del ACK, en la configuracion 
     *para la medida de humedad
     *  @details
     *  El sensor envia como respuesta a la configuracion de humedad, un valor de ACK
     *  ACK = 0 indica configuración correcta
     *  ACK = 1 indica configuracion incorrecta
     *  (ver hoja de dato)
     *
	 *  @return     ACK		indica si los valores enviados son correctos o no
***************************************************************************************************/
bool AckSht1x_getAck_Hum(void);

/*************************************************************************************************
	 *  @brief Funcion que simula el envio de un parametro erroneo para la lectura del ACK, en la configuracion
     *para realizar una medida
     *  @details
     *  El sensor envia como respuesta a la configuracion un valor de ACK
     *  ACK = 0 indica configuración correcta
     *  ACK = 1 indica configuracion incorrecta
     *  (ver hoja de dato)
     *
	 *  @return     ACK		indica si los valores enviados son correctos o no
***************************************************************************************************/
bool AckSht1x_getAck_Error();

/*************************************************************************************************
	 *  @brief Funcion para el calculo de la humedad lineal enviada por el sensor
     *
     *  @details
     *   	El fabricante indica la funcion para calcuar la humedad, de forma independiente a la 
     *      temperatura
     *      (ver hoja de dato)
     *
	 *  @return		rh_lin	valor de humedad que se obtiene del sensor
***************************************************************************************************/
float ReadSht1x_Humidity(void);

/*************************************************************************************************
	 *  @brief Funcion para el calculo de la temperatura enviada por el sensor
     *
     *  @details
     *   	El fabricante indica la funcion para calcuar la temperatura
     *      (ver hoja de dato)
     *
	 *  @return		temp_lin	valor de humedad que se obtiene del sensor
***************************************************************************************************/
float ReadSht1x_Temperature(void);

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



#endif