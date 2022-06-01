#include "stm32f10x.h"
#include "../../Drivers/Include/Driver_GPIO.h"

int main(void){
	//RCC -> APB2ENR |= (0x01 << 2) | (0x01 << 3)	| (0x01 << 4);
	//GPIO LED and Button
	MyGPIO_Struct_TypeDef led, btn;
	
	//Turn on registers GPIO C
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	//Config Led
	led.GPIO = GPIOA;
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
	} while (1);
}
