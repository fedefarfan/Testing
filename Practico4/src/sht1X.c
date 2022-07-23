#include "sht1X.h"
#include "communication.h"
#include<stdio.h>
#include <stdbool.h>

bool AckSht1x_getAck_Temp(void){

	bool ACK = communication_ConfigurationTempMeasurement(0x03);
	return ACK;
}

bool AckSht1x_getAck_Hum(void){

	bool ACK = communication_ConfigurationHumMeasurement(0x05);
	return ACK;
}

bool AckSht1x_getAck_Error(){

	bool ACK = communication_ConfigurationErrorMeasurement(0x08);
	return ACK;
}

float ReadSht1x_Humidity(void){

	uint16_t Value = communication_ReadHumSht1x(0x07);
	float rh_lin=-0.0000015955*(float)Value*(float)Value + 0.0367*(float)Value - 4.3468;
	printf("test_True_linear_hum_ESTIMATE: HUM_lineal(%u)= %.1f",Value,rh_lin);
	return rh_lin;
}

float ReadSht1x_Temperature(void){

	uint16_t Value = communication_ReadTempSht1x(0x08);
	float temp_lin=-40.1f + 0.01f*(float)Value;
	printf("test_linear_Temperature_ESTIMATE: TEMP_lineal(%u)= %.1f",Value,temp_lin);
	return temp_lin;
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