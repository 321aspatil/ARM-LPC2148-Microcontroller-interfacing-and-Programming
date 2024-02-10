/*write an embedded c program to operate DC motor in either direction on occurance of an interrupt.
use virq.generate reactangular wave on port p1.31.use it as interrupt source.
Example configure one interrupt ext 0 as high level sensitive while external interrupt 1 as low level sensitive.
*/
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<12750;i++);
}
void FIQ_Handler()__irq
{
	long int temp=EXTINT;
	if(temp & 0x01)
	{
		IOSET0=(1<<26);
		IOCLR0=(1<<25);
		delay();
		delay();
		delay();

	}
	EXTINT=temp;
}
void ext1isr()__irq
{
	long int temp=EXTINT;
	if(temp & 0x02)
	{
		IOSET0=(1<<25);
		IOCLR0=(1<<26);
		delay();
		delay();
	}
	EXTINT=temp;
	VICVectAddr=00;
}
void isrinit()
{
	  PINSEL0=(3<<2)|(3<<6);
	  VICIntSelect|=(1<<15);
	  VICVectCntl15=(1<<5)|15;
	  VICVectAddr15=(unsigned)ext1isr;
	  VICIntEnable=(1<<14)|(1<<15);
}
int main()
{
	IODIR0=(1<<25)|(1<<26);
	IODIR1=(1<<31);
	isrinit();
	while(1)
	{
		IOCLR0=(1<<25)|(1<<26);
		IOSET1=(1<<31);
		delay();
		delay();
		delay();
		IOCLR1=(1<<31);
		delay();
		delay();
	}
	return 0;
}