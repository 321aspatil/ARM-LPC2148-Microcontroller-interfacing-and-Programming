//FIQ eample
#include <LPC213X.H>
void delay(void){
	unsigned int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<1000;j++);
	}	
}
void FIQ_Handler(void)__irq
{
	IOSET0=0x10;
	delay();
	IOCLR0=0x10;
	delay();
	EXTINT=0x01;
}
void isr_init(void)
{
 	PINSEL0=0x0C;
	VICIntSelect|=(1<<14);//selecting FIQ
	VICIntEnable=(1<<14);
}
int main(void)
{
 IODIR0|=(1<<4);
 isr_init();
 while(1);
 return 0;
}
