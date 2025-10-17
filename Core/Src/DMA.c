#include "DMA.h"
#include "UART.h"
#include "EXTI.h"

void DMA1_Channel7_IRQHandler(void)
{
    if(DMA1_ISR & (0b1<<25))
    {
        DMA1_IFCR |= (0b1<<25);
        
    }
    
}

void DMA_transmit(char *c)
{
    int len = strlen(c);            

    DMA1_CCR7 &= ~(0b1 << 0);      
    DMA1_CMAR7 = (uint32_t)c;       // Địa chỉ buffer chứa chuỗi
    DMA1_CNDTR7 = len;                 // Số byte cần gửi
    DMA1_CCR7 |= (1 << 0);             // Enable channel (DMA bắt đầu chạy)

    while (!(DMA1_ISR & (1 << 25)));   // TCIF7
    DMA1_IFCR |= (0b1 << 25);            // Xóa cờ TC
    DMA1_CCR7 &= ~(0b1 << 0);       
    
}

void DMA_UART2_Config(void)
{
    DMA1_CCR7  &= ~(0b1 << 0); // clear bit EN
    DMA1_CPAR7 = 0x40004404; // địa chỉ UART2DR
    DMA1_CCR7 |= (0b10 << 12); // PL priority High
    DMA1_CCR7 |= (0b1 << 4); // DIR : 0: Read from peripheral 1: Read from memory
    DMA1_CCR7 |= (0b1 << 5); // CIRC: Circular mode .  1: Circular mode enabled
    DMA1_CCR7 |= (0b0 << 6); //  PINC: Peripheral increment mode .  0: Peripheral increment mode disabled
    DMA1_CCR7 |= (0b1 << 7); //  MINC : Memory increment mode.  1: Memory increment mode enabled 
    DMA1_CCR7 |= (0b00 << 8);// PSIZE[1:0]: Peripheral size  00: 8-bits
    DMA1_CCR7 |= (0b00 << 10); // MSIZE[1:0]: Memory size  00: 8-bits
    DMA1_CCR7 |= (0b1 <<2); //  HTIE: Half transfer interrupt enable.  1: HT interrupt enabled

    NVIC_DMA1_Channel7();
    DMA1_CCR7 |= (0b1 <<0); // Bit 0 EN: Channel enable 
}
