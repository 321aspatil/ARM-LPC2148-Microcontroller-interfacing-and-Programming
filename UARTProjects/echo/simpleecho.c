#include <LPC213X.H>
void init_UART0()
{
	PINSEL0=0x05;//(5<<0);
  U0FCR=0x07;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0x00;
	U0LCR=0x03;
}
int main()
{
	init_UART0();
	while(1)
	{
	unsigned char byte;
	while(!(U0LSR & 0x01));
	byte=U0RBR;
	U0THR=byte;
	while(!(U0LSR &(1<<6)));
	}
}
