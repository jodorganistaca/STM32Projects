#include "stm32f10x.h"
#include "../../Drivers/Include/Driver_GPIO.h"

void (* pointer) (void);

void Callback(){
	//toogle bit
	GPIOA->ODR ^= (0x1 << 5);
}

void TIM2_IRQHandler(void) {
	TIM2->SR &=~ (TIM_SR_UIF);
	if(pointer != 0) (* pointer) ();
}

int main(void){
	//RCC -> APB2ENR |= (0x01 << 2) | (0x01 << 3)	| (0x01 << 4);
	//GPIO LED and Button
	/*MyGPIO_Struct_TypeDef led, btn;
	
	//Turn on registers GPIO C
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	//Config Led
	led.GPIO = GPIOC;
	led.GPIO_Pin = 5;
	led.GPIO_Conf = Out_PushPull;
	MyGPIO_Init(&led);
	
	//Config button
	btn.GPIO = GPIOC;
	btn.GPIO_Pin = 13;
	btn.GPIO_Conf = In_PullUp;
	MyGPIO_Init(&btn);
	
	do
	{
		if(!MyGPIO_Read(btn.GPIO, btn.GPIO_Pin)){
			MyGPIO_Set(led.GPIO, led.GPIO_Pin);
		}else{
			MyGPIO_Reset(led.GPIO, led.GPIO_Pin);
		}
	}*/
	//Enable GPIOA GPIOC Clock
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;
	//CONFIG GPIOA PORT 5 OUT PUSH PULL
	GPIOA ->CRL &=~ (0xF << (5 * 4));
	GPIOA ->CRL |= (0x1 << (5 * 4));
	//CONFIG GPIOC PORT 13 INPUT
	GPIOC -> CRH &=~ (0xF << ((13-8) * 4));
	GPIOC -> CRH |= (0x8 << ((13-8) * 4));	
	//PULLUP
	//GPIOC -> ODR |= (0x1 << 13);
	//PULLDOWN
	GPIOC -> ODR &=~ (0x1 << 13);
	//Enable timer2 Clock
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->ARR=7200;
	TIM2->PSC=1000;
	//Start timer
	TIM2->CR1|=TIM_CR1_CEN;
	//Activate Interruption
	TIM2->DIER |= TIM_DIER_UIE;
	//Set Priority
	NVIC_SetPriority(TIM2_IRQn, 1);
	//Enable interruption
	NVIC_EnableIRQ(TIM2_IRQn);
	//Assign callback function
	pointer = Callback;
	do {
		if(GPIOC->IDR&(1 << 13)){
			GPIOA->ODR |= (0x1 << 5);
		}else{
			GPIOA->ODR &=~(0x1 << 5);
		}
	}
	while (1);
}
