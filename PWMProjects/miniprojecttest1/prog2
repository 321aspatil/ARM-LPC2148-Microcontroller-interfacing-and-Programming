//Write an embedded c program to generate single edge PWM at PWM1 with duty cycle=65%
//req.delay=1/frequency
//req. delay=NOC/Pclk
//T(on) count=duty cycle*count
//T(total)=NOC
//Load T(total) in PWMMR0 and T(on) in other PWM match channel
#include <LPC213X.H>
void pll()
{
	PLLCFG=0x60;
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	while(!(PLLSTAT &(1<<10)));
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x01;
	//PCLK=3MHz
}

void setpwm()
{
	IOSET0=(1<<4);
	PWMPCR=(1<<9);
	PWMPR=11999;
	PWMMCR=0x02;
	PWMMR0=100;
	PWMMR1=10;
	PWMLER=(1<<1);
	PWMTCR=0x02;
	PWMTCR=(1<<3)|(1<<0);
}
void ext0isr()__irq
{
	setpwm();
	EXTINT=(1<<0);
	VICVectAddr=0x00;
}
int main()
{
	PINSEL0=(2<<0)|(1<<16);
	VICVectCntl0=1<<5|14;
	VICVectAddr0=(unsigned)ext0isr;
	VICIntEnable=(1<<14);
	pll();
	IODIR0=(1<<4);
	while(1)
	{
	 
	}
}
