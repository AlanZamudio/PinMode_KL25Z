/**
 * @file    MKL25Z128xxx4_Project_prueba.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "Arduino.h"
#include "LCD1.H"

#define uart UART0
void UART_vfnDriverInit (void);
void Serial_READ(uint8_t *recived);

void transmit(char *DATA);
unsigned char UART_bfnRead (unsigned int *bpRxData);

int main(void) {

  	/* Init board hardware. */
	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    UART_vfnDriverInit ();
    LCD_init();
    PWM_vfnDriverInit();
    ADC_vfnDriverInit();

    DPY_bInitialPosition();

    unsigned int X=0;
    unsigned int Y=0;
    unsigned int Z = 0;
    unsigned int r0=0;
    char buffer[11];


    while(1)
    {

     Serial_READ(&r0);

     //UART_bfnRead(&r0);

     if(r0 != 0){
     X = r0;
     printf("%i\n",r0);
     //transmit(dato);

     if(X != Y){
     Z = r0;
     PWM_bfnAngleAdjustment (Z);
     LCD_command(DISPLAY_CLEAR);
     DPY_bfnWriteMsg("TEMP:");
     enteroACadena(r0,buffer);
     //LCD_data(b);
     DPY_bfnWriteMsg(buffer);
     }
     Y = r0;
    //delayMs(10);
     }

    }
 //   delayMs(500);
    return 0 ;
}


void UART_vfnDriverInit (void)
{
	MCG->C4=0xA0;//48MHz
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SCGC4|=SIM_SCGC4_UART0_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1]|=PORT_PCR_MUX(2);
	PORTA->PCR[2]|=PORT_PCR_MUX(2);
	UART0->BDL=0x38;
	UART0->BDH=0x1;
	UART0->C1=0x0;
	UART0->C2=0xC;
	UART0->C4=0x20;
}

void transmit(char *DATA)
{
	while(*DATA)
	{

		UART0->D=*DATA;
		delayMs(500);
		while(!(UART0->S1&UART_S1_TDRE_MASK));
		DATA++;
	}

}



void Serial_READ(uint8_t *recived)
{
  UART0->C2=0X4;
  //while(!(UART0->S1 & UART0_S1_RDRF_MASK));
  *recived=UART0->D;
  //wait for receive buffer full
}

