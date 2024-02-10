#include <lpc213x.h>
#include <stdio.h>

#define PCLK_FREQ 12000000  // Assuming PCLK is set to 12 MHz

volatile unsigned int start_time = 0;
volatile unsigned int end_time = 0;

void delay(unsigned int count) {
	unsigned int i,j;		
	for(i=0;i<count;i++)
	{
			for(j=0;j<1275;j++);
	}
}

void initUART() {
    PINSEL0 |= (1 << 0) | (1 << 1); // Select TXD0 and RXD0
    U0LCR = 0x83; // 8-bit data, 1 stop bit, DLAB = 1
    U0DLM = 0x00; // Set DLM to 0
    U0DLL = 78;   // Set DLL for 9600 baud rate
    U0LCR = 0x03; // 8-bit data, 1 stop bit, DLAB = 0
}

void initFIQ() {
    PINSEL1 |= (1 << 24); // P0.28 as CAP0.0
    FIO0DIR &= ~(1 << 28); // P0.28 as input

    VICIntSelect &= ~(1 << 18); // FIQ
    VICIntEnable |= (1 << 18); // Enable FIQ

    // Configure Timer 0 for capture mode
    T0CTCR = 0x01; // Timer Mode: Capture rising edges
    T0CCR = (1 << 0) | (1 << 2); // Capture on rising edge and generate interrupt
}

__irq void FIQ_Handler(void) {
    if (T0IR & (1 << 4)) { // Check if FIQ is pending for Timer 0
        if (start_time == 0) {
            start_time = T0CR0;
        } else {
            end_time = T0CR0;
            VICVectAddr = 0; // Acknowledge Interrupt
        }
    }
}

void initTimer() {
    T0TCR = 0x02; // Reset Timer 0
    T0TCR = 0x01; // Enable Timer 0
}

int main() {
    PLLCON=0x00;
		PLLFEED=0xAA;
		PLLFEED=0x55;
		VPBDIV=0x01;
		initUART();
    initFIQ();
    initTimer();

    while (1) {
        if (start_time != 0 && end_time != 0) {
            unsigned int latency = end_time - start_time;
            printf("FIQ Latency: %u us\r\n", latency * 1000 / PCLK_FREQ);
            start_time = 0;
            end_time = 0;
        }

        delay(100000); // Delay for a while
    }

}
