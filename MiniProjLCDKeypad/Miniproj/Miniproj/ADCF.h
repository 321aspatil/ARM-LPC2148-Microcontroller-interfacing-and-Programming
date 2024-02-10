#include <LPC213X.H>
void ADC1_init()
{
  AD1CR=0x00;
  AD1CR|=35<<8;//CLKDIV
  AD1CR|=1<<21;//PDN=1

}
unsigned int ADC1_read(unsigned int ch)
{
	unsigned int adcdata;
	AD1CR|=(1<<ch);//channel select
	delay();
	AD1CR|=1<<24;//start of conversion
	while(AD1DR&(0x80000000)==0); //check for EOC
	adcdata=AD1DR;
	adcdata=(adcdata>>6)&0x03FF;
	return adcdata;
}
void ADC0_init()
{
  AD0CR=0x00;
  AD0CR|=35<<8;//CLKDIV
  AD0CR|=1<<21;//PDN=1

}
unsigned int ADC0_read(unsigned int ch)
{
	unsigned int adcdata;
	AD0CR|=(1<<ch);//channel select
	delay();
	AD0CR|=1<<24;//start of conversion
	while(AD0DR&(0x80000000)==0); //check for EOC
	adcdata=AD0DR;
	adcdata=(adcdata>>6)&0x03FF;
	return adcdata;
}
