// Flash LED Connected to P0.4 using Software Delay and IOSET and IOCLR Register
#include <LPC213X.H>
int main(){
	unsigned int i;
	PINSEL0=0x00000000;
	IODIR0=0x00000010;
	while(1){
		IOSET0=0x00000010;
		for(i=0;i<1000;i++);
		IOCLR0=0x00000010;
		for(i=0;i<1000;i++);
	}
	return 0;
}
/*#include <LPC213X.H>
int main(){
	unsigned int i;
	IODIR0=0x000000FF;
	while(1){
		IOSET0=0x000000FF;
		for(i=0;i<1000;i++);
		IOCLR0=0x000000FF;
		for(i=0;i<1000;i++);
	}
	return 0;
}
*/