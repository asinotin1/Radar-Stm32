#include "SYSTICK.h"

void systick_delay_ms(int time)
{
    while(time)
    {
        SysTick_CTRL |= (0b1<<2);
        SysTick_LOAD = 8000-1;
        SysTick_VAL = 0;
        SysTick_CTRL |= (0b1<<0);
        while(!(SysTick_CTRL & (0b1<<16)));
        --time;
    }
}

void systick_delay_us(int time)
{
    while(time)
    {
        SysTick_CTRL |= (0b1<<2);
        SysTick_LOAD = 8-1;
        SysTick_VAL = 0;
        SysTick_CTRL |= (0b1<<0);
        while(!(SysTick_CTRL & (0b1<<16)));
        --time;
    }
}