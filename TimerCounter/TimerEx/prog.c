/*
write an embedded c program to find out difference between two events using capture facility.
display the time difference on lcd
*/
#include <LPC213X.H>
#include<stdio.h>
#include"lcd4.h"
unsigned int t1,t2,diff; 
char data[16];
void pll()
{
	PLLCFG=0x24;//CCLK=60MHz
	PLLCON=0x01;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	while(!(PLLSTAT&(1<<10)));
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x01;//PCLK=60MHz
}
void T0_isr()__irq
{
	static int i=0;
	if(i==0)
	{
		t1=T0CR0;
		IOSET0=(1<<25);
		i++;
	}
	else
	{
		t2=T0CR0;		
		IOCLR0=(1<<25);
		i=0;
		diff=t2-t1;
		sprintf(data,"%d us",diff);
		LCD_CMD(0x01);
		delay_ms(10);
		LCD_CMD(0x80);
		delay_ms(10);
		LCD_STRING(data);
		delay_ms(10);
	}
	T0IR|=0x10;
	VICVectAddr=0x00;
}
int main()
{
	IODIR0=(1<<25);
	pll();
	LCD_INIT();
	delay_ms(10);
	PINSEL1=0x00002000;
	T0PR=59;//for 1ms time for each TC count
	T0TCR=0x02;
	T0CCR=0x05;
	VICVectAddr0=(unsigned)T0_isr;
	VICVectCntl0=0x24;
	VICIntEnable=0x10;
	T0TCR=0x01;
	while(1);
}
