//multiplexed common cathode seven segment display help message
#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
int main()
{
	unsigned int i;
	unsigned char data[]={0xF6,0xF9,0xB8,0xF3};
	unsigned char con[]={0x0E,0x0D,0x0B,0x07};
	IODIR0=(0x7F<<0)|(0xF<<16);
	while(1)
	{
		for(i=0;i<4;i++)
		{
			  IOPIN0=(con[i]<<16)|(data[i]<<0);
			  delay();
		}
	}
}
