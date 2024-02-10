/*generate 10 frequency sawtooth wave on port P0.25 using DAC */
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
void msdelay(long int tms)
{
	T0CTCR=(0<<0);//Configure T0 as timer
	T0TCR=(0<<0);//Timer off
	T0PR=59999;//PR+1=Pclk/Ftimer        Ftimer=1/timer delay
	T0MR0=tms;
	T0MCR=0x04;//TC and PC will be stopped and Timer is disable if MR0 matches with TC
	T0TCR=(2<<0);//Timer reset
    T0TCR=(1<<0);//Timer ON
	while(T0MR0!=T0TC);//wait until timer counter matches the T0MR0
	T0TC=0;
}
void usdelay(long int tus)
{
	T0CTCR=(0<<0);//Configure T0 as timer
	T0TCR=(0<<0);//Timer off
	T0PR=59;//PR+1=Pclk/Ftimer        Ftimer=1/timer delay
	T0MR0=tus;
	T0MCR=0x04;//TC and PC will be stopped and Timer is disable if MR0 matches with TC 
	T0TCR=(2<<0);//Timer reset
    T0TCR=(1<<0);//Timer ON
	while(T0MR0!=T0TC);//wait until timer counter matches the T0MR0
	T0TC=0;
}
int main()
{
	int i;
	PINSEL1=0x00080000;//(2<<18);  //configuring port P0.25 as AOUT 
	pll_init();
	while(1)
	{
//	  	for(i=0;i<1023;i++)
//		{
//			DACR=i<<6;
//			usdelay(98);//for 10 Hz
//		}
		for(i=1022;i>0;i--)
		{
			DACR=i<<6;
			usdelay(98);
		}
	}
}
