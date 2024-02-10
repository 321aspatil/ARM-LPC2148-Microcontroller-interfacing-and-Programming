#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
void extint0()__irq
{
	IOSET0=1<<4;
	delay();
	IOCLR0=1<<4;
	delay();
	EXTINT=0x01;
	VICVectAddr=0x00;
}
void extint_init()
{
	PINSEL0=(3<<2);
	VICIntSelect=(0<<14);
	VICDefVectAddr=(unsigned)extint0;
	VICIntEnable=(1<<14);
}
int main()
{
	IODIR0|=(1<<4);
	extint_init();
	while(1);
}
