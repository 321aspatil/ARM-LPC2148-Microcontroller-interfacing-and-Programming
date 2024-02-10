#include <LPC213X.H>
unsigned int val;
void delay()
{
	int i;
	for(i=0;i<200;i++);
}
void AD1C_init()
{								
	PINSEL0=(3<<20);//Port P0.10 selected for ADC AD1.2
	AD1CR=0x00;
	AD1CR|=13<<8;//CLKDIV
	//AD1CR|=1<<16;//Burst ON
	AD1CR|=1<<21;//PDN=1
}
unsigned int AD1C_read(int ch)
{
	unsigned int adcdata;
	AD1CR|=(1<<ch);//channel select
	delay();
	AD1CR|=1<<24;//start of conversion
	while(AD1GDR&&(0x80000000)==0); //check for EOC
	adcdata=AD1GDR;
	adcdata=(adcdata>>6)&0x03FF;
	return adcdata;
}
//void AD0C_init()
//{								
//	PINSEL0=(3<<20);//Port P0.10 selected for ADC AD1.2
//	AD0CR=0x00;
//	AD0CR|=13<<8;//CLKDIV
//	AD0CR|=1<<16;//Burst ON
//	AD0CR|=1<<21;//PDN=1
//}
//unsigned int AD0C_read(int ch)
//{
//	unsigned int adcdata;
//	AD0CR|=(1<<ch);//channel select
//	delay();
//	AD0CR|=1<<24;//start of conversion
//	while(AD0GDR&&(0x80000000)==0); //check for EOC
//	adcdata=AD0GDR;
//	adcdata=(adcdata>>6)&0x03FF;
//	return adcdata;
//}
int main()
{
	unsigned int value;
	IODIR0|=(1<<4);
	AD1C_init();
	while(1)
	{
		value=AD1C_read(2);
		if(value<0x1FF)
		{
			IOSET0=0x10;
		}
		else
		{
			IOCLR0=0x10;
		}
	}
}
