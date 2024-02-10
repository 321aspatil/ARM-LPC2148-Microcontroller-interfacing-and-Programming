#include <LPC213X.H>
int main()
{
	PINSEL0=(2<<4);
	T0CTCR=0x01;
	T0TCR=0x02;
	//T0PR=10;
	T0TCR=0x01;
	while(1){}
}
