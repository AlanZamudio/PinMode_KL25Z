//pinmode


#include "MKL25Z4.h"
#include "pinSetting.h"

void pinMode(char puerto1, int numeropin1, int GPIO1)
{

	int mux_enable = 0x100;
	 SIM->SCGC5 = 0x3E00;

	 if(puerto1 == 'A')
	 {
		 PORTA->PCR[numeropin1] = mux_enable;
		 if(GPIO1 == 1)
		 {

			 GPIOA->PDDR|= 1<<numeropin1;

		 }else if(GPIO1 == 0)
		 	 {
			 	 GPIOA->PDDR &= ~(1<<numeropin1);
		 	 }

	 } else  if(puerto1 == 'B')
	 {


		 PORTB->PCR[numeropin1] = mux_enable;
		 if(GPIO1 == 1)
		 {

			 GPIOB->PDDR|=1<<numeropin1;

		 }else if(GPIO1 == 0)
		 	 {

			 	 GPIOB->PDDR &=~(1<<numeropin1);
		 	 }

	 } else  if(puerto1 == 'C')
	 {


		 PORTC->PCR[numeropin1] = mux_enable;
		 if(GPIO1 == 1)
		 {

			 GPIOC->PDDR |= 1<<numeropin1;

		 }else if(GPIO1 == 0)
		 	 {
			 	 GPIOC->PDDR &= ~(1<<numeropin1);
		 	 }

	 } else  if(puerto1 == 'D')
	 {


		 PORTD->PCR[numeropin1] = mux_enable;
		 if(GPIO1 == 1)
		 {

			 GPIOD->PDDR |= 1<<numeropin1;

		 }else if(GPIO1 == 0)
		 	 {
			 	 GPIOD->PDDR &= ~(1<<numeropin1);
		 	 }

	 } else  if(puerto1 == 'E')
	 {


		 PORTE->PCR[numeropin1] = mux_enable;
		 if(GPIO1 == 1)
		 {

			 GPIOE->PDDR |= 1<<numeropin1;

		 }else if(GPIO1 == 0)
		 	 {
			 	 GPIOE->PDDR &= ~(1<<numeropin1);
		 	 }

	 }


}

void digitalWrite(char puerto2, int numeropin2, int GPIO2)
{
		if(puerto2=='A')
		{
			if(GPIO2==1)
			{
				GPIOA->PDOR|= 1<<numeropin2;
			} else if(GPIO2==0)
			{
		    GPIOA->PDOR&=~(1<<numeropin2);
			}
		    }else if (puerto2=='B')
		    {
		    	if(GPIO2==1){
		    	 GPIOB->PDOR|=1<<numeropin2;
		    	} else if (GPIO2==0)
		    	{
		    		GPIOB->PDOR&=~(1<<numeropin2);
		    	}
		    }else if(puerto2=='C')
		    {
		    	if(GPIO2==1){
		    		 GPIOC->PDOR|=1<<numeropin2;

		    	}else if(GPIO2==0)
		    	{
		    		GPIOC->PDOR&=~(1<<numeropin2);
		    	}
		    }else if (puerto2=='D')
		    {
		    	if(GPIO2==1)
		    	{
		    		GPIOD->PDOR|= 1<<numeropin2;
		    	}else if(GPIO2==0)
		    	{
		    		GPIOD->PDOR&=~(1<<numeropin2);
		    	}
		    }else if(puerto2=='E')
		    {
		    	if(GPIO2==1)
		    	{
		    		GPIOE->PDOR|= 1<<numeropin2;
		    	} else if(GPIO2==0)
		    	{
		    		GPIOE->PDOR&=~(1<<numeropin2);
		    	}
		    }
		}



int digitalRead(char puerto3, int numeropin3)

{
	int regresar=0;

	if(puerto3== 'A')
	{
		regresar= (GPIOA->PDIR& (1<<numeropin3));
	}else if (puerto3=='B')
	{
		regresar=(GPIOB->PDIR&(1<<numeropin3));
	}else if (puerto3=='C')
	{
		regresar=(GPIOC->PDIR&(1<<numeropin3));
	}else if (puerto3=='D')
	{
		regresar=(GPIOD->PDIR&(1<<numeropin3));
	} else if(puerto3=='E')
	{
		regresar=(GPIOE->PDIR&(1<<numeropin3));
	}
	return regresar;
}
