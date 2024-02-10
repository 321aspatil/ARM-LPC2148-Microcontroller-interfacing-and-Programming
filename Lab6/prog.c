//VIRQ
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
void ext0isr(void)__irq
{
	IOSET0=(1<<4);
	delay();
	IOCLR0=(1<<4);
	delay();
	EXTINT=0x01;//(1<<0);
	VICVectAddr=00;

}
void ext1isr(void)__irq
{
	IOSET0=(1<<5);
	delay();
	delay();
	IOCLR0=(1<<5);
	delay();
	EXTINT=0x02;//(1<<1);
	VICVectAddr=00;
}
void isr_init()
{
	PINSEL0=(3<<2)|(3<<6);
	VICIntSelect|=(0<<14)|(0<<15);
	VICVectCntl0=(1<<5)|14;
	VICVectAddr0=(unsigned)ext0isr;
	VICVectCntl1=(1<<5)|15;
	VICVectAddr1=(unsigned)ext1isr;
	
	VICIntEnable=(1<<14)|(1<<15);//(3<<14);
}
int main()
{
	IODIR0=(1<<4)|(1<<5);
	isr_init();
	while(1);
	return 0;
}