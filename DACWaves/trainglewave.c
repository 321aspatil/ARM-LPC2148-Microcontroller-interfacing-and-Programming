#include <LPC213X.H>
void delay(int wt)
{
    T0CTCR=0X0000;          //Timer Mode
    T0PR=2;                 //Prescaler Value
    T0MR0=wt;                 //Match Register Value
    T0MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
    T0TCR=0X02;                 //Reset Timer
    T0TCR=0X01;                 //Timer ON
    while(T0TC!=T0MR0);
    T0TC=0;                         //Timer OFF
}
int main()
{	unsigned int i=0;
	PINSEL1 = (2<<18);
	while(1)
	{	
		for(i=0;i<1024;i++)
		{
			DACR=i<<6;
			delay(48);
		}
		for(i=1023;i>0;i--)
		{
			DACR=i<<6;
			delay(48);
		}
  }
}

