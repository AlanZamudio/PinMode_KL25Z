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
unsigned int PWM_bfnAngleAdjustment (int bNewAngle);
void delayMs(int n);

void PWM_vfnDriverInit (void)
{
    SIM->SCGC5 |= 0x800; 		//Habilitar reloj del puerto C
    SIM->SCGC6 |= 0x1000000; 	//Habilitar reloj PTM0
    PORTC->PCR[2] = 0x400;	    //Puerto C2 como alternativa 4-salida de PWM
    SIM->SOPT2 |= 0x1000000;    //Seleccion de reloj:MCGFLLCLK de 21 MHz

    TPM0->CONTROLS[1].CnSC = 0x28; 		//PWM edge aligned
    TPM0->MOD = 26249; 					//Modulo register calculado para CLK=21MHz, factor de div 16 y T=20ms
    TPM0->CONTROLS[1].CnV = 26249/2;  	//Channel value en duty cycle de 50%
    TPM0->SC = 0xC;            			//Pre-scaler factor div /16
}

unsigned int DPY_bInitialPosition (void){
	  TPM0->CONTROLS[1].CnV = 500; //servo en 0°
	  delayMs(500);
}

unsigned int PWM_bfnAngleAdjustment (int bNewAngle){
	int result;

		   if(bNewAngle == 180){
			   result = ADC_bfnReadADC(0); //PTE20
			   TPM0->CONTROLS[1].CnV =  500 +  result*5/8;   /* duty cicle 10%, señal en alto de 2ms, permite girar hasta 180°*/

		   } else if(bNewAngle == 90){
			   result = ADC_bfnReadADC(3); //PTE22
			   TPM0->CONTROLS[1].CnV = 500 + result/4;  /* duty cicle 5%, señal en alto de 1ms, permite girar hasta 90°*/

		   }

}

void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for(j = 0 ; j < 7000; j++)
	{ }
}

