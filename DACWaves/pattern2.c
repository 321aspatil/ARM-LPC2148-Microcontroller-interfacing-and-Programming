#include <LPC213X.H>
unsigned int data[] = {512, 644, 768, 874, 955, 1006, 1023, 1006, 955, 874, 768, 644,512};
void delay(int wt)
{
    T0CTCR=0X0000;          //Timer Mode
    //T0PR=29;                 //Prescaler Value
    T0MR0=30*wt;                 //Match Register Value
    T0MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
    T0TCR=0X02;                 //Reset Timer
    T0TCR=0X01;                 //Timer ON
    while(T0TC!=T0MR0);
    T0TC=0;                         //Timer OFF
}

int main()
{	
	unsigned int i=0;
	VPBDIV=0x01;
	PINSEL1 = (2<<18);
	while(1)
	{

			DACR=0<<6;
			delay(50*1000);
			DACR=512<<6;
			delay(50*1000);
		for(i=512;i<1024;i++)
		{	
			DACR = i<<6;
			delay(98);
		}
		for(i=1023;i>513;i--)
		{	
			DACR =i<<6;
			delay(98);
		}
			DACR=512<<6;
			delay(50*1000);
//			DACR=0<<6;
//			delay(50*1000);
		}
}

