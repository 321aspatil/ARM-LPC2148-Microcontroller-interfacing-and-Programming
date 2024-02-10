//square wave generation using match facility without interrupt
#include<lpc213x.h>
void wait(long int wt)
{
    T0CTCR=0X0000;          //Timer Mode
    T0PR=59;                 //Prescaler Value
    T0MR0=wt;                 //Match Register Value
    T0MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
    T0TCR=0X02;                 //Reset Timer
    T0TCR=0X01;                 //Timer ON
    while(T0TC!=T0MR0);
    T0TC=0;                         //Timer OFF
}

int main(void)
{

    IO0DIR=0xffffffff;

    while(1) {
        IOSET0=0xffffffff;
        wait(1);
        IOCLR0=0xffffffff;
        wait(1);
    }

}
