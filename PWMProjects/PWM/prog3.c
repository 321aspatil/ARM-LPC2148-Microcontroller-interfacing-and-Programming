/*
write an embedded c program to generate dual edge PWM using PWM2(2nd flip flop) duty cycle=50%
*/
//req.delay=1/frequency
//Period count(Pcount)=req.delay*Pclk
//T(on) count=duty cycle*Pcount
//T(total)=Pcount
//Duty cycle=(MR2-MR1)/MR0
//Load T(total) in PWMMR0 and T(on) counts in other 2 PWM match channels which are <PWMMR0
#include <LPC213X.H>
int main()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;	
	PINSEL0=(2<<14);
	PWMTCR=0x02;
	//PWMPR=2999;  //if PR is used(period 1sec)
	//PWMMR0=1000;
	//PWMMR1=100;
	//PWMMR2=600;
	PWMMR0=3000;//without PR(period 1ms)
	PWMMR1=100;
	PWMMR2=1600;
	PWMMCR=0x02;
	PWMLER=(7<<0);
	PWMPCR=(1<<10)|(1<<2);
	PWMTCR=(1<<3)|(1<<0);
	while(1); 
}
