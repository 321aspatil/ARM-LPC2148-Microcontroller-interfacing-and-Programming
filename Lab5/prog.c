#include <LPC213X.H>
void delay()
{
	   unsigned int i;
	   for(i=0;i<1275;i++);
}
void isr_ext0()__irq
{
	   IOSET0=(1<<4);
	   delay();
	   IOCLR0=(1<<4);
	   delay();
	   EXTINT=(1<<0);//clear flag bit
	   VICVectAddr=00;//Indicating end of isr
}
void init_extint()
{
	 PINSEL0=(3<<2);
	 VICIntSelect=(0<<14);
	 //VICIntSelect=VICIntSelect|(0<<14);
	 VICVectAddr0=(unsigned)isr_ext0;
	 VICVectCntl0=(1<<5)|14;
	 //EXTMODE=(1<<0);	//EXTMODE for Selecting between Level and Edge Sensitivity
	 //EXTMODE=(0<<0);
	 //EXTPOLAR=(1<<0);	//EXTPOLAR for Selecting between high/rising or Low/falling
	 //EXTPOLAR=(0<<0);
	 VICIntEnable=(1<<14);

}
int main()
{
   IODIR0=(3<<4);
   init_extint();
   while(1){
   		IOSET0=(1<<5);
		delay();
		IOCLR0=(1<<5);
		delay();
   }
   return 0;
}
