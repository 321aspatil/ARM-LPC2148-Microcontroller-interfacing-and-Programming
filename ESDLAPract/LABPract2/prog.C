/*with the help of 3 switch control create pwm on pwm1 with 25%,50% and 75% duty cycle.the freuecy of wave is 100Hz.
also display duty cycle on multiplexed seven segment display respectively for duty cycle
*/
#include <LPC213X.H>
unsigned char data[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void delay()
{
	unsigned int i;
	for(i=0;i<5000;i++);
}
int main()
{
	PINSEL0=0x00080000;
	PWMTCR=0x02;
	PWMMR0=30000;
	PWMMR6=3000;
	PWMMCR=0x02;
	PWMLER=(1<<0)|(1<<6);
	PWMPCR=(1<<9)|(1<<14);
	PWMTCR=(1<<3)|0x01;
	while(1)
	{
		if(!(IOPIN0&(1<<13)))
		{
			  PWMMR6=7500;
				PWMLER=(1<<6);
				while(!(IOPIN0&(1<<13)))
				{
					IOPIN0=data[1]<<0;
					delay();
				}
				PWMMR6=3000;
				PWMLER=(1<<6);
		}
		if(!(IOPIN0&(1<<14)))
		{
			 PWMMR6=15000;
			 PWMLER=(1<<6);
			 while(!(IOPIN0&(1<<14)))
				{
					IOPIN0=data[2]<<0;
					delay();
				}
			 PWMMR6=3000;
			 PWMLER=(1<<6);
		}
		if(!(IOPIN0&(1<<15)))
		{
			 PWMMR6=22500;
			 PWMLER=(1<<6);
			 while(!(IOPIN0&(1<<15)))
				{
					IOPIN0=data[3]<<0;
					delay();
				}
			 PWMMR6=3000;
			 PWMLER=(1<<6);
		}
		else{
		IOPIN0=data[0]<<0;
		}
	}
}
