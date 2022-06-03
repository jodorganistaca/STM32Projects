#include "../Include/Driver_Timer.h"

void (* pointer1) (void);
void (* pointer2) (void);
void (* pointer3) (void);

// Initialize TIMER
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * TimerStruct)
{
	TIM_TypeDef * TimerS = TimerStruct->Timer;
	if(TimerS==TIM1){
		//RCC->APB2ENR |= RCC_APB1ENR_TIM1EN;
	}else if(TimerS==TIM2){
		RCC->APB2ENR |= RCC_APB1ENR_TIM2EN;
	}
	else if(TimerS==TIM3){
		RCC->APB2ENR |= RCC_APB1ENR_TIM3EN;
	}
	else if(TimerS==TIM4){
		RCC->APB2ENR |= RCC_APB1ENR_TIM4EN;
	}
	
	TimerStruct->Timer->ARR = TimerStruct->ARR;
	TimerStruct->Timer->PSC = TimerStruct->PSC;

}

// Activate Interruption
void MyTimer_ActiveIT  (TIM_TypeDef * Timer , char Prio , void (*IT_function ) (void) ) 
{
	Timer->DIER |= TIM_DIER_UIE;
	if(Timer==TIM2){
		NVIC_SetPriority(TIM2_IRQn, Prio);
		NVIC_EnableIRQ(TIM2_IRQn);
		pointer1 = IT_function;
	}else if(Timer==TIM3){
		NVIC_SetPriority(TIM3_IRQn, Prio);
		NVIC_EnableIRQ(TIM3_IRQn);
		pointer2 = IT_function;
	}else if(Timer==TIM4){
		NVIC_SetPriority(TIM4_IRQn, Prio);
		NVIC_EnableIRQ(TIM2_IRQn);
		pointer3 = IT_function;
	}
}

// Initialize PWM
void MyTimer_PWM_Init (TIM_TypeDef * Timer , char Channel ) 
{	


}

// Configuration of PWM ratio
void MyTimer_PWM_ConfigureRatio(TIM_TypeDef * Timer, char Channel, int Ratio){

}


// Functions Handlers
void TIM1_IRQHandler ( void ){

}

void TIM2_IRQHandler ( void ){

}

void TIM3_IRQHandler ( void ){

}

void TIM4_IRQHandler ( void ){

}