/*
write an ebedded c program to blink led connnected at port P1.31.connect a switch at port P0.1 and configure it for external interrupt 0 as falling edge sensitive virq.
on occurance of interrupt display the count on ccssd.
*/
#include <LPC213X.H>
int count=0;
unsigned char data[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void delay()
{
	unsigned int i;
	for(i=0;i<60000;i++);
}
void isr_ext0(void)__irq
{
	 long int temp;
	 temp=EXTINT;
	 if((temp&0x01)==1)
	 {
		if(count>9)
		{
		  count=0;
		}
				{
					IOPIN0=(data[count]<<16);
					delay();
				}
				++count;
	}
	 EXTINT=temp;
	 VICVectAddr=0x00;
}
void irq_init()
{
	PINSEL0=(3<<2);
	VICIntSelect=0x00;
	VICVectCntl0=(1<<5)|14;
	VICVectAddr0=(unsigned)isr_ext0;
	VICIntEnable=(1<<14);
	EXTMODE|=0x01;
	EXTPOLAR|=0x00;
}
int main()
{
	IODIR1=(1<<31);
	IODIR0=0xFF<<16;
	irq_init();
	while(1)
	{
		IOSET1=(1<<31);
		delay();
		IOCLR1=(1<<31);
		delay();
		delay();
		delay();
	}
	return 0;
}