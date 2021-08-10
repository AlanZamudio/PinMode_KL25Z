/*
 * ADC.c
 *
 *  Created on: 24 jun. 2021
 *      Author: Alan Ramon Zamudio Arroyo
 */

#include "MKL25Z4.h"
#include<stdio.h>
#include "adc.h"

void ADC_vfnDriverInit (void);
unsigned short ADC_bfnReadADC (unsigned short bChannel);

void ADC_vfnDriverInit (void){

    SIM->SCGC5 |= 0x2000;       //Habilitar reloj del puerto E
    PORTE->PCR[20] = 0;         //PTE20 como entrada analogica
    PORTE->PCR[22] = 0;			//PTE22 como entrada analogica
    SIM->SCGC6 |= 0x8000000;    //Habilitar reloj ADC0

    //Caracteristicas de  ADC:
    //Clock div by 4, long sample time, single ended 12 bit, bus clock
    ADC0->CFG1 = 0x54;

}

unsigned short ADC_bfnReadADC (unsigned short bChannel){

    ADC0->SC1[0] = bChannel;           //Iniciar conversion en el canal "bChannel"
    while(!(ADC0->SC1[0] & 0x80)) { }  //Esperar a que la convercion se realize

    return ADC0->R[0];        		   //Lectura del resultado de la conversion
}
