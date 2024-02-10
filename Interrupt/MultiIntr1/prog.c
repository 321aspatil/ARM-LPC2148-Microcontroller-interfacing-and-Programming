/*
Write an embedded c program to perform task1,task2 and task3 using external interrupt 0,1 and 2 respectively.
configure ext0 as VIRQ,ext1 as NVIRQ and ext2 as FIQ
*/
#include <LPC213X.H>
void delay(unsigned int j)
{
	unsigned int i;
	for(i=0;i<1275*j;i++);
}
void ext0_isr(void)__irq
{
	 IOSET0=(1<<4);
	 delay(10);
	 IOCLR0=(1<<4);
	 delay(10);
	 EXTINT=0x01;
	 VICVectAddr=0x00;
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
void FIQ_Handler(void)__irq
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
}
void ext_init()
{
	PINSEL0|=(3<<2)|(3<<6)|(3<<14);
	VICIntSelect|=(0<<14)|(0<<15)|(1<<16);
	VICVectCntl0=(1<<5)|14;
	VICVectAddr0=(unsigned)ext0_isr;
	VICDefVectAddr=(unsigned)ext1_isr;
	//EXTMODE=(1<<2);
	EXTPOLAR=0x00;
	VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}
int main()
{
	IODIR0|=(7<<4);
	ext_init();
	while(1);
}
