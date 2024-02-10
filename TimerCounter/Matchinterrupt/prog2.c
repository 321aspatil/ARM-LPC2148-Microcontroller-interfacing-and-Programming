//generate square wave using  Match Control Register(MCR) interrupt
#include <LPC213X.H>

void T0_ISR(void) __irq
{
	IOPIN0^=(1<<0);  // Toggle P0.0
	T0IR=0x01;      // Clear match interrupt flag
	VICVectAddr = 0x00;
}

int main(void)
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	IODIR0=(1<<0);   // Configure P0.0 as output
	VPBDIV=0x01;
	//T0PR=59;      // Set prescaler for 1ms delay
	T0MR0=300;       // Toggle after TC==500 (500ms delay)
	T0TCR=0x02;      // Reset Timer Counter and Prescaler Counter
	T0MCR=0x03;      // Reset Timer counter on match and generate interrupt
	VICVectCntl0=(1<<5)|4;  // Enable Timer 0 interrupt slot and assign it to channel 4
	VICVectAddr0=(unsigned)T0_ISR;  // Set interrupt vector address for Timer 0
	VICIntEnable=(1<<4);   // Enable Timer 0 interrupt

	T0TCR=0x01;      // Start Timer 0

	while(1);
}
