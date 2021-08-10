/*
 * PWM.c
 *
 *  Created on: 9 jul. 2021
 *      Author: Alan Ramon Zamudio Arroyo
 */

#include "MKL25Z4.h"
#include "adc.h"

void PWM_vfnDriverInit(void);
unsigned int DPY_bInitialPosition (void);
unsigned int PWM_bfnAngleAdjustment (unsigned int bNewAngle);
void RetardoMs(int n);

void PWM_vfnDriverInit (void)
{
    SIM->SCGC5 |= 0x800; 		//Habilitar reloj del puerto C
    SIM->SCGC6 |= 0x1000000; 	//Habilitar reloj PTM0
    PORTC->PCR[2] = 0x400;	    //Puerto C2 como alternativa 4-salida de PWM
    SIM->SOPT2 |= 0x1000000;    //Seleccion de reloj:MCGFLLCLK de 48 MHz

    TPM0->CONTROLS[1].CnSC = 0x28; 		//PWM edge aligned
    TPM0->MOD = 26249; 					//Modulo register calculado para CLK=48MHz, factor de div 16 y T=20ms
    TPM0->CONTROLS[1].CnV = 26249/2;  	//Channel value en duty cycle de 50%
    TPM0->SC = 0xC;            			//Pre-scaler factor div /16
}

unsigned int DPY_bInitialPosition (void){
	  TPM0->CONTROLS[1].CnV = 1100; //6900;//1100 servo en 0°
	  RetardoMs(5);
}

unsigned int PWM_bfnAngleAdjustment (unsigned int bNewAngle){


	TPM0->CONTROLS[1].CnV =  1100 +  bNewAngle*116;   /* duty cicle 10%, señal en alto de 2ms, permite girar hasta 180°*/
	RetardoMs(5);
}

void RetardoMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for(j = 0 ; j < 7000; j++)
	{ }
}

