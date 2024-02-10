//Write an embedded c program to generate single edge PWM at PWM1 with duty cycle=40% and frequency=500Hz,Pclk=12MHz
//req.delay=1/frequency
//Period count(Pcount)=req.delay*Pclk
//T(on) count=duty cycle*Pcount
//T(total)=Pcount
//Load T(total) in PWMMR0 and T(on) in other PWM match channel
#include <LPC213X.H>

int main()
{
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x01;
	PINSEL0=(2<<0);
	PWMTCR=0x02;
	PWMMR0=24000;
	PWMMR1=9600;
	PWMMCR=0x02;
	PWMLER=(3<<0);
	PWMPCR=(1<<9);
	PWMTCR=(1<<3)|(1<<0);
	while(1); 
}
