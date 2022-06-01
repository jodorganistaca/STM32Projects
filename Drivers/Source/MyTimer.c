#include "../Include/Driver_Timer.h"


// Function Pointers for each timer
void (* monPointeur1) (void);
void (* monPointeur2) (void);
void (* monPointeur3) (void);
void (* monPointeur4) (void);

// Initialize TIMER
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * TimerStruct)
{
	if (TimerStruct->Timer == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (TimerStruct->Timer == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (TimerStruct->Timer == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if (TimerStruct->Timer == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	TimerStruct->Timer->ARR = TimerStruct->ARR;
	TimerStruct->Timer->PSC = TimerStruct->PSC;
}

// Activate Interruption
void MyTimer_ActiveIT  (TIM_TypeDef * Timer , char Prio , void (*IT_function ) (void) ) 
{
	Timer->DIER |= TIM_DIER_UIE;
	//TODO : if (Timer == TIM1)
	
	if (Timer == TIM2) 
	{
		NVIC_SetPriority(TIM2_IRQn , Prio);
		NVIC_EnableIRQ(TIM2_IRQn );
		monPointeur2 = IT_function; 
	}
	else if (Timer == TIM3) 
	{
		NVIC_SetPriority(TIM3_IRQn , Prio);
		NVIC_EnableIRQ(TIM3_IRQn );
		monPointeur3 = IT_function; 
	}
	else if (Timer == TIM4) 
	{
		NVIC_SetPriority(TIM4_IRQn , Prio);
		NVIC_EnableIRQ(TIM4_IRQn );
		monPointeur4 = IT_function; 
	}
}

// Initialize PWM
void MyTimer_PWM_Init (TIM_TypeDef * Timer , char Channel ) 
{	
	Timer -> CR1 |= TIM_CR1_ARPE;
	Timer -> EGR |= TIM_EGR_UG;
	
	if (Channel==1)
	{
		Timer -> CCMR1 |= TIM_CCMR1_OC1PE; //Enable
		Timer -> CCER |= TIM_CCER_CC1E;
		Timer -> CCMR1 &=~ (TIM_CCMR1_OC1M); // Reset bits
		Timer -> CCMR1 |= TIM_CCMR1_OC1M_1; // bit 1
		Timer -> CCMR1 |= TIM_CCMR1_OC1M_2; // bit 2
	}
	else if (Channel==2)
	{
		Timer -> CCMR1 |= TIM_CCMR1_OC2PE; //Enable
		Timer -> CCER |= TIM_CCER_CC2E;
		Timer -> CCMR1 &=~ (TIM_CCMR1_OC2M); // Reset bits
		Timer -> CCMR1 |= TIM_CCMR1_OC2M_1; // bit 1
		Timer -> CCMR1 |= TIM_CCMR1_OC2M_2; // bit 2
	}
	else if (Channel==3)
	{
		Timer -> CCMR2 |= TIM_CCMR2_OC3PE; //Enable
		Timer -> CCER |= TIM_CCER_CC3E;
		Timer -> CCMR2 &=~ (TIM_CCMR2_OC3M); // Reset bits
		Timer -> CCMR2 |= TIM_CCMR2_OC3M_1; // bit 1
		Timer -> CCMR2 |= TIM_CCMR2_OC3M_2; // bit 2
	}
	else if (Channel==4)
	{
		Timer -> CCMR2 |= TIM_CCMR2_OC4PE; //Enable
		Timer -> CCER |= TIM_CCER_CC4E;
		Timer -> CCMR2 &=~ (TIM_CCMR2_OC4M); // Reset bits
		Timer -> CCMR2 |= TIM_CCMR2_OC4M_1; // bit 1
		Timer -> CCMR2 |= TIM_CCMR2_OC4M_2; // bit 2
	}	
}

// Configuration of PWM ratio
void MyTimer_PWM_ConfigureRatio(TIM_TypeDef * Timer, char Channel, int Ratio){
	int value = (Ratio * Timer->ARR) / 100;
	switch(Channel){
		case 1:
			Timer->CCR1 = value;	
		break;
		case 2:
			Timer->CCR2 = value;
		break;
		case 3:
			Timer->CCR3 = value;
		break;
		case 4:
			Timer->CCR4 = value;	
		break;
		default:
		break;
	}
}


// Functions Handlers
void TIM1_IRQHandler ( void ){
	TIM1->SR &= ~(TIM_SR_UIF);
	if (monPointeur1 != 0) (*monPointeur1) (); /* appel indirect de la fonction */
}

void TIM2_IRQHandler ( void ){
	TIM2->SR &= ~(TIM_SR_UIF);
	if (monPointeur2 != 0) (*monPointeur2) (); /* appel indirect de la fonction */
}

void TIM3_IRQHandler ( void ){
	TIM3->SR &= ~(TIM_SR_UIF);
	if (monPointeur3 != 0) (*monPointeur3) (); /* appel indirect de la fonction */
}

void TIM4_IRQHandler ( void ){
	TIM4->SR &= ~(TIM_SR_UIF);
	if (monPointeur4 != 0) (*monPointeur4) (); /* appel indirect de la fonction */
}