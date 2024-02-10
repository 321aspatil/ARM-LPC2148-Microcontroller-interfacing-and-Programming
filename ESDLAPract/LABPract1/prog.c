//Displaying the count occurance of Interrupt type on Terminal
#include <LPC213X.H>
#include <stdio.h>
int ext1count=0,ext2count=0,ext3count=0;
char extcounts[80];
void delay()
{
	unsigned int i;
	for(i=0;i<6000;i++);
}
void URAT_init()
{
	//PINSEL0=0x05;//(5<<0);
	U0LCR=0x83;
	U0DLL=19;
	U0DLM=00;
	U0LCR=0x03;
}
void send_Char(char ch)
{
	U0THR=ch;
	while(!(U0LSR&(1<<6)));
}
char recv_Char()
{
	while(!(U0LSR&0x01));
	return U0RBR;
}
void send_Str(char *msg)
{
	int i=0;
	while(msg[i])
	{
		send_Char(msg[i]);
		i++;
	}
}
void FIQ_Handler(void)__irq
{
	ext1count++;
	sprintf(extcounts,"\rFIQ Count=%d\nVIRQ Count=%d\nNVIRQ Count=%d\r",ext1count,ext2count,ext3count);
	send_Str("\033[2J");
	send_Str("\033[H");
	send_Str(extcounts);
	EXTINT=(1<<1);
}
void ext2isr()__irq
{
	ext2count++;
	sprintf(extcounts,"\rFIQ Count=%d\nVIRQ Count=%d\nNVIRQ Count=%d\r",ext1count,ext2count,ext3count);
	send_Str("\033[2J");
	send_Str("\033[H");
	send_Str(extcounts);
	EXTINT=(1<<2);
	VICVectAddr=00;
}
void ext3isr()__irq
{
	ext3count++;
	sprintf(extcounts,"\rFIQ Count=%d\nVIRQ Count=%d\nNVIRQ Count=%d\r",ext1count,ext2count,ext3count);
	send_Str("\033[2J");
	send_Str("\033[H");
	send_Str(extcounts);
	EXTINT=(1<<3);
	VICVectAddr=00;
}
void isrinit()
{
	PINSEL0=0x000CC0C5;
	VICIntSelect=(1<<15);
	VICVectCntl0=(1<<5)|16;
	VICVectAddr0=(unsigned)ext2isr;
	VICDefVectAddr=(unsigned)ext3isr;
	EXTMODE=(1<<1)|(1<<2)|(1<<3);
	VICIntEnable=(1<<15)|(1<<16)|(1<<17);	
}
int main()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	isrinit();
	URAT_init();
	send_Str("Displaying Counts of Ocuurances of Interrupt Types Through UART\n");
	while(1)
	{
		
	}
}
