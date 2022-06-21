#include "sht1X.h"
#include<stdio.h>
#include <stdbool.h>

static uint8_t data_config_init=195;//
static uint8_t hum_config_measure=5;
static uint8_t temp_config_measure=3;
static bool LOW = 0;
static bool HIGH = 1;

void Gpio_DATA_In_Config(void){
	bool Gpio_DATA=0;

}

void Gpio_DATA_Out_Config(void){
	bool Gpio_DATA=1;

}

void Gpio_SCK_Out_Config(void){
	bool Gpio_SCK=1;

}

uint8_t DATA_send_bit_to_sensor(bool Num,uint8_t weight){
	return Num*weight;
}

void SCK_send_bit_to_sensor(bool Num){
	bool SCK_send=Num;

}

bool sht1X_Init(uint8_t data_in,uint8_t sck_in){
	uint8_t i,number_config=0;
	bool error=0;
	Gpio_DATA_Out_Config();
	Gpio_SCK_Out_Config();

	/*Dependiendo de los valores de data_in y sck_in, se envia 
	los 8  bits de forma serial por el puerto DATA y SCK 
	valor correcto para SCK: 01100110
	valor correcto para DATA: 11000011 */

	for (i=128;i>0;i/=2){ 

	/*Envia 1 y 0 por elpuerto DATA */
		if (i & data_in)  number_config=number_config + DATA_send_bit_to_sensor(HIGH,i);//ENVIA 1
		else  number_config=number_config + DATA_send_bit_to_sensor(LOW,i);//ENVIA 0
		
		Queue_Time(1);
	
	/*Envia 1 y 0 por elpuerto SCK */
		if (i & sck_in)  SCK_send_bit_to_sensor(HIGH);
		else  SCK_send_bit_to_sensor(LOW);

	}
	//printf("numero init config %u",number_config);

	/*Analizamos si el dato enviado es el correcto */
	error=DATA_init(number_config);
return error;
}

bool sht1X_Measure_Configure_Comand(uint8_t value){
	uint8_t i,number_config=0;
	bool error=0;


	/*Dependiendo del valor value, se envia 
	los 8  bits de forma serial por el puerto DATA 
	valor correcto para Temperatura: 00000011
	valor correcto para Humedad: 00000101 */

	for (i=128;i>0;i/=2){

		if (i & value)  number_config=number_config + DATA_send_bit_to_sensor(HIGH,i);//ENVIA 1
		else  number_config=number_config + DATA_send_bit_to_sensor(LOW,i);//ENVIA 0
		
		SCK_send_bit_to_sensor(HIGH);
		Queue_Time(1);
		SCK_send_bit_to_sensor(LOW);
	}
	//printf("numero %u",number_config);

	SCK_send_bit_to_sensor(HIGH);

	/*Cambia el puerto DATA como entrada */
	Gpio_DATA_In_Config();
	
	/*Analizamos si el dato enviado es el correcto por medio del ACK*/
	error=DATA_in_acknowledgment(number_config);

	SCK_send_bit_to_sensor(LOW);
	
return error;
}

bool DATA_in_acknowledgment(uint8_t number_config_sensor){
	if(number_config_sensor==hum_config_measure)
	return 0;
	else if(number_config_sensor==temp_config_measure)
	return 0;
	else
return 1;
}

bool DATA_init(uint8_t number_config_sensor){
if(number_config_sensor==data_config_init)
return 0;
else
return 1;
	
}

bool sht1X_linear_hum(uint16_t p_humedad){
	/* Constantes que indica elfabricante  */
	const float C1=-4.3468;
	const float C2=0.0367;
	const float C3=-0.0000015955;

	bool errorh=0;

	float rh;
	float rh_lin;

	rh =(float) p_humedad;

	/* Expresion que indica el fabricante para el
	calculo de la humedad lineal */
	rh_lin=C3*rh*rh + C2*rh + C1;


	printf("humedad lineal(%u)=%.1f",p_humedad,rh_lin);

	/* Control del valor de humedad*/
	if(rh_lin>100 || rh_lin<0.1)errorh=1;
	else errorh=0;
	
return errorh;
}

bool sht1X_true_linear_hum(uint16_t p_humedad,float t_C){
	/* Constantes que indica elfabricante  */
	const float C1=-4.3468;
	const float C2=0.0367;
	const float C3=-0.0000015955;
	const uint32_t T1=+0.01;
	const uint32_t T2=+0.00008;
	bool errorh=0;

	float rh;
	float rh_lin;
	float rh_true;
	rh =(float) p_humedad;

	/* Expresion que indica el fabricante para el
	calculo de la humedad lineal */
	rh_lin=C3*rh*rh + C2*rh + C1;

	/* Expresion que indica el fabricante para el
	calculo de la humedad real */
	rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;

	printf("humedad real(%u)= %.1f",p_humedad,rh_true);

	/* Control del valor de humedad*/
	if(rh_true>100 || rh_true<0.1)errorh=1;
	else errorh=0;
	
return errorh;
}


void Queue_Time(uint32_t Time_e){
uint32_t Micro_queue_time=Time_e;

}