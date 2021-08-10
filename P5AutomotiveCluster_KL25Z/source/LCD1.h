/*
 * LCD1.h
 *
 *  Created on: 16 jul. 2021
 *      Author: josel
 */

#ifndef LCD1_H_
#define LCD1_H_
typedef unsigned char uint_8;


//________________|Enums|_________________//
enum ini{FUNCION_SET=0x1C,DISPLAY_ON_OFF=0XD,DISPLAY_CLEAR=0X01,ENTRY_MODE_SET=0X6,RETURNH=0x02,Display_Shift=0x10};
/*
 *FUNCION_SET=0x1C;
 *DISPLAY_ON_OFF=0xB0;
 *RETURNH=0x40;
 *DISPLAY_CLEAR=0x80;
Function Set
RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
0 0 0 0 1 DL N F - -
DL: bit de control de longitud de datos de interfaz
Cuando DL = "Alto", significa modo de bus de 8 bits con MPU.
Cuando DL = "Bajo", significa modo de bus de 4 bits con MPU.
Cuando está en modo bus de 4 bits, necesita transferir datos de 4 bits dos veces.
N: bit de control del número de línea de la pantalla
Cuando N = "Bajo", significa modo de visualización de 1 línea.
Cuando N = "Alto", se establece el modo de visualización de 2 líneas.
F: Muestra el bit de control del tipo de fuente
Cuando F = "Bajo", significa modo de visualización de formato de 5 x 8 puntos
Cuando F = "Alto", modo de visualización de formato de 5 x11 puntos.



Display ON/OFF Control
RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
0 0 0 0 0 0 1 D C B
Pantalla de control / cursor / parpadeo ON / OFF registro de 1 bit.
D: Mostrar bit de control ON / OFF
Cuando D = "Alto", toda la pantalla se enciende.
Cuando D = "Low", la pantalla se apaga, pero los datos de la pantalla permanecen en DDRAM.
C: bit de control de Cursor ON / OFF
Cuando C = "Alto", el cursor está encendido.
Cuando C = "Bajo", el cursor desaparece en la pantalla actual, pero el registro I / D sigue siendo su dato.
B: Bit de control de parpadeo del cursor ON / OFF
Cuando B = "Alto", el cursor parpadea, que alterna entre todos los datos altos y
mostrar el carácter en la posición del cursor.
Cuando B = "Bajo", el parpadeo está apagado.

Clear Display
RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
0 0 0 0 0 0 0 0 0 1
Borre todos los datos de la pantalla escribiendo "20H" (código de espacio) en todas las direcciones DDRAM y configure
Dirección DDRAM a "00H" en AC (contador de direcciones). Devuelve el cursor al estado original.
Es decir, lleve el cursor al borde izquierdo de la primera línea de la pantalla. Hacer modo de entrada
incremento (I / D = "1").


Entry Mode Set
RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
0 0 0 0 0 0 0 1 I / D SH
Establezca la dirección de movimiento del cursor y la pantalla.
I / D: Incremento / decremento de la dirección DDRAM (cursor o parpadeo)
Cuando I / D = "Alto", el cursor / parpadeo se mueve hacia la derecha y la dirección DDRAM aumenta en 1.
Cuando I / D = "Low", el cursor / parpadeo se mueve hacia la izquierda y la dirección DDRAM se reduce en 1.
* CGRAM funciona igual que DDRAM, cuando se lee o escribe en CGRAM.
SH: Desplazamiento de toda la pantalla
Cuando la operación de lectura DDRAM (lectura / escritura CGRAM) o SH = "Low", el desplazamiento de toda la pantalla es
No realizado. Si SH = "High" y la operación de escritura DDRAM, el desplazamiento de toda la pantalla es
realizado de acuerdo con el valor I / D:
I / D = "1": desplazamiento a la izquierda,
I / D = "0": desplazamiento a la derecha

 */
enum pines{RS=0x04,EN=0xC,D0=0x0,D1,D2,D3,D4,D5,D6,D7};
/*
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
  0  0  0   0   1  DL   N   F   -  -
 */

enum cursor{Shift_cursor_L,Shift_cursor_R,Shift_display_L,Shift_display_R};
//________________|Macros|______________________//
#define Display_shift(x)   0x10|(x<<2)
//_______________|Prototipos|__________________//
extern void delayMs(int n);
extern void UPDATE(void);
extern void UPDATE2(void);
extern uint_8 DPY_bfnWriteMsg (uint_8 bpMsgSrc[]);
extern void LCD_init(void);
extern void LCD_data(unsigned char data);
extern void LCD_command(unsigned char command);
extern void enteroACadena(unsigned int numero, char *bufer);

#endif /* LCD1_H_ */
