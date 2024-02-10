#include <LPC213X.H>
unsigned int data[] = {512, 644, 768, 874, 955, 1006, 1023, 1006, 955, 874, 768, 644,512};
void delay(int wt)
{
    T0CTCR=0X0000;          //Timer Mode
    T0PR=2999;                 //Prescaler Value
    T0MR0=wt;                 //Match Register Value
    T0MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
    T0TCR=0X02;                 //Reset Timer
    T0TCR=0X01;                 //Timer ON
    while(T0TC!=T0MR0);
    T0TC=0;                         //Timer OFF
}
int main()
{	
	unsigned int i=0;
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	PINSEL1 = (2<<18);
	while(1)
	{
	
			DACR=0<<6;
			delay(20);
			DACR=512<<6;
			delay(20);
		for(i=0;i<=12;i++)
		{	
			DACR = (data[i]<<6);
			delay(2);
		}
			DACR=512<<6;
			delay(20);
//			DACR=0<<6;
//			delay(20);
		
		}
}

