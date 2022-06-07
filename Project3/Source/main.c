#include "stm32f10x.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

int voltage_poten = 0;

void Callback(void){
	voltage_poten = (int) ADC1->DR / 10;
	//printf("%d",voltage_poten);
}

int main(void){
	
	
	MyGPIO_Struct_TypeDef a, led;
	MyTimer_Struct_TypeDef t;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	//ADC INIT
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->CR2 |= ADC_CR2_CONT;
	ADC1->CR2 |= ADC_CR2_ADON;
	
	a.GPIO = GPIOA;
	a.GPIO_Conf = In_Analog;
	a.GPIO_Pin = 0;
	
	led.GPIO = GPIOA;
	led.GPIO_Conf = Out_PushPull;
	led.GPIO_Pin = 1;
	
	t.Timer = TIM1;
	t.ARR = 7200;
	t.PSC = 10000;
	
	MyGPIO_Init(&a);	
	MyGPIO_Init(&led);	
	MyTimer_Base_Init(&t);
	t.Timer->CR1 |= TIM_CR1_CEN;
	MyTimer_ActiveIT(t.Timer,1,Callback);
	ADC1->CR2 |= ADC_CR2_ADON;

 while(1){
	voltage_poten = (int) ADC1->DR / 10;
	 if(voltage_poten > 50){
		MyGPIO_Set(led.GPIO,led.GPIO_Pin);
	 }else{
		MyGPIO_Reset(led.GPIO,led.GPIO_Pin);
	 }
 };
}
