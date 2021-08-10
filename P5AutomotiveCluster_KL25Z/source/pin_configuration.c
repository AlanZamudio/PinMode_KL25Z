
#include <stdio.h>
#include "Arduino.h"
#include "MKL25Z4.h"




void Pin_Mode(int port,int pin,int estate)
{
	 SIM->SCGC5 |=SCGC5_PORT(port);
	 PORT(port)->PCR[pin]=MUX_ALT(Alternative1);
	 if(estate==1){GPIO(port)->PDDR|=0x01<<pin;}
	 else {GPIO(port)->PDDR &= ~(0x01<<pin);}
}





void Digital_Write(int port,int pin,int on)
{
    if(on==1){GPIO(port)->PDOR|=0x01<<pin;}
    else{GPIO(port)->PDOR &=~(0x01<<pin);}
}



int Read_Input(int port, int pin)
{
   return ((GPIO(port)->PDIR)>>pin)&0x1;
}




void delay(void) {
    entero i = 0;
    for (i = 0; i < COUNT; i++)
    {
        __NOP();

    }
}

