//Timer as counter
#include <LPC213X.H> 
void pll()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;

}
int main()
{
   pll();
   PINSEL0=(2<<4);
   T0CTCR=(1<<0);//TC value incremented on Rising edge
   //T0CTCR=(1<<1);//TC value incremented on Falling edge
   T0TCR=0x02;
   T0TCR=0x01;
   while(1);
}
