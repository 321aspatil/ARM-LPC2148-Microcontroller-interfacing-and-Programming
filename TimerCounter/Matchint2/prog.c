#include<lpc213x.h>
void wait()
{
    T0CTCR=0x00;          //Timer Mode
    T0PR=1199999;                 //Prescaler Value
    T0MR0=100;                 //Match Register Value
    T0MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
    T0TCR=0x02;                 //Reset Timer
    T0TCR=0x01;                 //Timer ON
    while(T0MR0!=T0TC);
    T0TCR=0x00;                         //Timer OFF
}
int main(void)
{
    IO0DIR=0xffffffff;
   	VPBDIV=0x01;                             //Fosc=12Mhz,CCLK=12,PCLK=12MHz
    while(1) {
        IO0SET=0xffffffff;
        wait();
        IO0CLR=0xffffffff;
        wait();
    }
}
