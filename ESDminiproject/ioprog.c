#include <LPC213X.H>
#include"LCD4.h"
#include"Keypad.h"
void pll()
{
	PLLCFG=0x60;
	PLLCON=0x01;
	PLLFEED-0xAA;
	PLLFEED=0x55;
	while(!(PLLSTAT&(1<<10)));
	PLLCON=0x03;
	PLLFEED-0xAA;
	PLLFEED=0x55;
}
int main()
{
	char key;
	PINSEL1=2<<10;
	pll();
	LCD_INIT();
	delay_ms(1);
	LCD_CMD(0x01);
	delay_ms(1);
	LCD_CMD(0x80);
	delay_ms(1);
	LCD_STRING("Read?(y=1/n=0)");
	delay_ms(10);
	while(1)
	{
		key=keypad();
		LCD_CMD(0xC0);
		delay_ms(1);
		LCD_STRING(&key);
		delay_ms(5);
		if(key=='1')
		{
			LCD_CMD(0x90);
			delay_ms(1);
			tempadcval=adcval(1,6);
			delay();
			voltage=((tempadcval/1023)*3.3);
			sprintf(volt,"Voltage=%.2f",voltage);
			LCD_STRING(volt);
			delay_ms(1);	
		}
	}		
}
