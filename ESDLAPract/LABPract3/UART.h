#include<LPC213X.H>
void initUART(void);
void sendUART(unsigned char);
unsigned char recvUART(void);
void strUART(char *mydata);
void initUART(void)
{
	PINSEL0|=0x05;//set P0.0 and P0.1 for Txd and Rxd respectively
	//make DLAB=1 in order to set baud rate
	U0FCR=0x07;//Enable FIFO and set RX and TX FIFOs for AutoReset
	U0LCR=0x83;//DLAB=1, bit 1:0 set as 11 for 8 bit UART
	U0DLL=19;//0x0014 for 9600bps(Divisor=PCLK/baudrate*16)
	U0DLM=0x00;
	U0LCR=0x03;//DLAB=0, bit 1:0 set as 11 for 8 bit UART
	//again make DLAB=0 in order to access U0THR and U0RBR after setting the baud rate
}
void sendUART(unsigned char mydata)
{
	U0THR=mydata;
	while(((U0LSR)&(1<<6))==0);//check if transmission is over,see the status of TEMT flag

}
unsigned char recvUART(void)
{
	while(((U0LSR)&(1<<1))==0);//check if data is received completely,see the status of RDR flag
	return U0RBR;
}
void strUART(char *mydata)
{
	int i=0;
	while(mydata[i]!='\0')
	{
		sendUART(mydata[i]);
		i++;
	}
	//sendUART('\n');
	sendUART('\r');
	
}
