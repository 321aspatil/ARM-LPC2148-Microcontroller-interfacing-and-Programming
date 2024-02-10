/*
for Pclk=12MHz
generate 1KHz square wave at P0.15
T=1/f=1/1KHz=1ms
Ton=500ms
Toff=500ms 
*/
#include <LPC213X.H>
void pll_init()
{
	PLLCFG=0x24;//CCLK=60MHz
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	while(!(PLLSTAT &(1<<10)));
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x01;//PCLK=CCLK
}
void msdelay(unsigned int tms)
{
	T0CTCR=(0<<0);//Configure T0 as timer
	T0TCR=(0<<0);//Timer off
	T0PR=59999;//PR+1=Pclk/Ftimer        Ftimer=1/timer delay
	T0TC=0;//Reset timer
	T0TCR=(2<<0);//Timer reset
  T0TCR=(1<<0);//Timer ON
	while(T0TC<tms);//wait until timer counter reaches the desired delay
	T0TCR=(0<<0);//Disable timer
}
void usdelay(unsigned int tus)
{
	T0CTCR=(0<<0);//Configure T0 as timer
	T0TCR=(0<<0);//Timer off
	T0PR=59;//PR+1=Pclk/Ftimer        Ftimer=1/timer delay
	T0TC=0;//Reset timer
	T0TCR=(2<<0);//Timer reset
  T0TCR=(1<<0);//Timer ON
	while(T0TC<tus);//wait until timer counter reaches the desired delay
	T0TCR=(0<<0);//Disable timer
}
int main()
{
	IODIR0=(1<<15);
	pll_init();
	while(1)
	{
		IOSET0=(1<<15);
		usdelay(1);
		IOCLR0=(1<<15);
		usdelay(1);
	}
}
