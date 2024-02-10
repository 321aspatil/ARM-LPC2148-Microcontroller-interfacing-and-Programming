//write an embeddded c program to flash led connected at P0.4 using software delay use IOSET register,IOCLR register and left shift operator
#include <LPC213X.H>
int main()
{
	unsigned int i;
	IODIR0=(1<<4);
	while(1)
	{
		IOSET0=(1<<4);
		for(i=0;i<20000;i++);
		IOCLR0=(1<<4);
		for(i=0;i<20000;i++);
	}
	return 0;	
}
