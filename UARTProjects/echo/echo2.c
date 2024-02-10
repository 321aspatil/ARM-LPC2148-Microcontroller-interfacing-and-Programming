#include <LPC213X.H>
void init_serial (void);
int putchar (int ch);
int getchar (void);
unsigned char test;
int main(void)
{
	char *Ptr = "*** UART0 Demo ***\n\n\rType Characters to be echoed!!\n\n\r";
	VPBDIV = 0x02;
	init_serial();
	// Divide Pclk by two init_serial();
	while(1)
	{
		while (*Ptr)
		{
			putchar(*Ptr++);
		}
		putchar(getchar());// Echo terminal
	}
}
void init_serial (void)
{
	PINSEL0 = 0x05;
	U0FCR = 0x07;
	U0LCR = 0x83;
	U0DLL = 0xC0;
	U0DLM = 0x00;
	U0LCR = 0x03;
}
int putchar (int ch)
{
	while (!(U0LSR & 0x20));
	return (U0THR = ch);
}
int getchar(void)
{
	while (!(U0LSR & 0x01));
	return (U0RBR);
}

