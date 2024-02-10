//capture facility with interrupt
//display captured time(or count) on lcd if 
#include <LPC213X.H>
#include<stdio.h>
#include"lcd4.h"
unsigned int cap;
char data[16];
void pll()                       
{
    PLLCON=0X01;
    PLLCFG=0X60;//Fosc=12Mhz,CCLK=12Mhz
    PLLFEED=0XAA;
    PLLFEED=0X55;
    while((PLLSTAT&(1<<10))==0);
    PLLCON=0X03;
    PLLFEED=0XAA;
    PLLFEED=0X55;
    VPBDIV=0X01;//PCLK=12MHz
}
void capisr()__irq
{
		cap=T0CR0;
		sprintf(data,"%d",cap);
		delay_ms(1);
		LCD_CMD(0x85);
		delay_ms(1);
		LCD_STRING(data);
		delay_ms(1);
		T0IR=0x10;
		VICVectAddr=00;	
}
void isrinit()
{
   	PINSEL0=(2<<4);
	VICVectCntl0=(1<<5)|4;
	VICVectAddr0=(unsigned)capisr;
	VICIntEnable=(1<<4);
}
int main()
{	
	pll();
	LCD_INIT();
	isrinit();
	T0PR=11999999;//TC count incemented after 1 sec
	T0TCR=0x02;
	T0CCR=0x06;
	LCD_STRING("CAPT:");
	delay_ms(1);
	LCD_CMD(0x89);
	delay_ms(1);
	LCD_STRING("sec.");
	T0TCR=0x01;
	while(1);
}
