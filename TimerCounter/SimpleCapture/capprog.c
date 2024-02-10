//capture facility without interrupt
//display captured time(or count) on lcd if 
#include <LPC213X.H>
#include<stdio.h>
#include"lcd4.h"
unsigned int cap;
char data[16];
int main()
{
	VPBDIV=0x01;
	PINSEL0=(2<<4);
	T0PR=11999999;//TC count incemented after 1 sec
	T0TCR=0x02;
	T0CCR=0x02;
	T0TCR=0x01;
	LCD_INIT();
	LCD_STRING("CAPT:");
	delay_ms(1);
	LCD_CMD(0x89);
	delay_ms(1);
	LCD_STRING("sec.");
	while(1)
	{
		cap=T0CR0;
		sprintf(data,"%d",cap);
		delay_ms(1);
		LCD_CMD(0x85);
		delay_ms(1);
		LCD_STRING(data);
		delay_ms(1);
	}
}
