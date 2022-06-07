#include "stm32f10x.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

// CALLBACK FUNCTION FOR TIMER
MyGPIO_Struct_TypeDef g;

void Callback () {
	MyGPIO_Toggle(g.GPIO, g.GPIO_Pin);
}

int main(void)
{
	//GPIO Timer
	/*MyTimer_Struct_TypeDef t;
	MyGPIO_Struct_TypeDef g;
	
	//Turn on GPIOA C
	
	//PWM out´config
	led.GPIO = GPIOC;
	led.GPIO_Conf = Out_PushPull;
	led.GPIO_Pin = 10;
	MyGPIO_Init(&led);
	
	g.GPIO = GPIOA;
	g.GPIO_Conf = AltOut_PushPull;
	g.GPIO_Pin = 0;
	MyGPIO_Init(&g);
	
	//Config tim2
	t.Timer = TIM2;
	t.ARR = 6000-1;
	t.PSC = 6000-1;
	MyTimer_Base_Init(&t);
	
	MyTimer_PWM_Init(t.Timer,1);
	MyTimer_PWM_ConfigureRatio(t.Timer,1, 10);
	
	//Activate timer and configs
	MyTimer_ActiveIT(t.Timer, 1, Callback);
	MyTimer_Base_Start(t.Timer);*/
	//MyGPIO_Struct_TypeDef g;
	MyGPIO_Struct_TypeDef b;
	MyTimer_Struct_TypeDef t;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;
	
	g.GPIO = GPIOC;
	g.GPIO_Conf = Out_PushPull;
	g.GPIO_Pin = 5;
	
	b.GPIO = GPIOC;
	b.GPIO_Conf = In_PullUp;
	b.GPIO_Pin = 3;
	
	t.Timer = TIM3;
	t.ARR = 34463;
	t.PSC = 34463;
	
	MyGPIO_Init(&g);
	MyGPIO_Init(&b);	
	MyTimer_Base_Init(&t);	
	MyTimer_ActiveIT(t.Timer,1,Callback);
	MyTimer_Base_Start(t.Timer);
	
	while(1){
		/*if(MyGPIO_Read(b.GPIO,b.GPIO_Pin)){
			MyGPIO_Reset(g.GPIO,g.GPIO_Pin);
		}else{
			MyGPIO_Set(g.GPIO,g.GPIO_Pin);
		}*/
	};
}
