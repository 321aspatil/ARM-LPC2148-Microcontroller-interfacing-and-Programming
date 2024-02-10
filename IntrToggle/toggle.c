/*
write an embedded c program to toggle port P0.4 using external interrupt 0.
configure external interrupt 0 as rising edge  sensitive NVIRQ
*/
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<1275*10;i++);
}
void ext0_isr(void)__irq
{
	static int i=0;
	IOPIN0=IOPIN0^(1<<4);
	EXTINT=0x01;
	VICVectAddr=0x00;
}
void ext0_init()
{
	PINSEL0=(3<<2);
	VICIntSelect|=(0<<14);
	VICDefVectAddr=(unsigned)ext0_isr;
	EXTMODE=0x01;
	EXTPOLAR=0x01;
	VICIntEnable=(1<<14);
} 
int main()
{
	IODIR0|=(1<<4);
	ext0_init();
	while(1);
}
