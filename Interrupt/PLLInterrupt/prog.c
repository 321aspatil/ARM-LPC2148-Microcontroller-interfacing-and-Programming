/*
write an embedded c program to obtain CCLOCK=60MHz using PLL interrupt.also set PCLOCK=30Mhz.
configure PLL interrupt as VIRQ assign slot no.6
frequency of oscillation fosc=12Mhz
*/
#include <LPC213X.H>
void pll_init()
{
	PLLCFG=0x24;
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
}
void pll_isr(void)__irq
{
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x02;
}
void isr_init()
{
	VICVectCntl6=(1<<5)|12;
	VICVectAddr6=(unsigned)pll_isr;
	VICIntEnable=(1<<12);
}
int main()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	while(IOPIN0&(1<<0));
	pll_init();
  isr_init();
  while(1);
}
