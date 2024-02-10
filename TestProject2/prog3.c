//Write an embedded C program to operate led connected at P0.4 using switch connected at P0.0 assume switch is connected in pull up network
#include <LPC213X.H>
int main()
{
	IODIR0=(1<<4);
		while(1)
		{
			if(IOPIN0 & (1<<0))
			{
				 //IOPIN0=(1<<4);
				 IOSET0=(1<<4);
			}
			else
			{			  
				  IOCLR0=(1<<4);
				  //IOPIN0=0x00;
			}
		}
	return 0;	
}