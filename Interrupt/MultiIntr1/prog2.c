/*
Write an embedded c program to perform following:
1)Square wave generation on P0.4 using external interrupt 0 low level sensitive FIQ
2)Reactangular wave generation on P0.5 using external interrupt 1 low level sensitive VIRQ falling edge sensitive
3)Toggle P0.6 using external interrupt 2 rising edge sensitive NVIRQ
*/
#include <LPC213X.H>
void delay(unsigned int j)
{
	unsigned int i;
	for(i=0;i<1275*j;i++);
}
void FIQ_Handler(void)__irq
{
	 IOSET0=(1<<4);
	 delay(10);
	 IOCLR0=(1<<4);
	 delay(10);
	 EXTINT=0x01;
}
void ext1_isr(void)__irq
{
	 IOSET0=(1<<5);
	 delay(20);
	 IOCLR0=(1<<5);
	 delay(10);
	 EXTINT=0x02;
	 VICVectAddr=0x00;
}
void ext2_isr(void)__irq
{
	 long int temp=EXTINT;
	 if((temp&0x04))
	 {
	 	if(IOSET0 & (1<<6))
		{
			IOCLR0=(1<<6);
		}
		else
		{
		   IOSET0=(1<<6);
		}		
	 }
	 EXTINT=temp;
	 VICVectAddr=0x00;
}
void ext_init()
{
	PINSEL0|=(3<<2)|(3<<6)|(3<<14);
	VICIntSelect|=(1<<14)|(0<<15)|(0<<16);
	VICVectCntl0=(1<<5)|15;
	VICVectAddr0=(unsigned)ext1_isr;
	VICDefVectAddr=(unsigned)ext2_isr;
	EXTMODE=0x06;
	EXTPOLAR=0x04;
	VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}
int main()
{
	IODIR0|=(7<<4);
	ext_init();
	while(1);
	return 0;
}