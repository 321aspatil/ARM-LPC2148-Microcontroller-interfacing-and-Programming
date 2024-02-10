/*
write an embedded c program to generate dual edge PWM using PWM2(2nd flip flop) duty cycle=75% and frequency=500
*/
//req.delay=1/frequency
//req. delay=NOC/Pclk
//T(on) count=duty cycle*count
//T(total)=NOC
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
	PWMMR0=6000;
	PWMMR1=1000;
	PWMMR2=5500;
	PWMMCR=0x02;
	PWMLER=(7<<0);
	PWMPCR=(1<<10)|(1<<2);
	PWMTCR=(1<<3)|(1<<0);
	while(1); 
}
