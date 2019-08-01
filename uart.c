/**
 * @file   uart.h
 * @Author Nikita.T (anikitatarasov@gmail.com)
 * @date   July, 2019
 * @brief  UART for atmega168/328
 *
 * Need to enable interrupts in void main and ISR
 *	ISR(USART_RX_vect){
 *	cli();
 *	data = UDR0;
 *	}
 */


#include <avr/io.h>
#include "uart.h"

/*!
	\brief init UART in 9600 8n1
	
	interrupts only on recieve
*/
void UART_Init(void){
	UBRR0 = MYUBRR;
	UCSR0B =  (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);  //Tx and Rx(interrupts) enable
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);   //8n1
}
/*!
	\brief transmitting one byte
*/
void UART_Send_Char(unsigned char c)
{
	while (!(UCSR0A & (1 << UDRE0))) ;
	UDR0 = c;
}
/*!
	\brief transmitting string
*/
void UART_Send_Str(char str[])
{
	unsigned char i = 0;
	while (str[i]!='\0')
	{
		UART_Send_Char(str[i]);
		i++;
	}
}
/*!
	\brief convert uint8_t to HEX(ascii) and transmitting
	
	\params prefix = 1 adds "0xFF" in ascii to package
*/
void UART_Send_u8_as_Hex(uint8_t num, uint8_t prefix)
{
	if(prefix == 1) UART_Send_Str("0x");
	UART_Send_Char(Get_Hex_from_byte(num >> 4));
	UART_Send_Char(Get_Hex_from_byte(num));
}
/*!
	\brief convert uint16_t to HEX(ascii) and transmitting
	
	\params prefix = 1 adds "0xFFFF" in ascii to package
*/
void UART_Send_u16_as_Hex(uint16_t num, uint8_t prefix)
{
	UART_Send_u8_as_Hex((uint8_t)(num >> 8), prefix);
	UART_Send_u8_as_Hex((uint8_t)num, 0);
}
/*!
	\brief converts 4 right bits to one HEX ASCII symbol 
*/
char Get_Hex_from_byte(uint8_t fourth_of_byte){
	fourth_of_byte &= 0b00001111; //!bitmask
	return ((fourth_of_byte < 10) ? (fourth_of_byte + '0') : (fourth_of_byte + 'A' - 10));	
}