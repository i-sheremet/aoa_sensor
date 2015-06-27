#include "ma3_encoder.h"

void _get_ma3_data()
{


  if (dataCaptureReady)
    {
      ma3_capture=(IC3ReadValue1 - IC3ReadValue2);
      if (ma3_capture<0)
        ma3_capture=4095+ma3_capture;

      ma3_capture_angle=ma3_capture/11.375; // translated into angle

      dataCaptureReady = 0;
    }
}

void TIM3_IRQHandler()
{

  if(TIM_GetITStatus(TIM3, TIM_IT_CC1) == SET)
    {
      //  Clear TIM3 Capture compare interrupt pending bit
      TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
      if(CaptureNumber == 0)
        {
          //  Get the Input Capture value
          IC3ReadValue1 = TIM_GetCapture1(TIM3);
          CaptureNumber = 1;
          tim3ConfigFalling();
        }
      else if(CaptureNumber == 1)
        {
          //  Get the Input Capture value
          IC3ReadValue2 = TIM_GetCapture1(TIM3);
          dataCaptureReady = 1;
          CaptureNumber = 0;
          tim3ConfigRising();
        }
    }
}

void _ma3_init()
{
  initGpio();
  initTimers();

  IC3ReadValue1 = 0;
  IC3ReadValue2 = 0;
  ma3_capture = 0;
  CaptureNumber = 0;
  dataCaptureReady = 0;
  ma3_capture_angle=0;
}

void initTimers()
{
         RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

         RCC_ClocksTypeDef RCC_Clocks;       // added
         RCC_GetClocksFreq(&RCC_Clocks);     // added

          // „астота счЄта - 10 мкс, период - 20 мс
         TIM_TimeBaseInitTypeDef base_timer;
         TIM_TimeBaseStructInit(&base_timer);
         base_timer.TIM_Prescaler = 84 - 1;
         base_timer.TIM_Period = 4095;//4080;
         base_timer.TIM_ClockDivision = 0;
         base_timer.TIM_CounterMode = TIM_CounterMode_Up;
         TIM_TimeBaseInit(TIM3, &base_timer);

         tim3ConfigRising();

         // TIM enable counter
         TIM_Cmd(TIM3, ENABLE);

         // Enable the CC2 Interrupt Request
         TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);

         NVIC_InitTypeDef NVIC_InitStructure;

         NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
         NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
         NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
         NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
         NVIC_Init(&NVIC_InitStructure);
}

void initGpio()
{
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

        GPIO_InitTypeDef gpioStruct;
        gpioStruct.GPIO_Mode = GPIO_Mode_IN;
        gpioStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
        gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
        gpioStruct.GPIO_Pin = GPIO_Pin_6;
        gpioStruct.GPIO_Mode = GPIO_Mode_AF;

        GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);

        GPIO_Init(GPIOA, &gpioStruct);
}

void tim3ConfigRising()
{
        TIM_ICInitTypeDef timICStruct;

        timICStruct.TIM_Channel = TIM_Channel_1;
        timICStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
        timICStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
        timICStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        timICStruct.TIM_ICFilter = 0x0;

        TIM_ICInit(TIM3, &timICStruct);
}

void tim3ConfigFalling()
{
        TIM_ICInitTypeDef timICStruct;

        timICStruct.TIM_Channel = TIM_Channel_1;
        timICStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
        timICStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
        timICStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        timICStruct.TIM_ICFilter = 0x0;

        TIM_ICInit(TIM3, &timICStruct);
}
