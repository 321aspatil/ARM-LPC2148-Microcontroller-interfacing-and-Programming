#include <LPC213X.H>
#include"LCD4.h"
#include"Keypad.h"
int main()
{
	
	char key;
	IODIR1|= (0<<16)|(0<<17)|(0<<18)|(1<<19)|(1<<20)|(1<<21)|(1<<22);  // Port1.16, 1.17, 1.18 are i/p and 1.19,1.20,1.21,1.21 are o/p
	LCD_INIT();
	delay_ms(1);
	LCD_CMD(0x01);
	delay_ms(1);
	LCD_CMD(0x80);
	delay_ms(1);
	while(1)
	{
		key=keypad();
		delay_ms(1);
		LCD_STRING(&key);
		delay_ms(5);
	}		
}
