# avr_uart
UART 9600 8n1 for atmega168/328 with interrupts

remember to put this code in void main

```c
#include "uart.h"

ISR(USART_RX_vect){
    cli();
    data = UDR0;
    //put handler here
}

int main(void){
  UART_Init();
  sei();
}
```
