#include "UART.h"
#include "GPIO.h"
#include "EXTI.h"
void USART1_IRQHandler(void){
	if(USART1_SR & (1 << 5)){
		//Doing sth
		char c = (char)(USART1_DR & (0xFF));
		UART1_SendChar(c);
	}
}

void UART1_Init(void){
	
	GPIO_Config(GPIOA,GPIO_PIN_9,GPIO_MODE_AF_PP);
	GPIO_Config(GPIOA,GPIO_PIN_10,GPIO_MODE_INPUT_FLOATING);
	
    USART1_BRR = 0x0341;

    USART1_CR1 |= (1 << 13);  
    USART1_CR1 |= (1 << 3);   
    USART1_CR1 |= (1 << 2);

	USART1_CR1 |= (1 << 5);
	NVIC_UART_En();

}
void UART1_SendChar(char c) {
    while (!(USART1_SR & (1 << 7))); 
    USART1_DR = c;
}

void UART1_SendString(const char *str) {
    while (*str) {
        UART1_SendChar(*str++);
    }
}


void UART2_Init(void)
{
    // transmit
    GPIO_Config(GPIOA,GPIO_PIN_2,GPIO_MODE_AF_PP);
    GPIO_Config(GPIOA,GPIO_PIN_3,GPIO_MODE_INPUT_FLOATING);
    USART2_CR1 |= (0b1<<13);
    USART2_CR1 |=  (0b0<<12);
    USART2_CR2 |=(0b00<<12);
    USART2_BRR = 0x0341;
    USART2_CR1 |= (0b1<<3);
    USART2_CR3 |= (0b1 <<7);
}

void UART2_SendChar(char c)
{
    while((USART2_SR & (0b1<<7)) == 0 );
        USART2_DR = c;
    while((USART2_SR & (0b1<<6))==0);
}

void UART2_SendString(const char *str) 
{
    while (*str)
    {
        UART2_SendChar(*str++);
    }
    
}
void UART2_RECEVIED(void)
{
    USART2_CR1 |=   (0b1<<13);
    USART2_CR1 |=   (0b0<<12);
    USART2_CR2 |=   (0b00<<12);
    USART2_BRR  =   (52 << 4) | (1 << 0);
    USART2_CR1 |=   (0b1<<2);
    USART2_CR3 |=   (0b1<< 6);
}

uint8_t Read_data_uart2()
{
    while((USART2_SR & (0b1<<5))==0);
    uint8_t c = USART2_DR;
    return c;
}

void UART2_ReadString(uint8_t *buffer, uint32_t length)
{
    uint8_t c;
    for(uint32_t i =0 ;i<length;i++)
    {
        c = Read_data_uart2();
        *buffer = c;
        buffer++;
    }
        *buffer = '\0';
}


void Send_and_read(char *c)
{
    while((USART2_SR & (0b1<<5))==0);
    *c = USART2_DR;
    while((USART2_SR & (0b1<<7)) == 0 );
    USART2_DR = *c;
    //while((USART2_SR & (0b1<<6))==0);
}