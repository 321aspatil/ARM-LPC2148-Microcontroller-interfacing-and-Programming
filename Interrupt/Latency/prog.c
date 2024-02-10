//Find latency of FIQ,VIRQ and NVIRQ
//FIQ=0.33us
#include <LPC213X.H>
void FIQ_Handler(void)__irq
{
	IOCLR0=1<<4;
	EXTINT=1<<0;
}
void ext1isr()__irq
{
	IOCLR0=1<<5;
	EXTINT=1<<1;
	VICVectAddr=00;
}
void ext2isr()__irq
{
	IOCLR0=1<<6;
	EXTINT=1<<2;
	VICVectAddr=00;
}
void isrinit()
{
	PINSEL0=(3<<2)|(3<<6)|(3<<14);
	VICIntSelect=(1<<14);
	VICVectCntl0=(1<<5)|15;
	VICVectAddr0=(unsigned)ext1isr;
	VICDefVectAddr=(unsigned)ext2isr;
//EXTMODE=(1<<0)|(1<<1)|(1<<2);
	VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}
int main()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x01;
	IODIR0=(7<<4);
	IOPIN0=7<<4;
	isrinit();
	while(1)
	{
	}
}
