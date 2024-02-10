#include <LPC213X.H>
#include"LCD8.h"
void FIQ_Handler()__irq
{
	lcd_cmd(0x01);
	delay(100);
	lcd_cmd(0x80);
	delay(100);
	string("FIQ!!!");
	delay(100);
	EXTINT=0x01;
}
void ext1isr()__irq
{
	lcd_cmd(0x01);
	delay(100);
	lcd_cmd(0x80);
	delay(100);
	string("VIRQ!!!");
	delay(100);
	EXTINT=0x02;
	VICVectAddr=00;
}
void ext2isr()__irq
{
	lcd_cmd(0x01);
	delay(100);
	lcd_cmd(0x80);
	delay(100);
	string("NVIRQ!!!");
	delay(100);
	EXTINT=0x04;
	VICVectAddr=00;
}
void isrinit()
{
	PINSEL1=(1<<0);
	PINSEL0=(2<<28)|(2<<30);
	VICIntSelect|=(1<<14)|(0<<15)|(0<<16);
	VICVectCntl0=(1<<5)|15;
	VICVectAddr0=(unsigned)ext1isr;
	VICDefVectAddr=(unsigned)ext2isr;
	VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}
int main()
{
	IODIR0=(0xFF<<0)|(1<<8)|(1<<9);
	IODIR1=(1<<31);
	lcd_init();
	isrinit();
	while(1)
	{
		IOSET1=(1<<31);
		delay(500);
		IOCLR1=(1<<31);
		delay(500);
		lcd_cmd(0x01);
		delay(100);
		lcd_cmd(0x80);
		delay(100);
		string("NO INTRPTS!");
		delay(100);
		EXTINT=0x07;
	}
	return 0;
}