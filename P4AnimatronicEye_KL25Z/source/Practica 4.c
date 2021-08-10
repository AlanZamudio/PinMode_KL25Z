/*Practica 4 - Diseño de sistemas con microprocesadores - Ing Mecatronica
 Nombre								Registro
  Alan Ramon Zamudio Arroyo			4510558
  Luis Guillermo Castro Gaxiola
*/

#include "MKL25Z4.h"
#include "adc.h"
#include "PWM.h"

int main(void) {
	int sensor1;
	int sensor2;

	ADC_vfnDriverInit (); //Inicializar ADC0
	PWM_vfnDriverInit(); //Inicializar PWM

	DPY_bInitialPosition(); //Servo en posicion 0°

	while(1){
		sensor1 = ADC_bfnReadADC(0); //Leer y guardar valor de sensor 1
	  	sensor2 = ADC_bfnReadADC(3); //Leer y guardar valor de sensor 2

		if(sensor1 > sensor2){
			PWM_bfnAngleAdjustment(180); //Giro Max de 180° dependiente de sensor 1
		} else if(sensor2 > sensor1){
			PWM_bfnAngleAdjustment(90); //Giro Max de 90° dependiente de sensor 2
		}
	}
}
