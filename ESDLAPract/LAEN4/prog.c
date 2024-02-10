#include <LPC213X.H>
unsigned char data[]={0x06,0x5B,0x4F};
unsigned char con[]={0x03,0x05,0x06};
void delay(unsigned int time)
{
	unsigned long int i;
	for(i=0;i<1275*time;i++);
}
void FIQ_Handler()__irq
{
	IOPIN0=(con[0]<<16)|(data[0]<<0);
	delay(20);
	EXTINT=0x02;
}
void ext2isr()__irq
{
	IOPIN0=(con[1]<<16)|(data[1]<<0);
	delay(20);
	EXTINT=0x04;
	VICVectAddr=00;
}
void ext3isr()__irq
{
	IOPIN0=(con[2]<<16)|(data[2]<<0);
	delay(20);
	EXTINT=0x08;
	VICVectAddr=00;
}
void isr_init()
{
	PINSEL0=(2<<28)|(2<<30);
	PINSEL1=(2<<28);
	VICIntSelect|=(1<<15)|(0<<16)|(0<<17);
	VICVectCntl6=(1<<5)|16;
	VICVectAddr6=(unsigned)ext2isr;
	VICDefVectAddr=(unsigned)ext3isr;
	VICIntEnable=(1<<15)|(1<<16)|(1<<17);
}
int main()
{
	unsigned int i;
	IODIR0=(0xFF<<0)|(7<<16);
	IODIR1=(1<<31);
	isr_init();
	while(1)
	{
		for(i=0;i<3;i++)
		{
			IOPIN0=(con[i]<<16)|(0x00<<0);	
		}
		IOSET1=(1<<31);
		delay(100);
		IOCLR1=(1<<31);
		delay(200);
		EXTINT=0x08;
		EXTINT=0x04;
		EXTINT=0x02;	
	}
}

