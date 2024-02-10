/*
  Compare match mode for timer in LPC2148(ARM7)
  http://www.electronicwings.com/arm7/lpc2148-resetstop-timer-on-compare-match
*/

#include <lpc213x.h>

__irq void T0_ISR (void)
{
	T0IR = ( T0IR | (0x02) ); 
	VICVectAddr = 0x00;
}


int main (void)
{
	PLLCFG=0x24;
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	while(!(PLLSTAT&(1<<10)));
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x01;
	//VPBDIV = 0x00000002; /* For Pclk = 30MHz */
	/* We have configured Cclk=60MHz. Above instruction makes Pclk = Cclk/2 = 30MHz */
	PINSEL0 = PINSEL0 | 0x00000800; /* Configure P0.5 as Match 0.1 */
	VICVectAddr0 = (unsigned) T0_ISR; /* T0 ISR Address */
	VICVectCntl0 = 0x00000024; /* Enable T0 IRQ slot */
	VICIntEnable = 0x00000010; /* Enable T0 interrupt */
	VICIntSelect = 0x00000000; /* T0 configured as IRQ */
	T0TCR = 0x02; /* Reset TC and PR */
	T0CTCR = 0x00; /* Timer mode, increment on every rising edge */
	//T0PR = 0x1D; /* Load Pre-Scalar counter with 29 (0 to 29 = 30), so that timer counts every 1usec */
	T0MR1 =2; /* Load timer counter for 100msec delay, 1usec*1000*100 */
	T0MCR = 0x0018; /* Interrupt generate on match and reset timer */
	T0EMR = 0x00C0; /* EM1 enable with toggling on match */
	T0TCR = 0x01; /* Enable timer */

	while (1);
}
