//NVIRQ example
#include <LPC213X.H>
void delay(void){
	unsigned int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<1000;j++);
	}	
}
void ext0isr(void)__irq
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
	//VICIntSelect=0x00;//selecting VIRQ
	VICDefVectAddr=(unsigned)ext0isr;
	VICIntEnable=(1<<14);
}
int main(void)
{
 IODIR0|=(1<<4);
 irq_init();
 while(1){
 	IOSET0=0x20;
 	delay();
 	IOCLR0=0x20;
 	delay();
 }
 return 0;
}