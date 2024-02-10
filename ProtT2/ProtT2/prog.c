#include <LPC213X.H>
#include "UART.h"
#include<math.h>
#include <stdio.h>
unsigned int angle;
char buffer[100];
int dval = 1;
int ch,hj;
void chk(void);

void delay(int t)
{
 T0CTCR=0X0000;               //Timer Mode
  T0MR0=6000*t;               //Match Register Value
  T0MCR=0x04;                 //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
  T0TCR=0X02;                 //Reset Timer
  T0TCR=0X01;                 //Timer ON
  while(T0TC!=T0MR0);
  T0TC=0;                     //Timer OFF
}

void isr_int1()__irq
{
  delay(dval);
  IOSET0 = (1<<4);
  delay(10);
  IOCLR0 = (1<<4);
  EXTINT = (1<<1);
  VICVectAddr = 00;
}

void init1()
{
PINSEL0 = (3<<6);
VICVectAddr0 = (unsigned)isr_int1;
VICVectCntl0 = (1<<5)|15;
EXTMODE = (1<<1);

}

 void setfangle()
{
	strUART("\n\rSelect Firing Angle:\n\r1)22.5\n\r2)45\n\r3)67.5\n\r4)90\n\r5)112.5\n\r6)135\n\r7)157\n\r");	
	ch=recvUART();
	sendUART(ch);
	sendUART('\n');
	sendUART('\r');
	switch(ch)
	{
		case '1':dval=10;break;
		case '2':dval=20;break;
		case '3':dval=30;break;
		case '4':dval=40;break;
		case '5':dval=50;break;
		case '6':dval=60;break;
		case '7':dval=70;break;
	
		case '*':
				 chk();
		         break;
		default:dval=1;
	}
}
 

void fine()
{
	strUART("\n\rFiring angle Fine Control Selected\n\r");
  	while(1)
{
		
		if(IOPIN0&(1<<23))
	{
			if(dval>79)
			{
				dval=1;
			}
			else
			{
				while(IOPIN0&(1<<23));
				dval++;
			}
	    angle = floor(dval * 2.25);
        sprintf(buffer, "%d", angle);
        strUART("\r\nNew Firing Angle=");
        strUART(buffer);
	}

		 else if (IOPIN0&(1<<25))
	{

		   if(dval<=1)
			{
				dval=79;
			}
        // Decrease the firing angle
		else{
				while(IOPIN0&(1<<25));
				dval--;
			}
		angle = floor(dval * 2.25);
        sprintf(buffer, "%d", angle);
        strUART("\r\nNew Firing Angle=");
        strUART(buffer);    
	}
	   
}
}

void lvl()
{
  strUART("\n\rFiring angle level Control\n\r");
	setfangle();
	while(1)
	{
		ch=recvUART();
		sendUART(ch);
		if(ch=='0')
		{
		setfangle();
		}
	}

}



void chk()
{
  	strUART("\n\rSelect Firing Angle Control Mode:\n\rA)Level control\n\rB)Fine control\n\r");
	
	hj = recvUART();
	sendUART(hj); 
	VICIntEnable =(1<<15)|(1<<17);
	while(1)
{
	if((hj == 'B')|(hj == 'b'))
	{
	 fine();
	}
    else if((hj == 'A')|(hj == 'a'))
	{
	 lvl();
	}
} 
}

 
int main()
{
	VPBDIV=0x01;
	IODIR0 = (1<<4);
	init1();
	initUART();

  while(1)
  {
   chk();
  }

}

