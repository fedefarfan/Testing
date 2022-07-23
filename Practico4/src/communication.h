#ifndef communication_H
#define communication_H

#include <stdint.h>

/*************************************************************************************************
	 *  @brief Funcion que simula la lectura del ACK enviado por el sensor para configuracion de 
     *medida de temperatura
     *  @details
     *  El sensor envia como respuesta a la configuracion de temperatura, un valor de ACK
     *  ACK = 0 indica configuración correcta
     *  ACK = 1 indica configuracion incorrecta
     *  (ver hoja de dato)
     *
	 *  @return     ACK		indica si los valores enviados son correctos o no
***************************************************************************************************/
uint8_t communication_ConfigurationTempMeasurement(uint8_t Configuration_Value);

/*************************************************************************************************
	 *  @brief Funcion que simula la lectura del ACK enviado por el sensor para configuracion de 
     *medida de humedad
     *  @details
     *  El sensor envia como respuesta a la configuracion de temperatura, un valor de ACK
     *  ACK = 0 indica configuración correcta
     *  ACK = 1 indica configuracion incorrecta
     *  (ver hoja de dato)
     *
	 *  @return     ACK		indica si los valores enviados son correctos o no
***************************************************************************************************/
uint8_t communication_ConfigurationHumMeasurement(uint8_t Configuration_Value);

/*************************************************************************************************
	 *  @brief Funcion que simula la lectura del ACK enviado por el sensor para una configuracion 
     *erronea del sensor
     *  @details
     *  El sensor envia como respuesta a la configuracion de temperatura, un valor de ACK
     *  ACK = 0 indica configuración correcta
     *  ACK = 1 indica configuracion incorrecta
     *  (ver hoja de dato)
     *
	 *  @return     ACK		indica si los valores enviados son correctos o no
***************************************************************************************************/
uint8_t communication_ConfigurationErrorMeasurement(uint8_t Configuration_Value);

/*************************************************************************************************
	 *  @brief Funcion que simula la lectura de humedad que entrega el ADC del sensor 
     *
     *  @details
     *      En la lectura se obtiene un uint16_t
     *
	 *  @return     rh_lin	valor de humedad 
***************************************************************************************************/
uint16_t communication_ReadHumSht1x(uint8_t Configuration_Value);

/*************************************************************************************************
	 *  @brief Funcion que simula la lectura de temperatura que entrega el ADC del sensor 
     *
     *  @details
     *      En la lectura se obtiene un uint16_t
     *
	 *  @return     rh_lin	valor de temperatura
***************************************************************************************************/
uint16_t communication_ReadTempSht1x(uint8_t Configuration_Value);

#endif // communication_H
