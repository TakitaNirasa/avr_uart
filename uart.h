/**
 * @file   uart.h
 * @Author Nikita.T (anikitatarasov@gmail.com)
 * @date   July, 2019
 * @brief  UART for atmega168/328
 *
 */


#ifndef UART_H_
#define UART_H_

//!put cpu frequency here
#ifndef F_CPU
	#define F_CPU 8000000
#endif

//!put boudrate here and replace commented code lower
#define BAUD 9600	
//!or put number from datasheet table
#define MYUBRR 51//(F_CPU/16/BAUD-1)

void UART_Init(void);
void UART_Send_Char(unsigned char c);
void UART_Send_Str(char str[]);
void UART_Send_u8_as_Hex(uint8_t num, uint8_t prefix);
void UART_Send_u16_as_Hex(uint16_t num, uint8_t prefix);
char Get_Hex_from_byte(uint8_t fourth_of_byte);

#endif /* UART_H_ */