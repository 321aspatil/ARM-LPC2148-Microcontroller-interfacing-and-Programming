//configure pll for CCLK=60MHz flash led after pll configured
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
void pllinit()
{
	PLLCFG=0x24;
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	//while(!(PLLSTAT&0x0400));
	//while(!(PLLSTAT&(1<<10)));
	while((PLLSTAT&(1<<10))==0);
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
}
int main()
{
	
	IODIR0|=(1<<4);
	pllinit();
	while(1)
	{
		IOSET0=(1<<4);
		delay();
		IOCLR0=(1<<4);
		delay();;
	}
}
