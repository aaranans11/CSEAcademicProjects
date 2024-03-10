//SYSC330 Lab 7
//Authors: Aaranan Sathiendran (10119639), Mark Hamad (101182093), Justin Worthing(101200580)
#include "msp.h"

//uint8_t LED_state = 1;
uint8_t RGB_state = 0;

void TA0_N_IRQHandler(void)
{
		TA0CTL &= (uint16_t)(~(1<<0)); //clear TAIFG interrupt flag
		
		//switch state of RED LED
		P1->OUT ^= (1 << 0);
}

void TA1_N_IRQHandler(void)
{
		TA1CTL &= (uint16_t)(~(1<<0)); //clear TAIFG interrupt flag
		
		//switch state of RGB LED
		RGB_state = (RGB_state + 1) % 8;
		P2->OUT &= (~((1 << 0) | (1 << 1) | (1 << 2)));
		P2->OUT |= RGB_state;
}

void TA1_0_IRQHandler(void)
{
		TA1CCTL0 &= (uint16_t)(~(1<<0)); //clear TA1CCIFG interrupt flag
		
		//switch state of RGB LED
		RGB_state = (RGB_state + 1) % 8;
		P2->OUT &= (~((1 << 0) | (1 << 1) | (1 << 2)));
		P2->OUT |= RGB_state;
}

int main()
{
  //Watchdog timer turned off  

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	
	//Select GPIO for P1 and 2
	P1->SEL0 &= (uint8_t)(~((1 << 0)));
	P1->SEL1 &= (uint8_t)(~((1 << 0))); 
	P2->SEL0 &= (uint8_t)(~((1 << 0) | (1 << 1) | (1 << 2)));
	P2->SEL1 &= (uint8_t)(~((1 << 0) | (1 << 1) | (1 << 2)));

	//Configure P1.0, 2.0, 2.1, 2.2 as outputs
	P1->DIR |= (uint8_t)(1 << 0);
	P2->DIR |= (uint8_t)((1 << 0) | (1 << 1) | (1 << 2));
   
	//Initialize Red LED state as on and RGB led as off
	P1->OUT |= (uint8_t)(1 << 0);
	P2->OUT &= (uint8_t)(~((1 << 0) | (1 << 1) | (1 << 2)));
	
	//Configure timer interrupts
	TA0CTL &= (uint16_t)(~((1<<5) | (1<<4))); //stop timer
	TA0CTL &= (uint16_t)(~(1<<0)); //clear TAIFG interrupt flag
	TA0CCR0 = 0x7FFF;; //Set CCR0 to 32768 - 1
	TA0CTL |= (uint16_t)((1<<1)); //interrupt enable (TAIE)
	TA0CTL |= (uint16_t)((1<<4)); //up mode
	TA0CTL |= (uint16_t)((1<<8)); //Select ACLK
	
	TA1CTL &= (uint16_t)(~((1<<5) | (1<<4))); //stop timer
	//Configure timerA1 to start at 0.4s to implement 0.1s offset between LEDs
	TA1R = 0x3332;
	TA1CTL &= (uint16_t)(~(1<<0)); //clear TAIFG interrupt flag
	TA1CCR0 = 0x3FFF; //Set CCR0 to 16384 - 1
	TA1CTL |= (uint16_t)((1<<1)); //interrupt enable (TAIE)
	TA1CTL |= (uint16_t)((1<<4) | (1<<5)); //up/down mode
	TA1CTL |= (uint16_t)((1<<8)); //Select ACLK
	
	TA1CCTL0 &= (uint16_t)(~(1<<0)); //clear TA1CCIFG interrupt flag
	TA1CCTL0 |= (uint16_t)((1<<4)); //interrupt enable (TA1CCIE)
	
	//Configure NVIC
	NVIC_SetPriority(TA0_N_IRQn, 1);
	NVIC_ClearPendingIRQ(TA0_N_IRQn);
	NVIC_EnableIRQ(TA0_N_IRQn);
	
	NVIC_SetPriority(TA1_N_IRQn, 1);
	NVIC_ClearPendingIRQ(TA1_N_IRQn);
	NVIC_EnableIRQ(TA1_N_IRQn);
	
	NVIC_SetPriority(TA1_0_IRQn, 1);
	NVIC_ClearPendingIRQ(TA1_0_IRQn);
	NVIC_EnableIRQ(TA1_0_IRQn);
	
	//Enable global interrupts
	__ASM("CPSIE I");
	
	while(1);
	
}


