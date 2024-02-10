/*Write an embedded C program to generate square wave on port pin P0.4 using external interrupt 0 
and rectangular wave on port pin P0.5 using external interrupt 1.Configure both interrupt sources as VIRQ.
External Interrupt 0 pin-P0.1(Highest Priority)
External Interrupt 1 pin-P0.3(Lowest Priority)
What is the latency?
*/
#include <LPC213X.H>
void delay(unsigned int j)
{
	unsigned int i;
	for(i=0;i<1275*j;i++);
}
void extint0()__irq
{
	IOSET0=(1<<4);
	delay(1);
	IOCLR0=(1<<4);
	delay(1);
	EXTINT=0x01;
	VICVectAddr=0x00;
}
void extint1()__irq
{
	IOSET0=(1<<5);
	delay(2);
	IOCLR0=(1<<5);
	delay(1);
	EXTINT=0x02;
	VICVectAddr=0x00;
}
void extint_init()
{
	PINSEL0=(3<<2)|(3<<6);
	VICIntSelect|=(0<<14)|(0<<15);
	VICVectAddr0=(unsigned)extint0;
	VICVectCntl0=(1<<5)|14;
	VICVectAddr15=(unsigned)extint1;
	VICVectCntl15=(1<<5)|15;
	VICIntEnable=(1<<14)|(1<<15);
}
int main()
{
	IODIR0|=(1<<4)|(1<<5);
	extint_init();
	while(1);
}
