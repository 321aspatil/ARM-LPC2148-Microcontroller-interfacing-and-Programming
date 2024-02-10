#include <LPC213X.H>
unsigned int data[] = {512, 644, 768, 874, 955, 1006, 1023, 1006, 955, 874, 768, 644,512};
void delay(int wtime)
{
	T0TCR=0x02;
	//T0PR=59;
	T0MR0=60*wtime;
	T0MCR=0x04;
	T0TCR=0x01;
	while(T0TC!=T0MR0);
	T0TC=0;
}
int main()
{
	unsigned int i;
	VPBDIV=0x01;
	PINSEL1=0x00080000;//P0.25 as AOUT pin
	while(1)
	{
		DACR=512<<6;
	delay(16.66*1000);
	for(i=512;i<1024;i++)
	{
			DACR=i<<6;
			delay(8);
	}
	for(i=1023;i>=512;i--)
	{
			DACR=i<<6;
			delay(8);
	}
	DACR=512<<6;
	delay(16.66*1000);
	for(i=0;i<13;i++)
	{
		DACR=data[i]<<6;
		delay(1.28*1000);
	}
	DACR=512<<6;
	delay(16.66*1000);
	DACR=0<<6;
	delay(16.66*1000);
	}
}
