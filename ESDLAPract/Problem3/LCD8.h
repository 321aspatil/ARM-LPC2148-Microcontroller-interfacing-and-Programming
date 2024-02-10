//16X2 LCD interfacing with lpc2138 
#include <LPC213X.H>
void delay(unsigned int t)
{
	   unsigned long int i;
	   for(i=0;i<12750*t;i++);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0=(1<<15); //en=0
	IOPIN0=(cmd<<16);//Latch command data on P0.14 t0 P0.22
	IOCLR0=(1<<14);	  //rs=0
	IOSET0=(1<<15); //en=1
	delay(5);
	IOCLR0=(1<<15); //en=0
		
}
void lcd_data(unsigned char data)
{
	IOCLR0=(1<<15); //en=0
	IOPIN0=(data<<16);//Latch command data on P0.14 t0 P0.22
	IOSET0=(1<<14);	  //rs=1
	IOSET0=(1<<15); //en=1
	delay(5);
	IOCLR0=(1<<15); //en=0
		
}
void lcd_init()
{
	lcd_cmd(0x01);
	delay(5);
	lcd_cmd(0x38);
	delay(5);
	lcd_cmd(0x0C);
	delay(5);
	lcd_cmd(0x06);
	delay(5);
}
void str(char str[])
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		delay(5);
		i++;
	}
}