#include "msp.h"


void PORT1_IRQHandler(void)
{
	static uint8_t LED_state = 1;
	static uint8_t RGB_state = 0;
	
	int i = 100000;
	
	//Test if pin 1 was selected
	if ((P1->IFG & (uint8_t)(1<<1)))
	{
		while (i > 0) {i--;}
	
		if ((P1->IFG & (uint8_t)(1<<1)))
		{
			//Yes, pin 1: Clear flag
			P1->IFG &= (uint8_t)(~(1<<1));
			//switch LEDs
			LED_state ^= (uint8_t)(1 << 0);
			P1->OUT &= (~(1 << 0));
			P2->OUT &= (~((1 << 0) | (1 << 1) | (1 << 2)));
		}
	}
	else if ((P1->IFG & (uint8_t)(1<<4)))
	{
		while (i > 0) {i--;}
		if ((P1->IFG & (uint8_t)(1<<4)))
		{
			//Yes, pin 4: clear flag
			P1->IFG &= (uint8_t)(~(1<<4));
			
			//switch state of RED LED
			if (LED_state & (uint8_t)(1 << 0))
			{
				P1->OUT ^= (1 << 0);
			}
			else //switch state or RGB LED
			{
				if (RGB_state == 7)
				{
					RGB_state = 0;
				}
				else
				{
					RGB_state++;
				}
				P2->OUT &= (~((1 << 0) | (1 << 1) | (1 << 2)));
				P2->OUT |= RGB_state;
			}
		}
	}
}


int main()
{
  //Watchdog timer turned off  

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	
	//Select GPIO for P1 and 2
	P1->SEL0 &= (uint8_t)(~((1 << 0) |(1 << 1) | (1 << 4)));
	P1->SEL1 &= (uint8_t)(~((1 << 0) |(1 << 1) | (1 << 4))); 
	P2->SEL0 &= (uint8_t)(~((1 << 0) | (1 << 1) | (1 << 2)));
	P2->SEL1 &= (uint8_t)(~((1 << 0) | (1 << 1) | (1 << 2)));
  
	//Configure P1.1 and 1.4 as pull-up input resistors
	P1->DIR &= (uint8_t)(~((1 << 1) | (1 << 4)));
	P1->OUT |= (uint8_t)((1 << 1) | (1 << 4));  
	P1->REN |= (uint8_t)((1 << 1) | (1 << 4));  
	
	//Configure P1.0, 2.0, 2.1, 2.2 as outputs
	P1->DIR |= (uint8_t)(1 << 0);
	P2->DIR |= (uint8_t)((1 << 0) | (1 << 1) | (1 << 2));
   
	//Initialize LED states as off
	P1->OUT &= (uint8_t)(~(1 << 0));
	P2->OUT &= (uint8_t)(~((1 << 0) | (1 << 1) | (1 << 2)));
	
	//Configure device interrupts
	P1->IES |= (uint8_t)(((1 << 1) | (1 << 4)));
	P1->IFG &= (uint8_t)(~((1 << 1) | (1 << 4)));
	P1->IE |= (uint8_t)(((1 << 1) | (1 << 4)));
	
	//Configure NVIC
	NVIC_SetPriority(PORT1_IRQn, 2);
	NVIC_ClearPendingIRQ(PORT1_IRQn);
	NVIC_EnableIRQ(PORT1_IRQn);
	
	//Enable global interrupts
	__ASM("CPSIE I");
	
	while(1);
	
}


