#ifndef ARDUINO_H_
#define ARDUINO_H_
typedef int entero;
typedef unsigned char uint_8;
typedef unsigned int uint_16;
#define offset_p 0x1000
#define offset_g 0x40
#define  SCGC5_PORT(x) (uint_16)(0x1<<(9+x))
#define  MUX_ALT(x)    (uint_16)(x<<8)
#define  Output ((entero)1u)
#define  Intput ((entero)0u)
#define  PORT(x) ((PORT_Type *)(PORTA_BASE+x*offset_p))
#define  GPIO(x)  ((GPIO_Type *)(GPIOA_BASE+x*offset_g))
//__________|Puertos|__________//
enum ports{A,B,C,D,E};
enum boolean{ON=((entero)1u),OFF=((entero)0u)};
enum mux{analog,Alternative1,Alternative2,Alternative3,Alternative4,Alternative5,Alternative6,Alternative7};
enum E_S{OUTPUT=1,INPUT=0};
extern void Pin_Mode(int portA,int pin,int confi);
extern void Digital_Write(int portA,int pin,int on);
extern int Read_Input(int port, int pin);
extern void delay(void);
#define COUNT 1000000U//delay


#endif /* ARDUINO_H_ */
