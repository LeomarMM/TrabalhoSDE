#include "timer.h"
 
#define bit16 (1<<16)
#define bit26 (1<<26)
#define bit27 (1<<27)
#define bit1  (1<<1)
#define bit0  (1<<0)
#define bit3  (1<<3)

void (*funcao)(void);

void desabilita_timer (void)
{
	LPC_RIT->RICTRL  &= ~bit3;
}

void habilita_timer(void)
{
	LPC_RIT->RICTRL  |= bit3;				// enable timer
}

void timer_init(void (*f)(void))
{
	LPC_SC->PCONP |= bit16;					//Power Control for Peripherals register: power up RIT clock
	LPC_SC->PCLKSEL1 |= (bit26 & bit27);	//Peripheral clock selection: divide clock by 8 (run RIT clock by 12MHz)
	LPC_RIT->RICOUNTER = 0;					//set counter to zero
	LPC_RIT->RICOMPVAL = 24000;				//interrupt tick every second (clock at 100MHz)
	LPC_RIT->RICTRL |= bit1;				// clear timer when counter reaches value
	LPC_RIT->RICTRL |= bit3;				// enable timer
	//enable interrupt
	NVIC_SetPriority(RIT_IRQn, 31);
	NVIC_EnableIRQ(RIT_IRQn);
	funcao = f;	
}
 
void RIT_IRQHandler(void (*f)(void))
{
	//clear flag
	LPC_RIT->RICTRL |= bit0; //write 1 to clear bit
	funcao();
}