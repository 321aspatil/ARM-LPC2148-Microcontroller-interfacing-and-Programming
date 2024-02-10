//Write an embedded c program to generate single edge PWM at PWM1 with duty cycle=65%
//req.delay=1/frequency
//req. delay=NOC/Pclk
//T(on) count=duty cycle*count
//T(total)=NOC
//Load T(total) in PWMMR0 and T(on) in other PWM match channel
#include <LPC213X.H>

int main()
{
	PINSEL0=(2<<0);
	PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	PWMTCR=0x02;
	PWMPR=2999;
	PWMMCR=0x02;
	PWMMR0=100;
	PWMMR1=65;
	PWMLER=(3<<0);
	PWMPCR=(1<<9);
	PWMTCR=(1<<3)|(1<<0);
	while(1); 
}
