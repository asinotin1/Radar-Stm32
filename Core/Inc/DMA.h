#ifndef DMA_H
#define DMA_H
#include <stdint.h>
//--------------------------ADDRESS BASE DMA-----------------------
#define DMA_BASE_ADDRESS     0x40020000UL

//----------------------------ADDRESS REGISTER---------------------

#define  DMA_ISR    0x000
#define  DMA_IFCR   0x004
#define  DMA_CCR1   0x008
#define  DMA_CNDTR1 0x00C
#define  DMA_CPAR1  0x010
#define  DMA_CMAR1  0x014  
#define  DMA_CCR2   0x01C
#define  DMA_CNDTR2 0x020
#define  DMA_CPAR2  0x024
#define  DMA_CMAR2  0x028
#define  DMA_CCR3   0x030
#define  DMA_CNDTR3 0x034 
#define  DMA_CPAR3  0x038
#define  DMA_CMAR3  0x03C
#define  DMA_CCR4   0x044
#define  DMA_CNDTR4 0x048 
#define  DMA_CPAR4  0x04C
#define  DMA_CMAR4  0x050
#define  DMA_CCR5   0x058
#define  DMA_CNDTR5 0x05C
#define  DMA_CPAR5  0x060 
#define  DMA_CMAR5  0x064
#define  DMA_CCR6   0x06C
#define  DMA_CNDTR6 0x070
#define  DMA_CPAR6  0x074
#define  DMA_CMAR6  0x078   
#define  DMA_CCR7   0x080 
#define  DMA_CNDTR7 0x084
#define  DMA_CPAR7  0x088
#define  DMA_CMAR7  0x08C


//---------------------------DMA--------------------------------------------------

#define  DMA1_ISR         *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_ISR))
#define  DMA1_IFCR        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_IFCR))
#define  DMA1_CCR1        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CCR1))
#define  DMA1_CNDTR1      *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CNDTR1))
#define  DMA1_CPAR1       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CPAR1))
#define  DMA1_CMAR1       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CMAR1))
#define  DMA1_CCR2        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CCR2))
#define  DMA1_CNDTR2      *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CNDTR2))
#define  DMA1_CPAR2       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CPAR2)) 
#define  DMA1_CMAR2       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CMAR2))
#define  DMA1_CCR3        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CCR3))
#define  DMA1_CNDTR3      *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CNDTR3))
#define  DMA1_CPAR3       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CPAR3))
#define  DMA1_CMAR3       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CMAR3))
#define  DMA1_CCR4        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CCR4))
#define  DMA1_CNDTR4      *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CNDTR4))
#define  DMA1_CPAR4       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CPAR4)) 
#define  DMA1_CMAR4       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CMAR4))
#define  DMA1_CCR5        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CCR5)) 
#define  DMA1_CNDTR5      *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CNDTR5))   
#define  DMA1_CPAR5       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CPAR5))
#define  DMA1_CMAR5       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CMAR5))
#define  DMA1_CCR6        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CCR6))
#define  DMA1_CNDTR6      *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CNDTR6))
#define  DMA1_CPAR6       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CPAR6))
#define  DMA1_CMAR6       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CMAR6))
#define  DMA1_CCR7        *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CCR7))
#define  DMA1_CNDTR7      *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CNDTR7))
#define  DMA1_CPAR7       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CPAR7))
#define  DMA1_CMAR7       *((volatile  uint32_t*)(DMA_BASE_ADDRESS + DMA_CMAR7))

//---------------------------------API----------------------------------------
void DMA_UART2_Config(void);
void DMA1_Channel7_IRQHandler(void);
void DMA_transmit(char *c);
#endif