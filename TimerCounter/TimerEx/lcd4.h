//LCD interfacing with lpc2138 in 4 bit mode
#include <LPC213X.H>
#define RS 8
#define EN 9
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STRING(char*);
void delay_ms(unsigned int);
void LCD_INIT()
{
	IODIR0=(0xFF<<0)|(1<<8)|(1<<9);//0x00000FF0;//output pins declared
	delay_ms(20);
	IOCLR0=1<<EN;//en=0
	LCD_CMD(0x02);	//initialize lcd in 4 bit mode
	LCD_CMD(0x28); // 2 lines
	LCD_CMD(0x01); //display clear
	LCD_CMD(0x0C);//display on cursor off
	LCD_CMD(0x80); //force cursor to first line first position
}
void LCD_CMD(unsigned char cmd)
{
	IOPIN0|=00;
	IOPIN0=((IOPIN0 & 0xFFFFFF00) | ((cmd & 0xF0)<<0));//upper nibble of command
	IOCLR0=(1<<RS);//rs=0
	IOSET0=(1<<EN);//en=1
	delay_ms(10);
	IOCLR0=(1<<EN);//en=0

	delay_ms(10);

	IOPIN0=((IOPIN0 & 0xFFFFFF00) | ((cmd & 0x0F)<<4));//lower nibble of command
	IOCLR0=(1<<RS);//rs=0
	IOSET0=(1<<EN);//en=1
	delay_ms(10);
	IOCLR0=(1<<EN);//en=0
}
void LCD_DATA(unsigned char data)
{
	IOPIN0|=00;
	IOPIN0=((IOPIN0 & 0xFFFFFF00) | ((data & 0xF0)<<0));//upper nibble of command
	IOSET0=(1<<RS);//rs=1
	IOSET0=(1<<EN);//en=1
	delay_ms(10);
	IOCLR0=(1<<EN);//en=0

	delay_ms(10);

	IOPIN0=((IOPIN0 & 0xFFFFFF00) | ((data & 0x0F)<<4));//lower nibble of command
	IOSET0=(1<<RS);//rs=1
	IOSET0=(1<<EN);//en=1
	delay_ms(10);
	IOCLR0=(1<<EN);//en=0
}	
void LCD_STRING(char *msg)
{
	unsigned char i=0;
	while(msg[i]!='\0')
	{
		LCD_DATA(msg[i]);
		i++;
	}
}
void delay_ms(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<1200;j++);
	}
}
