//Transmit character
#include <LPC213X.H>
#include"UART.h"
void delay()
{
	int i;
	for(i=0;i<200;i++);
}
int main()
{
	initUART();
	while(1)
	{
		strUART("WCE SANGLI");
		delay();
	}
}
