//Flash LED connected at P0.4 using IOPIN register
/*#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<20000;i++);
}
int main()
{
	IODIR0=0x00000010;
	while(1)
	{
		IOPIN0=0x00000010;
		delay();
		IOPIN0=0x00000000;
		delay();
	}
	return 0;
}
*/
////Flash LED connected at P0.4 using IOSET and IOCLR register
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<20000;i++);
}
int main()
{
	IODIR0=0x00000010;
	while(1)
	{
		IOSET0=0x00000010;
		delay();
		IOCLR0=0x00000010;
		delay();
	}
	return 0;
}