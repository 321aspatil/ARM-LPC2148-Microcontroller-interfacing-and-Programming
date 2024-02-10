/*
write an ebedded c program to blink led connnected at port P1.31.connect a switch at port P0.1 and configure it for external interrupt 0 as low level sensitive nvirq.
on occurance of interrupt display "Interrupt on" message on 16*2 lcd.otherwise display "Interrupt off"
*/
#include <LPC213X.H>
#include"LCD8.h"
#include<stdio.h>
int count=0;
char data[18];
void isr_ext0(void)__irq
{
	 long int temp;
	 temp=EXTINT;
	 if((temp&0x01)==1)
	 {
				++count;
	}
	 EXTINT=temp;
	 VICVectAddr=0x00;
}
void nvirq_init()
{
	PINSEL0=(3<<2);
	VICIntSelect=0x00;
	VICDefVectAddr=(unsigned)isr_ext0;
	VICIntEnable=(1<<14);
	EXTMODE|=0x00;
	EXTPOLAR|=0x00;
}
int main()
{
	IODIR1=(1<<31);
	IODIR0=(0xFFF<<14);//P0.14 to P0.22 set as o/p pins
	nvirq_init();
	lcd_init();
	
	
	while(1)
	{
		lcd_cmd(0x01);
		delay(5);
		lcd_cmd(0x80);
		delay(5);
		sprintf(data,"%d",count);
		str(data);
		delay(5);
		IOSET1=(1<<31);
		delay(5);
		IOCLR1=(1<<31);
		delay(5);
	}
	return 0;
}