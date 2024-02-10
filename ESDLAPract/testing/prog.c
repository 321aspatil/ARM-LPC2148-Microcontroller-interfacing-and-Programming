#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<12750;i++);
}
int main()
{
	IODIR0=(1<<0);
	while(1)
	{
		IOSET0=(1<<0);
		delay();
		IOCLR0=(1<<0);
		delay();
	}
}
