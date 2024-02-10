 //capture facility with interrupt
//display captured time(or count) on lcd if 
#include <LPC213X.H>
#include<stdio.h>
long int cap,temp1=0,temp2=0;
unsigned char hexCodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
unsigned char con[]={0x0E,0x0D};
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
void pll()                       
{
    PLLCON=0x00;
		PLLFEED=0xAA;
		PLLFEED=0x55;
		VPBDIV=0x01;
}
void capisr()__irq
{
		cap=T0CR0;
		temp1=cap%10;
		temp2=cap/10;
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
	IODIR0=(0xFFFF<<8);
	pll();
	isrinit();
	T0PR=11999999;//TC count incemented after 1 sec
	T0TCR=0x02;
	T0CCR=0x05;
	T0TCR=0x01;
	while(1)
	{
	IOPIN0=(con[1]<<16)|(hexCodes[temp1]<<8);
	IOPIN0=(con[0]<<16)|(hexCodes[temp2]<<8);
	}
}

