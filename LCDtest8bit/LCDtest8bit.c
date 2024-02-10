//16X2 LCD interfacing with lpc2138 
#include <LPC213X.H>
void delay()
{
	   unsigned int i;
	   for(i=0;i<1275;i++);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0=(1<<3); //en=0
	IOPIN0=(cmd<<4);//Latch command data on P0.4 t0 P0.11
	IOCLR0=(1<<1);	  //rs=0
	IOSET0=(1<<3); //en=1
	delay();
	IOCLR0=(1<<3); //en=0
		
}
void lcd_data(unsigned char data)
{
	IOCLR0=(1<<3); //en=0
	IOPIN0=(data<<4);//Latch data on P0.4 t0 P0.11
	IOSET0=(1<<1);	  //rs=1
	IOSET0=(1<<3); //en=1
	delay();
	IOCLR0=(1<<3); //en=0
		
}
void lcd_init()
{
	lcd_cmd(0x01);
	delay();
	lcd_cmd(0x38);
	delay();
	lcd_cmd(0x0C);
	delay();
	lcd_cmd(0x06);
	delay();
}
void str(char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		delay();
		i++;
	}
}
int main()
{
	IODIR0=0x00000FFF;//P0.0 to P0.11 set as o/p pins
	lcd_init();
	lcd_cmd(0x80);
	str("EMBEDDED SYSTEMS");
	//str("LCD INTERFACING");
	delay();
	lcd_cmd(0xC0);
	str("ELECTRONICS DEPT");
	//str("WITH LPC2138");
	delay();
	while(1);
	return 0;
}