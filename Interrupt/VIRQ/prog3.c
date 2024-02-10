#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
void FIQ_Handler(void)__irq
{
	IOSET0=1<<4;
	delay();
	IOCLR0=1<<4;
	delay();
	EXTINT=0x01;
}
void extint_init()
{
	PINSEL0=(3<<2);
	VICIntSelect=(1<<14);
	VICIntEnable=(1<<14);
}
int main()
{
	IODIR0|=(1<<4);
	extint_init();
	while(1);
}
