#include <LPC213X.H>

void T0_ISR (void)__irq              //isr for timer
{
	T0IR = ( T0IR | (0x02) ); 
	VICVectAddr = 0x00;
}

void init()   //initialization of timer
{	
	VICVectAddr0 = (unsigned) T0_ISR; 
	VICVectCntl0 = 0x00000024; 
	VICIntEnable = 0x00000010; 
	VICIntSelect = 0x00000000;
}

void pll_init()   //initialization of PLL
{
	PLLCON = 0x01;
	PLLCFG = 0x24;
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
	while(!(PLLSTAT & 0x00000400));
	PLLCON = 0x03;
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
	VPBDIV = 0x01;
}

int main (void)
{
	pll_init();
	PINSEL1=0x00080000;
	PINSEL0 |= 0x00000800;
	init();
	T0TCR = 0x02; 
	T0CTCR = 0x00; 
	T0MR1 = 6; 
	T0MCR = 0x0018; 
	T0EMR = 0x00C0;
	T0TCR = 0x01;
	while (1);
}
