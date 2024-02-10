#include <LPC213X.H>
void delay(unsigned int t)
{
	unsigned int i,j;
	for(j=0;j<t;j++)
	{
	for(i=0;i<1275;i++);
	}
}
void lcd_cmd(unsigned char cmd)
{
	IOPIN0=(cmd<<0);
	IOCLR0=(1<<8);//rs=0
	IOSET0=(1<<9);//en=1
	delay(50);
	IOCLR0=(1<<9);//en=0
}
void lcd_data(unsigned char data)
{
	IOPIN0=(data<<0);
	IOSET0=(1<<8);//rs=1
	IOSET0=(1<<9);//en=1
	delay(50);
	IOCLR0=(1<<9);//en=0
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
int main()
{
	IODIR0=(0xFFF<<0)|(1<<25);
	lcd_init();
	while(1)
	{
		IOSET0=(1<<25);
		delay(200);
		IOCLR0=(1<<25);
		delay(50);
		lcd_cmd(0x01);
		delay(50);
		lcd_cmd(0x80);
		delay(50);
		string("EMBEDDED LAB");
		delay(100);
		lcd_cmd(0xC0);
		delay(50);
		string("ASSESMENT EXAM");
		delay(100);
	}
}
