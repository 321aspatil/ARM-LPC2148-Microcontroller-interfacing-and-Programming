#include <LPC213X.H>
unsigned char data1[]={0xF6,0xF9,0xB8,0xF3};
unsigned char data2[]={0xF3,0xB8,0xF9,0xF6};
unsigned char con[]={0x0E,0x0D,0x0B,0x07};
void delay(unsigned int t)
{
	  unsigned int i,j;
	  for(j=0;j<t;j++)
	  {
	  	for(i=0;i<1200;i++);
	  }
} 
void ext0isr()__irq
{
	long int temp;
	temp=EXTINT;
	if(VICIRQStatus & (1<<15))
	{
		unsigned int i;
		for(i=0;i<4;i++)
		{
			IOPIN0=(con[i]<<16)|(data1[i]<<0);
			delay(40);
		}
	}
	else if(VICIRQStatus & (1<<16))
	{
		unsigned int i;
		for(i=0;i<4;i++)
		{
			IOPIN0=(con[i]<<16)|(data2[i]<<0);
			delay(40);
		}
	}
	EXTINT=temp;
	VICVectAddr=00;
}
void isr_init()
{
	PINSEL0=(2<<28)|(2<<30);
	VICIntSelect=00;
	VICDefVectAddr=(unsigned)ext0isr;
	VICIntEnable=(1<<15)|(1<<16);
}
int main()
{
	IODIR0=(0xFF<<0)|(0xFF<<16)|(1<<25);
	isr_init();
	while(1)
	{
		IOCLR0|=(0xFF<<0)|(0xFF<<16);
		IOSET0=(1<<25);
		delay(50);
		IOCLR0=(1<<25);
		delay(100);
	}
}

