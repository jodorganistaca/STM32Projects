#include "stm32f10x.h"

int main(void){
	//00000000 00000000
	//00000000 00001110 
	RCC -> APB2ENR |= (0x01 << 2) | (0x01 << 3)	| (0x01 << 4);
	
	while(1);
}
