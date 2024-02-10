#include <LPC213X.H>
#include"LCD8.h"
#include<stdio.h>
char buffer[16];
int binaryInput;
int decimalOutput;
int binaryToDecimal(int binaryInput) {
    int decimal = 0, base = 1, remainder;
    while (binaryInput > 0) {
        remainder = binaryInput % 10;
        decimal += remainder * base;
        binaryInput /= 10;
        base *= 2;
    }
    return decimal;
}
int main()
{
	 lcd_init();
	 lcd_cmd(0x80);
	 delay();
	 str("Binary:");
	 lcd_cmd(0xC0);
	 delay();
	 str("Decimal:");
	 while(1){
	  binaryInput = ((IO0PIN >> 25) & 0x0F);
	 decimalOutput = binaryToDecimal(binaryInput);

	 sprintf(buffer, "%b", binaryInput);
	 lcd_cmd(0x88);
	 delay();
	 str(buffer);
	 delay();
	 sprintf(buffer, "%d", decimalOutput);
	 lcd_cmd(0xC8);
	 delay();
	 str(buffer);
	 delay();
	 }
}
