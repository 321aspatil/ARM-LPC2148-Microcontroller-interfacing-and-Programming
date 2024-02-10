#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<60000;i++);
}
int main()
{
	unsigned char data[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
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