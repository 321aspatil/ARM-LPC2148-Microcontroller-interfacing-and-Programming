// Flash LED Connected to P0.4 using Software Delay and IOPIN Register
#include <LPC213X.H>
int main(){
	unsigned int i;
	IODIR0=0x00000010;
	while(1){
		IOPIN0=0x00000010;
		for(i=0;i<1000;i++);
		IOPIN0=0x00000000;
		for(i=0;i<1000;i++);
	}
	return 0;
}