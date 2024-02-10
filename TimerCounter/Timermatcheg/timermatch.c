//timer as timer using match facility
#include<lpc213x.h>
void pll()                       //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
{
    PLLCON=0X01;
    PLLCFG=0X24;
    PLLFEED=0XAA;
    PLLFEED=0X55;
    while((PLLSTAT&(1<<10))==0);
    PLLCON=0X03;
    PLLFEED=0XAA;
    PLLFEED=0X55;
    VPBDIV=0X01;
}

void wait()
{
    T1CTCR=0X0000;          //Timer Mode
    T1PR=59999;                 //Prescaler Value
    T1MR0=500;                 //Match Register Value
    T1MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
    T1TCR=0X04;                 //Reset Timer
    T1TCR=0X01;                 //Timer ON
    while(T1TC!=T1MR0);
    T1TC=0;                         //Timer OFF
}

int main(void)
{

    IODIR0=0xffffffff;
    pll();                             //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
    while(1) {
        IOSET0=0xffffffff;
        wait();
        IOCLR0=0xffffffff;
        wait();
    }
}
