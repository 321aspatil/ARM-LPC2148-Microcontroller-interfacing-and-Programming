//stepsize=Vref/1023
//Ain=Dout*stepsize
/*
	Here step-size=3.3/1023=0.0032
	Dout=Ain/stepsize=1.5/0.0032=465=0x1D1
*/
#include <LPC213X.H>
void delay()
{
	unsigned int i;	
	for(i=0;i<1275;i++);
}
void ADC_init()
{
  PINSEL0=(3<<20);
  AD1CR=0x00;
  AD1CR|=2<<8;//CLKDIV
  AD1CR|=1<<21;//PDN=1

}
unsigned int ADC_read(unsigned int unit,unsigned int ch)
{
	unsigned int adcdata;
	switch(unit)
	{
		case 0:
			AD0CR|=(1<<ch);//channel select
			delay();
			AD0CR|=1<<24;//start of conversion
			while((AD0GDR&0x80000000)==0); //check for EOC
			adcdata=(AD0GDR>>6)&0x03FF;
			break;

		case 1:
			AD1CR|=(1<<ch);//channel select
			delay();
			AD1CR|=1<<24;//start of conversion
			while((AD1GDR&0x80000000)==0); //check for EOC
			adcdata=(AD1GDR>>6)&0x03FF;
			break;
		
	}
	return adcdata;
}
int main(void)
{
unsigned int value;
 IODIR0 |= (1<<4)|(1<<5)|(1<<6);
 PLLCON=0x00;
	PLLFEED=0xAA;
	PLLFEED=0x55;
 ADC_init();
  while(1)
  {
  value = ADC_read(1,2);
    if(value<0x1D1)
	{
	IOSET0 = (1<<4);
	IOCLR0 = (1<<5);
	IOCLR0 = (1<<6);
	}
	else if(value>0x1D1)
	{
	IOSET0 = (1<<5);
	IOCLR0 = (1<<4);
	IOCLR0 = (1<<6);
	} 
	else if(value == 0x1D1)
	   {
	IOCLR0 = (1<<5);
	IOCLR0 = (1<<4);
	IOSET0 = (1<<6);
	   }
  }
}
