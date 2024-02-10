#include <LPC213X.H>
int count=0;
void delay()
{
	unsigned int i;
	for(i=0;i<10000;i++);
}
void isr_ext0(void)__irq
{
	 long int temp;
	 temp=EXTINT;
	 if((temp&0x01)==1)
	 {
	 	if(count>=10)
		{
		  IOSET1=(1<<25);
		}
		else
		{
			IOCLR1=(1<<25);
			count++;
		}
	 }
	 EXTINT=temp;
	 VICVectAddr=0x00;
}
void irq_init()
{
	PINSEL0=(3<<2);
	//VICIntSelect=0x00;
	VICVectCntl0=(1<<5)|14;
	VICVectAddr0=(unsigned)isr_ext0;
	EXTMODE|=0x01;
	EXTPOLAR|=0x00;
	VICIntEnable=(1<<14);
}
int main()
{
	IODIR1=(1<<25)|(1<<31);
	irq_init();
	while(1)
	{
		IOSET1=(1<<31);
		delay();
		IOCLR1=(1<<31);
		delay();
	}
}
