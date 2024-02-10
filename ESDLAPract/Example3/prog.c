/*
write an embedded c program to obtain CCLOCK=60MHz using PLL interrupt.also set PCLOCK=30Mhz.
configure PLL interrupt as VIRQ assign slot no.6
frequency of oscillation fosc=12Mhz
*/
#include <LPC213X.H>
#include "LCD8.h"
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
	//VICIntSelect|=(0<<12);
	VICVectCntl6=(1<<5)|12;
	VICVectAddr6=(unsigned)pll_isr;
	VICIntEnable=(1<<12);
}
int main()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	lcd_init();
	delay();
	lcd_cmd(0x01);
	delay();
	lcd_cmd(0x80);
	delay();
	str("CCLK=12MHz");
	delay();
	lcd_cmd(0x90);
	str("PCLK=3MHz");
	delay();
	while(!(IOPIN0&(1<<20)));
	pll_init();
  isr_init();
	lcd_cmd(0x01);
	delay();
	lcd_cmd(0x80);
	delay();
	str("CCLK=60MHz");
	delay();
	lcd_cmd(0x90);
	delay();
	str("PCLK=30MHz");
	delay();
  while(1);
}


