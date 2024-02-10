#include <LPC213X.H>
unsigned long int x;
int main()
{
	PINSEL1=0x0400;//set P0.21 as PWM5
	PWMMR0=0x0F;//Period Register
	PWMMR5=0x00;//Duty Cycle Register
	PWMMCR=0x03;//PWMMR0=0;if PWMMR=PWMTC,set Intrrupt flag
	PWMPCR=0x00002000;//PWM5 output enabled
	PWMTCR=0x00000009;//PWM and Counter Enabled
	PWMLER=0x00000020;//LER Configured
	while(1)
	{
		while(PWMIR!=0x00000001);//wait here until interrupt
		PWMIR=0x01;//clear interrupt register
		PWMMR5=x;
		if(x>PWMMR0)
		{
			x=0;
		}
		x=x+1;//increasing duty cycle by 1
		PWMLER=0x00000020; //LER configured
	}
}
