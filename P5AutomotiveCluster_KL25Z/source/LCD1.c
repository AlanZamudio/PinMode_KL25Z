/*
 * LCD1.c
 *
 *  Created on: 16 jul. 2021
 *      Author: josel
 */

#include"Arduino.h"
#include"MKL25Z4.h"
#include"LCD1.h"

void LCD_init(void) /* esta function inicializa el LCD*/
{ int i=0;
  SIM->SCGC5 |=SCGC5_PORT(D)|SCGC5_PORT(A); /* habilita el relog del Puerto  D y A */
  while(i<8)
  {PORTD->PCR[i] =MUX_ALT(Alternative1);
   GPIOD->PDDR|=0x1<<i;
    i++;}
  PORTA->PCR[RS] = MUX_ALT(Alternative1); /* usaremos el pin 4 del Puerto A */
  PORTA->PCR[EN] = MUX_ALT(Alternative1); /* usaremos el pin 12 del Puerto A */
  PTA->PDDR  |=(0x1<<RS|0x1<<EN);  /*  hacemos  a  los  pines  2,  4  y  5 salidad */
  //delayMs(100); /* secuencia de inicializacion del LCD */
  LCD_command(FUNCION_SET);
  delayMs(4); /* secuencia de inicializacion del LCD */
  LCD_command(DISPLAY_CLEAR);
  delayMs(4);
  LCD_command(RETURNH);
  delayMs(4);
  LCD_command(DISPLAY_ON_OFF);
  delayMs(4);
}



void delayMs(int n)
{ int i;
  int j;
for(i = 0 ; i < n; i++)
for(j = 0 ; j < 7000; j++) { }
}


void LCD_command(unsigned char command)
{ PTA->PCOR = RS;
  PTA->PSOR = EN;
  PTD->PDOR = command;
  PTA->PCOR = EN;
  UPDATE2();
}


void LCD_data(unsigned char data)
{
  PTA->PSOR = RS;
  PTA->PSOR = EN;
  PTD->PDOR = data;
  PTA->PCOR = EN;
  UPDATE();
  UPDATE();
}


void UPDATE(void)
{
	Digital_Write(A,RS, 1); //RS
	Digital_Write(A,EN, 0); //E
	Digital_Write(A,EN, 1); //E
}

void UPDATE2(void)
{
	Digital_Write(A,RS, 0); //RS
	Digital_Write(A,EN, 1); //E
	Digital_Write(A,EN, 0); //E
}




uint_8 DPY_bfnWriteMsg (uint_8 bpMsgSrc[])
{
	uint_8 *buffer=bpMsgSrc;
	while(*buffer!='\0')
	{  delayMs(1);
	   LCD_data(*buffer);
	   delayMs(1);
	   buffer++;
	}
}

void enteroACadena(unsigned int numero, char *bufer){
    sprintf(bufer, "%u", numero);
}
