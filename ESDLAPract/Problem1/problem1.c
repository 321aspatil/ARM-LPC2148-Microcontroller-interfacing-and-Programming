/*Operate DC motor in any direction when external interrupt 2  occurs and display help on ccssd multiplexed display 
when external interrupt 3 occurs.configure both interrupts as level sensitive virq assign highest priority to external interrupt 2
*/
#include <LPC213X.H>
unsigned char data[]={0xF6,0xF9,0xB8,0xF3};
unsigned char con[]={0x0E,0x0D,0x0B,0x07};
void delay(unsigned int count)
{
	unsigned int i,j;
	for(j=0;j<count;j++)
	{
		for(i=0;i<50000;i++);
	}
}
void ext2isr()__irq
{
	  IOSET0=(1<<25);
	  delay(5);
	  delay(5);
	  delay(5);
	  EXTINT=0x04;
	  VICVectAddr=00;	  
}
void ext3isr()__irq
{
		unsigned int i;
		for(i=0;i<4;i++)
		{
			  IOPIN0=(con[i]<<16)|(data[i]<<0);
			  delay(10);
		}
	 	EXTINT=0x08;
	    VICVectAddr=00;
}
void isr_init()
{
	PINSEL0=(2<<30);
	PINSEL1=0x20000000;
	VICIntSelect=(0<<16)|(0<<17);
	VICVectCntl0=(1<<5)|16;
	VICVectAddr0=(unsigned)ext2isr;
	VICVectCntl1=(1<<5)|17;
	VICVectAddr1=(unsigned)ext3isr;
	VICIntEnable=(1<<16)|(1<<17);
}

int main()
{
	IODIR0=(0x7F<<0)|(0xF<<16)|(1<<25);
	isr_init();
	while(1)
	{	
		unsigned int i;
		for(i=0;i<4;i++)
		{
			  IOPIN0=(con[i]<<16)|(0x00<<0);
			  delay(10);
		}
		IOCLR0=(1<<25);

	}
}
