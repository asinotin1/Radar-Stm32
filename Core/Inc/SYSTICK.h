#include <stdio.h>
#include <stdint.h>
#ifndef   __SYSTICK_H
#define   __SYSTICK_H

#define SCS_BASE        0xE000E000UL
#define SysTick_BASE     (SCS_BASE + 0x0010UL)


#define STK_CTRL_offset    0x00
#define STK_LOAD_offset    0x04
#define STK_VAL_offset     0x08
#define STK_CALIB_offset   0x0C



#define SysTick_CTRL    *((volatile uint32_t *)(SysTick_BASE  + STK_CTRL_offset))
#define SysTick_LOAD    *((volatile uint32_t *)(SysTick_BASE + STK_LOAD_offset))
#define SysTick_VAL     *((volatile uint32_t *)(SysTick_BASE + STK_VAL_offset))
#define SysTick_CALIB   *((volatile uint32_t *)(SysTick_BASE + STK_CALIB_offset))

void systick_delay_ms(int time);
void systick_delay_us(int time);
#endif