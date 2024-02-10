/*write an embedded c program to operate DC motor in either direction on occurance of an interrupt.
use nvirq.meantime generate reactangular wave on port p1.31*/
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<12750;i++);
}
void extisr()__irq
{
	long int temp=EXTINT;
	if(temp & 0x01)
	{
		IOSET0=(1<<26);
		IOCLR0=(1<<25);
		delay();
	}
	else if(temp & 0x02)
	{
		IOSET0=(1<<25);
		IOCLR0=(1<<26);
		delay();
	}
	EXTINT=temp;
	VICVectAddr=00;
}

void isrinit()
{
	  PINSEL0=(3<<2)|(3<<6);
	  VICIntSelect=0x00;
	  VICDefVectAddr=(unsigned)extisr;
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
		IOCLR1=(1<<31);
		delay();
	}
	return 0;
}