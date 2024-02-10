/*on pressing switch set pll for 60MHz,display message on lcd showing 60MHz*/
#include <LPC213X.H>
void delay(unsigned int t)
{
	   unsigned long int i;
	   for(i=0;i<1275*t;i++);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0=(1<<3); //en=0
	IOPIN0=(cmd<<4);//Latch command data on P0.4 t0 P0.11
	IOCLR0=(1<<1);	  //rs=0
	IOSET0=(1<<3); //en=1
	delay(10);
	IOCLR0=(1<<3); //en=0
		
}
void lcd_data(unsigned char data)
{
	IOCLR0=(1<<3); //en=0
	IOPIN0=(data<<4);//Latch data on P0.4 t0 P0.11
	IOSET0=(1<<1);	  //rs=1
	IOSET0=(1<<3); //en=1
	delay(10);
	IOCLR0=(1<<3); //en=0
		
}
void lcd_init()
{
	lcd_cmd(0x01);
	delay(5);
	lcd_cmd(0x0C);
	delay(5);
}
void str(unsigned char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		delay(5);
		i++;
	}
}
void init_pll()
{
	PLLCFG=0x24;
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	while((!(PLLSTAT & (1<<10)))&&(!(IOPIN0 & (1<<19))));
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	lcd_cmd(0x01);
	delay(5);
	lcd_cmd(0x80);
	delay(10);
	str("CCLK=Sixty");
	delay(5);
	VPBDIV=0x02;
	lcd_cmd(0xC0);
	delay(5);
	str("PCLK=Thirty");
	delay(5);
}
int main()
{
	IODIR0=0x0000FFF;//P0.0 to P0.11 set as o/p pins
	lcd_init();
	delay(5);
	while(1)
	{
	   	lcd_cmd(0x80);
		delay(5);
		str("C MHZ");
		delay(5);
		if((IOPIN0 & (1<<30))==0)
		{
			break;
		}
	}
//	init_pll();
	return 0;
}