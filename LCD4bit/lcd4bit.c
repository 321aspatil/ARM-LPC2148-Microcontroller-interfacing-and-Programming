#include <LPC213X.H>
#include "LCD.h"
int main(void)
{
	LCD_INIT();
	while(1)
	{
		LCD_STRING("LCD in 4 bit");
		LCD_CMD(0xC0);
		LCD_STRING("with LPC2138");
		LCD_CMD(0x01);
		LCD_CMD(0x80);
		delay_ms(700);	
	}

}
