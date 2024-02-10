//Flashing LEDS connected at ports P0.4,P0.5,P0.,P0.6,P0.7 alternatively using IOPIN regiser
/*#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<20000;i++);
}
int main()
{
	IODIR0=0x000000F0;
	while(1)
	{
		IOPIN0=0x000000A0;
		delay();
		IOPIN0=0x00000050;
		delay();
	}
	return 0;
}
*/
//Flashing LEDS connected at ports P0.4,P0.5,P0.,P0.6,P0.7 alternatively using IOSET and IOCLR regiser
/*#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<20000;i++);
}
int main()
{
	IODIR0=0x000000F0;
	while(1)
	{
		IOSET0=0x000000A0;
		delay();
		IOCLR0=0x000000A0;
		delay();
		IOSET0=0x00000050;
		delay();
		IOCLR0=0x00000050;
		delay();
	}
	return 0;
}
*/
////Flashing LEDS connected at ports P0.4,P0.5,P0.,P0.6,P0.7  in running mode
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<20000;i++);
}
int main()
{
	IODIR0=0x000000F0;
	while(1)
	{
		IOPIN0=0x00000010;
		delay();
		IOPIN0=0x00000020;
		delay();
		IOPIN0=0x00000040;
		delay();
		IOPIN0=0x00000080;
		delay();
	}
	return 0;
}