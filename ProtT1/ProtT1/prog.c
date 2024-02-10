#include <LPC213x.h>
#include "UART.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
unsigned int val;
static int dval=1;
void delay(int t)
{
	T0CTCR=0X0000;          //Timer Mode
  T0MR0=6000*t;                 //Match Register Value
  T0MCR=0x04;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
  T0TCR=0X02;                 //Reset Timer
  T0TCR=0X01;                 //Timer ON
  while(T0TC!=T0MR0);
  T0TC=0;                         //Timer OFF
}
void isr_int1()__irq
{
  delay(dval);
  IOSET0 = (1<<4);
  delay(dval);
  IOCLR0 = (1<<4);
  EXTINT = (1<<1);
  VICVectAddr = 00;
}
void init1()
{
PINSEL0 = (3<<6);
VICVectAddr3 = (unsigned)isr_int1;
VICVectCntl3 = (1<<5)|15;
EXTMODE = (1<<1);
VICIntEnable =(1<<15);
}
void setfangle()
{
	dval=((val*1023)/(0.0032))*40;
}
unsigned int adc(int no,int ch)
{
    switch(no)                                    //select adc
    {
        case 0: AD0CR=0x00200A00|(1<<ch);       //select channel
                AD0CR|=(1<<24);                 //start conversion
                while((AD0GDR& (1U<<31))==0);
                val=AD0GDR;
                break;
        case 1: AD1CR=0x00200F00|(1<<ch);       //select channel
                AD1CR|=(1<<24);                 //start conversion
                while((AD1GDR&(1<<31))==0);
                val=AD1GDR;
                break;
    }
    val=(val >> 6) & 0x03FF;                   // bit 6:15 is 10 bit AD value
    return val;
}
int main()
{
	VPBDIV=0x01;
	IODIR0 = (1<<4);
	init1();
	initUART();
	strUART("Firing angle Control using LDR\n\r");
	
	while(1)
	{
		adc(1,4);
		setfangle();
	}
}

