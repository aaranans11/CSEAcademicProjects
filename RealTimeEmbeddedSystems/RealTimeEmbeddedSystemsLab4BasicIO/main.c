#include "msp.h"

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
	
	uint8_t LED_state = 1;
	uint8_t RGB_state = 0;
	
	
	while(1)
		{
			int i = 100000;
			while(P1->IN & (uint8_t)(1 << 1) && P1->IN & (uint8_t)(1 << 4)) {}
			while (i > 0) {i--;}
			if (P1->IN & (uint8_t)(1 << 1) && P1->IN & (uint8_t)(1 << 4)){
				continue;
			}
			
			else
				{
					if (P1->IN & (uint8_t)(1 << 4))
						{
							LED_state ^= (uint8_t)(1 << 0);
							P1->OUT &= (~(1 << 0));
							P2->OUT &= (~((1 << 0) | (1 << 1) | (1 << 2)));
						}
						
						else if (P1->IN & (uint8_t)(1 << 1))
							{
								if (LED_state & (uint8_t)(1 << 0))
									{
										P1->OUT ^= (1 << 0);
									}
									else
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
}


