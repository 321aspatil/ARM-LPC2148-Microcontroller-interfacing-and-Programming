#include<LPC213X.H>
#define RS 	5
#define EN 	6
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
	IOCLR0=(1<<EN);//en=0
	IOPIN0=(cmd<<7);
	IOCLR0=(1<<RS);//rs=0
	IOSET0=(1<<EN);//en=1
	delay(50);
	IOCLR0=(1<<EN);//en=0
}
void lcd_data(unsigned char data)
{
	IOCLR0=(1<<EN);//en=0
	IOPIN0=(data<<7);
	IOSET0=(1<<RS);//rs=1
	IOSET0=(1<<EN);//en=1
	delay(50);
	IOCLR0=(1<<EN);//en=0
}
void lcd_init()
{
	lcd_cmd(0x01);
	delay(50);
	lcd_cmd(0x38);
	delay(50);
	lcd_cmd(0x0C);
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
	IODIR0|=(0x3FF<<5)|(1<<25)|(1<<26);
	lcd_init();
	while(1)
	{
		if(!(IOPIN0&(1<<1)))
		{
		IOSET0=(1<<26);
		delay(200);
		IOCLR0=(1<<26);
		delay(50);
		lcd_cmd(0x01);
		delay(20);
		lcd_cmd(0x80);
		delay(20);
		string("ASSESMENT EXAM");
		delay(50);
		lcd_cmd(0xC0);
		delay(20);
		string("EMBEDDED LAB");
		delay(50);	
		}
		else{
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
		delay(50);
		}
	}
}
