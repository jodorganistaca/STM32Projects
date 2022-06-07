#include "stm32f10x.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

int voltage_poten;

void Callback(void){

	printf("%d",voltage_poten);
}

int main(void){
	
	
	MyGPIO_Struct_TypeDef a;
	MyTimer_Struct_TypeDef t;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	//ADC INIT
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->CR2 |= ADC_CR2_CONT;
	ADC1->CR2 |= ADC_CR2_ADON;
	
	a.GPIO = GPIOA;
	a.GPIO_Conf = In_Analog;
	a.GPIO_Pin = 0;
	
	t.Timer = TIM1;
	t.ARR = 7200;
	t.PSC = 10000;
	
	MyGPIO_Init(&a);	
	MyTimer_Base_Init(&t);
	t.Timer->CR1 |= TIM_CR1_CEN;
	MyTimer_ActiveIT(t.Timer,4,Callback);
	ADC1->CR2 |= ADC_CR2_ADON;

 while(1){
	voltage_poten = (int) ADC1->DR / 10;
 };
}
