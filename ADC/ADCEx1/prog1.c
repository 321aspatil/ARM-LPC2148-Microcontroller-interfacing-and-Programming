//simple ADC program
#include <LPC213X.H>
void delay()
{
	unsigned int i;	
	for(i=0;i<1275;i++);
}
int main()
{
	int value;
	IODIR0=1<<4;
	PINSEL0=3<<20;
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	AD1CR=0x00200402;
	while(1)
	{
		AD1CR|=(1<<24);
		while((AD1GDR&0x80000000)==0);
		value=(AD1GDR>>6)&0x3FF;
		if(value==0x1D1)
		{
			IOSET0=1<<4;
		}
		else
		{
			IOCLR0=1<<4;
		}
	}
	
}
