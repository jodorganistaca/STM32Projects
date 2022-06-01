#ifndef GPIO_H
#define GPIO_H
#include "stm32f10x.h"

typedef struct
{
	GPIO_TypeDef * GPIO;
	char GPIO_Pin; //0 to 15 (16 I/O pins by port A/B/C/D)
	char GPIO_Conf; //Input/Output configs (see below)
} GPIO_Struct;

#define In_Floating 0x21;
#define In_PullDown 0x21;
#define In_PullUp 0x21;
#define In_Analog 0x21;
#define Out_PushPull 0x21;
#define Out_OpenDrain 0x21;
#define AltOut_PushPull 0x21;
#define AltOut_OpenDrain 0x21;

#endif