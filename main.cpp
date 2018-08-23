#include "userdef.h"
#include "LyzkUsart.h"
#include <stdio.h>

int main ()
{
    LyzkUsart printer;
    
	LyzkGpio gpio;
	GpioConfig config;
	int i;
	
	config.m_mode	= GPIO_Mode_Out_PP;
	config.m_speed	= GPIO_Speed_10MHz;
	
	gpio.SetGPIOx (GPIOB);
	gpio.SetPin (GPIO_Pin_12);
	
	gpio.Init (config);
    
    USART_InitTypeDef cfg;
    cfg.USART_BaudRate      = 115200;
    cfg.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    cfg.USART_Mode          = USART_Mode_Rx | USART_Mode_Tx;
    cfg.USART_Parity        = USART_Parity_No;
    cfg.USART_StopBits      = USART_StopBits_1;
    cfg.USART_WordLength    = USART_WordLength_8b;
    printer.SetUSART (USART1);
    printer.Init (&cfg);
	
	gpio.Set ();
    
    printer.PutChar ('0');
    printer.PutChar ('\r');
    printer.PutChar ('\n');    
}
