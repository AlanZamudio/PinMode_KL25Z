/*
 * ADC.c
 *
 *  Created on: 24 jun. 2021
 *      Author: Personal
 */

#include "MKL25Z4.h"
#include<stdio.h>
#include "adc.h"

void ADC_vfnDriverInit ( void )
{
	SIM->SCGC6 = 0x8000000; //Activar reloj del ADC

	SIM->SCGC5 = 0x3E00;	//Inicializar reloj de todos los  puertos (	B )

	PORTB->PCR[0] |= PORT_PCR_MUX(0); //Establecer MUX como entrada analogica B0

	ADC0->CFG1 = 0x70; //   11|1|00|00
	//ADIV = clock/8 |ADLSMP = long sample time|MODE = 8 bits|ADICLK = Bus clock

	ADC0->CFG1 |= (ADC_CFG1_ADLPC(0)); //Modo de potencia normal

	ADC0->SC1[0] = ADC_SC1_ADCH(31); //Desactivar todos los canales

}

unsigned short ADC_bfnReadADC (unsigned short bChannel)
{

	ADC0->SC1[0] = bChannel;  //canal 8 para trabajo con puerto PTB0 como entrada de adc
	//se ejecuta conversion

	//while(ADC0->SC2 & ADC_SC2_ADACT_MASK); 		// 1000 0000-conversion en progreso
	//while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));		//100 0000-conversion completada

	return ADC0->R[0]; //La funcion regresa el valor de temperatura en bits

}
