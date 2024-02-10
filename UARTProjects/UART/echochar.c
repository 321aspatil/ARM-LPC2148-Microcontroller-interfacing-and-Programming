#include <LPC213X.H>
void delay()
{
	int i;
	for(i=0;i<5000;i++);
}
void init_UART0()
{
	PINSEL0=0x05;//(5<<0);
  U0FCR=0x07;
	U0LCR=0x83;
	U0DLL=20;
	U0DLM=0x00;
	U0LCR=0x03;
}
int main()
{
	init_UART0();
	while(1)
	{
	unsigned char byte;
	U0FCR=0x07;
	while(!(U0LSR & (1<<1)));
	byte=U0RBR;
	U0THR=byte;
	while(!(U0LSR &(1<<6)));
	delay();
	}
}
