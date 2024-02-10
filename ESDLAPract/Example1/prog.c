/*Write an embedded c program to display the interrupt type  on 16*2 lcd,Configure all interrupt as low level sensitive.
interface lcd in 4 bit mode
configure ext 0 as fiq
ext 1 as virq
ext 2 as nvirq
*/
#include <LPC213X.H>
#include"LCD.h"

void FIQ_Handler(void)__irq
{
	 LCD_CMD(0x01);
	 delay_ms(10);
	 LCD_CMD(0x80);
	 delay_ms(10);
	 LCD_STRING("FIQ ONGOING");
	 delay_ms(50);
	 LCD_CMD(0x01);
	 delay_ms(10);
	 EXTINT=0x01;
}
void ext1isr()__irq
{
	 LCD_CMD(0x01);
	 delay_ms(10);
	 LCD_CMD(0x80);
	 delay_ms(10);
	 LCD_STRING("VIRQ ONGOING");
	 delay_ms(50);
	 LCD_CMD(0x01);
	 delay_ms(10);
	 EXTINT=0x02;
	 VICVectAddr=00;
}
void ext2isr()__irq
{
	 LCD_CMD(0x01);
	 delay_ms(10);
	 LCD_CMD(0x80);
	 delay_ms(10);
	 LCD_STRING("NVIRQ ONGOING");
	 delay_ms(50);
	 LCD_CMD(0x01);
	 delay_ms(10);
	 EXTINT=0x04;
	 VICVectAddr=00;
}
void isr_init()
{
	PINSEL0=(2<<28)|(2<<30);
	PINSEL1=0x01;//(1<<0)
	VICIntSelect|=(1<<14)|(0<<15)|(0<<16);
	VICVectCntl0=(1<<5)|15;
	VICVectAddr0=(unsigned)ext1isr;
	VICDefVectAddr=(unsigned)ext2isr;
	VICIntEnable|=(1<<14)|(1<<15)|(1<<16);
}
int main(void)
{
	IODIR1|=(1<<31);
	LCD_INIT();
	isr_init();
	while(1)
	{	
		LCD_CMD(0x01);
	 	delay_ms(10);
	 	LCD_CMD(0x80);
	 	delay_ms(10);
	 	LCD_STRING("NO INTRPTS!");
	 	delay_ms(50);
		IOSET1=(1<<31);
		delay_ms(30);
		IOCLR1=(1<<31);
		delay_ms(30);
		EXTINT=EXTINT;	
	}
	return 0;
}

