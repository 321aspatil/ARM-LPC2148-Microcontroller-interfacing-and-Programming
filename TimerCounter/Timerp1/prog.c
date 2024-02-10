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
void delay(unsigned int time)
{
	unsigned int i=0;
	while(time>i)
	{
		i++;
	}
}
void msdelay(int tms)
{
	T0CTCR=0X0000;          //Timer Mode
  T0PR=59999;                 //Prescaler Value
  T0MR0=tms;                 //Match Register Value
  T0MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
  T0TCR=0X02;                 //Reset Timer
  T0TCR=0X01;                 //Timer ON
  while(T0TC!=T0MR0);
  T0TC=0;                         //Timer OFF
}
void usdelay(int tus)
{
	T0CTCR=0X0000;          //Timer Mode                //Prescaler Value
  T0MR0=60*tus;                 //Match Register Value
  T0MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
  T0TCR=0X02;                 //Reset Timer
  T0TCR=0X01;                 //Timer ON
  while(!(T0TC==T0MR0));
  T0TC=0;                         //Timer OFF
}
int main()
{
	IODIR0=(1<<4);
 pll_init();
	while(1)
	{
		IOSET0=(1<<4);
		usdelay(10);
		IOCLR0=(1<<4);
		usdelay(10);
	}
}
