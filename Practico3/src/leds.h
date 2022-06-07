#ifndef _LEDS_H 
#define _LEDS_H

#include <stdint.h>
#include "errores.h"
#include <stdbool.h>

uint16_t LedToMask (uint8_t led);


/**
 * @brief Configura biblioteca y apaga todos los leds
 * 
 * @param direccion Dirección del puerto GPIO que controla los leds
 */
void LedsInit(uint16_t *direccion, registro_errores_t FuncionRegistro);


/**
 * @brief Prende un led.
 * 
 * @param led Numero de led a prender (1 al 16).
 */
void LedTurnOn (uint8_t led); 


/**
 * @brief Apaga un led.
 * 
 * @param led Numero de led  pagar (1 al 16).
 */
void LedTurnOff (uint8_t led);


/**
 * @brief Funcion para prender todos los leds
 * 
 */
void LedsAllOn(void);

/**
 * @brief Funcion para apagar todos los leds
 * 
 */
void LedsAllOff(void);

/**
 * @brief Funcion para leer el estado de un led
 * 
 * @param led Numero de led para leer estado (1 al 16)
 * @return true 
 * @return false 
 */
bool LedState(uint8_t led);

#endif