//display default CCLK and PCLK on lcd on button press set CCLK=60MHz and PCLK=30MHz and dislplay same on lcd
#include <LPC213X.H>
#include"lcd8.h"
void pll(int MSEL,int PSEL)
{
	PLLCFG=(MSEL<<0)|(PSEL<<5);
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	while(!(PLLSTAT&(1<<10)));
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x02;
}
void FIQ_Handler(void)__irq
{
  pll(4,2); 
  lcd_cmd(0x01);
  delay();
  lcd_cmd(0x80);
  delay();
  str("CCLK=60MHz");
  delay();
  lcd_cmd(0xC0);
  delay();
  str("PCLK=30MHz");
  delay();
  EXTINT=0x08;
	
}
void isrinit()
{
	PINSEL1=0x300;
	VICIntSelect=(1<<17);
	EXTMODE=0x08;
	VICIntEnable=(1<<17);
}
int main()
{
  IODIR0=0x00000FFF;//P0.0 to P0.11 set as o/p pins
  lcd_init();
  isrinit();
  pll(6,0);
  lcd_cmd(0x01);
  delay();
  lcd_cmd(0x80);
  delay();
  str("CCLK=12MHz");
  delay();
  lcd_cmd(0xC0);
  delay();
  str("PCLK=6MHz");
  delay();
  while(1)
  {
		
  }
}
