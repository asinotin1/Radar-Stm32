#include <stdint.h>
#include <stdio.h>
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"
#include "EXTI.h"
#include <string.h>
#include "AFIO.h"
#include "UART.h"
#include "DMA.h"
#include "SYSTICK.h"
#include <stdbool.h>
extern uint32_t result;
char str1[20];

uint32_t read_distance(void);

int main()
{
    HAL_Init();        
    
    RCC_Enable_PortB();
    RCC_Enable_PortC();
    RCC_Enable_PortA();
    RCC_Enable_AFIO();
    RCC_Enable_TIM2();
    RCC_Enable_TIM3();
    RCC_Enable_TIM4();
    RCC_Enable_USART2();
    RCC_Enable_DMA();

    uint32_t *afio = (uint32_t *)(0x40010000 + 0x4);
    *afio = (0b010 << 23); // remap TIM4

    GPIO_Config(GPIOB, GPIO_PIN_6, GPIO_MODE_AF_PP);     // TIM4 PWM
    GPIO_Config(GPIOA, GPIO_PIN_6, GPIO_MODE_INPUT_FLOATING); // Echo
    GPIO_Config(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP); // Trig
    GPIO_Config(GPIOB, GPIO_PIN_12, GPIO_MODE_OUTPUT_PP); // led
    TIM_Input_Capture_forHCSR04();
    UART2_Init();
    TIM4_PWM_init();
    uint32_t distance;
    while (1)
    {
        for (int i = 250; i <= 1250; i += 10)
        {
         TIM4_PWM(i);
         systick_delay_ms(3); // servo ổn định
        distance = read_distance();
        if (distance == 0 || distance > 400) continue; // bỏ giá trị nhiễu

        if (distance > 0 && distance <= 50)
            GPIO_Write_Pin(GPIOB, GPIO_PIN_12, 1);
        else
            GPIO_Write_Pin(GPIOB, GPIO_PIN_12, 0);

        sprintf(str1, " %d %d", distance, i);
        UART2_SendString(str1);
        systick_delay_ms(5);
        }
    }
    return 0;
}


uint32_t read_distance(void)
{
    GPIO_Write_Pin(GPIOA, GPIO_PIN_7, 1);
    delay_us(15);
    GPIO_Write_Pin(GPIOA, GPIO_PIN_7, 0);
    uint32_t start = HAL_GetTick();
    while ((HAL_GetTick() - start) < 60)
    {
        if(result != 0)
            return result;
    }  

    return 0;
}
