#include "TIM.h"
#include "EXTI.h"


void TIM2_init_IT(void){
	TIM2_PSC = 7999;
	TIM2_ARR = 999;
	TIM2_DIER |= (1 << 0);
	TIM2_CR1 |= (1 << 0);
	NVIC_ISER0 |= (1 << 28);
}

void TIM2_IRQHandler(void){
	if(TIM2_SR & 0x01){
		//doing sth
		TIM2_SR &= ~(uint32_t)(1 << 0);
	}
}


void delay_us(uint32_t us)
{
	TIM2_PSC = 7;
	TIM2_ARR = us;
	TIM2_CNT = 0;
	TIM2_CR1 |= (1 << 0);
	while(TIM2_CNT < us){}
	TIM2_CR1 &= ~(uint32_t)(1 << 0);
	TIM2_CNT = 0;
}

void delay_ms(uint32_t ms){
	TIM2_PSC = 7999;
	TIM2_ARR = ms;
	TIM2_CNT = 0;
	TIM2_CR1 |= (1 << 0);
	while(TIM2_CNT < ms){}
	TIM2_CR1 &= ~(uint32_t)(1 << 0);
	TIM2_CNT = 0;
}

void TIM_Input_Capture_forHCSR04(void)
{
	TIM3_PSC = 7;
	TIM3_ARR = 0xFFFF; // ARR càng lớn thì càng lấy được xung tần số thấp
	TIM3_CCMR1 &= ~(0b11<<0); // clear cc1s
	TIM3_CCMR1 |= (0b01<<0); // TIMER chanel 1 là input capture
	TIM3_CCMR1 |= (0b0000<<4); // k lọc
	TIM3_CCER |= (0b0<<1); //  CC1P: 1 bắt cạnh low, 0 bắt cạnh high
	TIM3_CCMR1 |= (0b00 << 2); // IC1PSC :00  k chia bắt hết tất cả các cạnh
	TIM3_CCER |=(0b1<<0); // CC1E. 1: Capture enabled.
	TIM3_DIER |= (0b1<<1); // CC1IE. 1: CC1 interrupt enabled. 0: CC1 interrupt disabled.
	TIM3_CR1 |= (0b1 << 7); //ARPE : Auto-reload preload enable.1: TIMx_ARR register is buffered

	TIM3_CR1 |= (0b1 << 0); // Enable couter 
	NVIC_ISER0 |= (1 << 29); // tim3 
}

uint32_t first = 0, second = 0;
uint32_t result = 0;
uint8_t capture_state = 0;

void TIM3_IRQHandler(void)
{
    if (TIM3_SR & (0b1<<1))   // Kiểm tra CC1IF
    {
        TIM3_SR &= ~(0b1<<1); // Xóa cờ bằng cách ghi 0

        if (capture_state == 0)
        {
            first = TIM3_CCR1;   // lần bắt 1
            capture_state = 1;
			TIM3_CCER |= (0b1<<1);
        }
        else
        {
            second = TIM3_CCR1;  // lần bắt 2
            result =(second-first)/58;
            capture_state = 0;   // reset lại
			TIM3_CCER &= ~(0b1<<1);	
			TIM3_CNT = 0;
        }
    }
}


void TIM4_PWM_init(void)
{
	TIM4_CCMR1 &= ~(0b111 << 4); // clear OC1M 
	TIM4_CCMR1 |= (0b110 << 4); // set OC1M (chế độ PWM mode 1 : cao trước, thâp sau)
	TIM4_CCER |= (0b1 << 0); // xuất ra tín hiệu ở chân chanel 1
	TIM4_PSC = 15;
	TIM4_ARR = 9999;
	TIM4_CR1 |= (0b1 << 0); // Enable couter 
}
void TIM4_PWM(uint32_t pulse_us)
{
    TIM4_CCR1 = pulse_us;
}
