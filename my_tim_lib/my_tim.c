#include "my_tim.h"

int TIM2_init(void)
{
	TIM_TimeBaseInitTypeDef    TIM_InitStruct;

	RCC_ClocksTypeDef RCC_Clocks;      // shows clocks freq
	RCC_GetClocksFreq(&RCC_Clocks);		//shows clocks freq

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_InitStruct.TIM_Prescaler = 4200 - 1;                // This will configure the clock to 20 kHz
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;     // Count-up timer mode
    TIM_InitStruct.TIM_Period = 20 - 1;                    // 20 kHz down to 1000 Hz = 1 ms
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        // Divide clock by 1
    TIM_InitStruct.TIM_RepetitionCounter = 0;                // Set to 0, not used
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);


}

int timer_ms(uint32_t ms) // delay function using TIM_2
{
	  if (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) != RESET)
	    {
	      TIM_ClearFlag(TIM2, TIM_IT_Update);
	      if(ms<=0)
	        return 0;
	      if(ms>0)
	        {
	        ms--;
	        return 1;
	        }

	    }
}

void delay_ms(uint32_t ms)
{
        volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
        for (; nCount!=0; nCount--);
}
/*
void delay_ms(uint32_t ms)
{
	RCC_ClocksTypeDef RCC_Freq;
	RCC_GetClocksFreq(&RCC_Freq);

	int b = RCC_Freq.SYSCLK_Frequency;
	float frq;
	frq = (float)1000000/b;
	int m = (int) ms/frq/13;
	while(m--)
	{
		;
	}

}
*/
