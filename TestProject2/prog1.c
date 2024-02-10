#include <LPC213X.H>
int main(){		
	//IODIR0=0x40000290;
	//IOPIN0=0x40000290;
	IODIR0=0x00000090;
	//IOPIN0=(1<<4);//(data<<position)//Load IOPIN register to set P0.4 high using left shift operator 32-bit equivalent hex code is IOPIN0=0x00000010;
	//IOPIN0=(1<<7);////Load IOPIN register to set P0.7 high using left shift operator 32-bit equivalent hex code is IOPIN0=0x00000080;
	//IOPIN0=(1<<7)|(1<<4);//Load IOPIN register to set P0.4 and P0.7 high using left shift operator 32-bit equivalent hex code is IOPIN0=0x00000090; 
	//IOPIN0=(9<<4);//same as above setting binary 9 from fourth position
	//IOPIN0=(15<<4);//If IOPIN is loaded with (15<<4) what is the effect of the statement
	//IOPIN0=(0xF<<4)//same as above
	//IOPIN0=(0xF0<<0);//same as above
	return 0;
}
