#include <LPC213X.H>
int main(){
	IODIR0=(1<<4);
	while(1){
		if(!(IOPIN0 & (1<<0))){
			IOSET0=(1<<4);
		}
		else{
			IOCLR0=(1<<4);
		}	
	}
}
