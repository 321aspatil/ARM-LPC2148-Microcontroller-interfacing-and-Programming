//capture facility with interrupt
//display captured time(or count) on lcd if 
#include <LPC213X.H>
#include<stdio.h>
unsigned int cap;
char data[16];
unsigned char hexCodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
unsigned char con[]={0x0E,0x0D};
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
		//7segcode
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
	unsigned int i;
	IODIR0=(0xFFFF<<8);
	pll();
	isrinit();
	T0PR=11999999;//TC count incemented after 1 sec
	T0TCR=0x02;
	T0CCR=0x05;
	T0TCR=0x01;
	for(i=0;i<2;i++)
	{
		IOPIN0=(con[i]<<16)|(hexCodes[i]<<8);
	}
	while(1);
}
