#include <LPC213X.H>

void delay(unsigned int t)
{
	unsigned long int i;
	for(i=0;i<1275*t;i++);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0=(1<<9);//en=0;
	IOPIN0=(cmd<<0);
	IOCLR0=(1<<8);//rs=0
	IOSET0=(1<<9);//en=1;
	delay(50);
	IOCLR0=(1<<9);//en=0;
}
void lcd_data(unsigned char data)
{
	IOCLR0=(1<<9);//en=0;
	IOPIN0=(data<<0);
	IOSET0=(1<<8);//rs=1
	IOSET0=(1<<9);//en=1;
	delay(50);
	IOCLR0=(1<<9);//en=0;
}
void lcd_init()
{	
	lcd_cmd(0x01);
	delay(50);
	lcd_cmd(0x38);
	delay(50);
	lcd_cmd(0x0C);
	delay(50);
	lcd_cmd(0x06);
	delay(50);
}
void string(char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		delay(50);
		i++;
	}
}
