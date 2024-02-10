#include <LPC213X.H>
int count=0;
void delay()
{
	unsigned int i;
	for(i=0;i<12750;i++);
}
void ext0int_isr()__irq
{
	long int temp=EXTINT;
	if((temp & 0x01))
	{
		++count;
		if(count>=10)
		{
			IOSET1=(1<<25);
			count=0; //led will be on every 10's place count like 10,20,30,40... 
		}
		else
		{
			IOCLR1=(1<<25);
		}
	}
	EXTINT=temp;
	VICVectAddr=0x00;
}
void ext1int_isr()__irq
{
	long int temp=EXTINT;
	if((temp & 0x02))
	{
//		if(IOSET1&(1<<26))
//		{
//			IOCLR1=(1<<26);
//		}
//		else
//		{
//			IOSET1=(1<<26);
//		}
		IOPIN1=IOPIN1^(1<<26);
	}
	EXTINT=temp;
	VICVectAddr=0x00;
}
void extint_init()
{
	PINSEL0=(3<<2)|(2<<28);
	VICIntSelect|=(0<<14)|(0<<15);
	VICVectCntl0=(1<<5)|14;
	VICVectAddr0=(unsigned)ext0int_isr;
	VICVectCntl1=(1<<5)|15;
	VICVectAddr1=(unsigned)ext1int_isr;
	EXTMODE=(3<<0);
	EXTPOLAR=(0<<0);
	VICIntEnable=(1<<14)|(1<<15);

}

int main()
{
   IODIR1|=(1<<25)|(1<<26)|(1<<31);
   extint_init();
   while(1)
   {
   		IOSET1=(1<<31);
		delay();
		IOCLR1=(1<<31);
		delay();
   }
}
