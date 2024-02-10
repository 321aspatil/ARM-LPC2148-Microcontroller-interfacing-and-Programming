//Toggle T0MR0 pin p0.3 (using T0EMR register)
//generate square wave using External Match Register
#include <lpc213x.h>
int main()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	IODIR0=(1<<3);//set P0.3 as output pin
	PINSEL0=(2<<6);//select Match 0 functionality of P0.3
	//T0PR=2999;//loading Prescale register to generate 1ms delay 
	T0MR0=1;//toggle after TC==50 i.e after 50ms delay
	T0TCR=0x02;//reset Timer Counter 0(both TC and PC)
	T0MCR=0x02;//reset Timer counter on match
	T0EMR=0x30;//set action as togglein EMR
	T0TCR=0x01;//Enable timer counter,i.e start	
	while(1)
	{
	 	
	}
}
