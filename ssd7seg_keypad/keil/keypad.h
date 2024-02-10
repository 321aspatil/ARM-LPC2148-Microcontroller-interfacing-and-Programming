#include <LPC213X.H>
#define r1 19;
#define r2 20;
#define r3 21;
#define r4 22;
#define c1 16;
#define c2 17;
#define c3 18;
unsigned char hexCodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}
void keypad(void);
void keypad()
{
	//c1=c2=c3=1;
	//	r1=0;r2=1;r3=1;r4=1;
	IOCLR0=(0<<r1);
	IOSET0=(1<<r2)|(1<<r3)|(1<<r4);
	if(!(IOPIN0 & (1<<c1)))
	{
		IOPIN0=(hexCodes[1]<<0);
		while(!(IOPIN0 & (1<<c1)));
	}
	else if(!(IOPIN0 & (1<<c2)))
	{
		IOPIN0=(hexCodes[2]<<0);
		while(!(IOPIN0 & (1<<c2)));
	}
	else if(!(IOPIN0 & (1<<c3)))
	{
		IOPIN0=(hexCodes[3]<<0);
		while(!(IOPIN0 & (1<<c3)));
	}
	
	//	r1=1;r2=0;r3=1;r4=1;
	IOCLR0=(0<<r2);
	IOSET0=(1<<r1)|(1<<r3)|(1<<r4);
	if(!(IOPIN0 & (1<<c1)))
	{
		IOPIN0=(hexCodes[4]<<0);
		while(!(IOPIN0 & (1<<c1)));
	}
	else if(!(IOPIN0 & (1<<c2)))
	{
		IOPIN0=(hexCodes[5]<<0);
		while(!(IOPIN0 & (1<<c2)));
	}
	else if(!(IOPIN0 & (1<<c3)))
	{
		IOPIN0=(hexCodes[6]<<0);
		while(!(IOPIN0 & (1<<c3)));
	}
	
	//	r1=1;r2=1;r3=0;r4=1;
	IOCLR0=(0<<r3);
	IOSET0=(1<<r1)|(1<<r2)|(1<<r4);
	if(!(IOPIN0 & (1<<c1)))
	{
		IOPIN0=(hexCodes[7]<<0);
		while(!(IOPIN0 & (1<<c1)));
	}
	else if(!(IOPIN0 & (1<<c2)))
	{
		IOPIN0=(hexCodes[8]<<0);
		while(!(IOPIN0 & (1<<c2)));
	}
	else if(!(IOPIN0 & (1<<c3)))
	{
		IOPIN0=(hexCodes[9]<<0);
		while(!(IOPIN0 & (1<<c3)));
	}
	
	//	r1=1;r2=1;r3=1;r4=0;
	IOCLR0=(0<<r4);
	IOSET0=(1<<r1)|(1<<r2)|(1<<r3);
	if(!(IOPIN0 & (1<<c1)))
	{
		IOPIN0=(hexCodes[0]<<0);
		while(!(IOPIN0 & (1<<c1)));
	}
	else if(!(IOPIN0 & (1<<c2)))
	{
		IOPIN0=(hexCodes[0]<<0);
		while(!(IOPIN0 & (1<<c2)));
	}
	else if(!(IOPIN0 & (1<<c3)))
	{
		IOPIN0=(hexCodes[0]<<0);
		while(!(IOPIN0 & (1<<c3)));
	}
}
int main()
{
	IODIR0=(0xFF<<0)|(0xFF<<16);
	while(1)
	{
		keypad();
	}
}
