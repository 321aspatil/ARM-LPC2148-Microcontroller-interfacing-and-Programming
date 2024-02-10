#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<60000;i++);
}
int main()
{
	unsigned char data[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	IODIR0=(0xFF<<0);
	while(1)
	{
		unsigned int j;
		for(j=0;j<10;j++)
		{
			IOPIN0=(data[j]<<0);
			delay();
		}
	}
	return 0;
}