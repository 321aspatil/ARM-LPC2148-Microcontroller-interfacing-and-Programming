#include <LPC213X.H>
void delay(void){
	unsigned int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<1000;j++);
	}	
}
void isr_int0(void)__irq
{
	IOSET0=0x10;
	delay();
	IOCLR0=0x10;
	delay();
	EXTINT=0x01;
	VICVectAddr=0x00;
}
void irq_init(void)
{
 	PINSEL0=0x0C;
	VICIntSelect=0x00;
	VICVectAddr0=(unsigned)isr_int0;
	VICVectCntl0=0x2E;
	VICIntEnable=0x4000;
}
int main(void)
{
 IODIR0|=0x10;
 irq_init();
 while(1);
}