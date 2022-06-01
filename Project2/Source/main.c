#include "stm32f10x.h"
#include "../../Drivers/Include/Driver_Timer.h"
#include "../../Drivers/Include/Driver_GPIO.h"

// CALLBACK FUNCTION FOR TIMER
MyGPIO_Struct_TypeDef led;
void Callback () {
	MyGPIO_Toggle(led.GPIO, led.GPIO_Pin);
}

int main(void)
{
	

	while(1);
}
