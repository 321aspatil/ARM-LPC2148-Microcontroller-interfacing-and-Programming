#include <LPC213X.H>
unsigned char hexCodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
int keypad (void)
{ 
 while (1)
 {
  IOCLR0 |= (1<<3);   // Port0.3=0 (rowA=0)
  IOSET0 |= (1<<4)|(1<<5)|(1<<6);    //Port0.4, 0.5, 0.6 =1 (rowB, rowC, rowD =1)
  if (!(IOPIN0&(1<<0))) 
   { while (!(IOPIN0&(1<<0))); return 1;}   // if pin0 goes low (if c1 = 0), display 1 on lcd  
  if (!(IOPIN0&(1<<1)))
   { while (!(IOPIN0&(1<<1))); return 2;}  // if pin1 goes low (if c2 = 0), display 2 on lcd
  if (!(IOPIN0&(1<<2)))
   { while (!(IOPIN0&(1<<2))); return 3;} // if pin1 goes low (if c3 = 0), display 3 on lcd
  
  IOCLR0 |= (1<<4);   // Port0.4=0 (rowB=0)
  IOSET0 |= (1<<3)|(1<<5)|(1<<6);    //Port0.3, 0.5, 0.6 =1 (rowA, rowC, rowD =1)
    if (!(IOPIN0&(1<<0)))
   { while (!(IOPIN0&(1<<0))); return 4;}  //if pin0 goes low (if c1 = 0), display 4 on lcd  
  if (!(IOPIN0&(1<<1)))
   { while (!(IOPIN0&(1<<1))); return 5;}  // if pin1 goes low (if c2 = 0), display 5 on lcd
  if (!(IOPIN0&(1<<2)))
   { while (!(IOPIN0&(1<<2))); return 6;}  // if pin1 goes low (if c3 = 0), display 6 on lcd
  
  IOCLR0 |= (1<<5);   // Port0.5=0 (rowC=0)
  IOSET0 |= (1<<3)|(1<<4)|(1<<6);    //Port0.3, 0.4, 0.6 =1 (rowA, rowB, rowD =1)
    if (!(IOPIN0&(1<<0)))
   { while (!(IOPIN0&(1<<0))); return 7;}  //if pin0 goes low (if c1 = 0), display 7 on lcd  
  if (!(IOPIN0&(1<<1)))
   { while (!(IOPIN0&(1<<1))); return 8;}  // if pin1 goes low (if c2 = 0), display 8 on lcd
  if (!(IOPIN0&(1<<2)))
   { while (!(IOPIN0&(1<<2))); return 9;}  // if pin1 goes low (if c3 = 0), display 9 on lcd
  
  IOCLR0 |= (1<<6);   // Port0.6=0 (rowA=0)
  IOSET0 |= (1<<3)|(1<<4)|(1<<5);    //Port0.3, 0.4, 0.5 =1 (rowA, rowB, rowC =1)
    if (!(IOPIN0&(1<<0)))
   { while (!(IOPIN0&(1<<0))); return 0;}  //if pin0 goes low (if c1 = 0), display * on lcd  
  if (!(IOPIN0&(1<<1)))
   { while (!(IOPIN0&(1<<1))); return 0;}  // if pin1 goes low (if c2 = 0), display 0 on lcd
  if (!(IOPIN0&(1<<2)))
   { while (!(IOPIN0&(1<<2))); return 0;}  // if pin1 goes low (if c3 = 0), display # on lcd
 }
}

int main()
{
 int key;
 IODIR0 |= (0<<0)|(0<<1)|(0<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6);  // Port0.0, 0.1, 0.2 are i/p and 0.3,0.4,0.5,0.6 are o/p
 IODIR1 = 0xffffffff;    // all pins of PORT1 are o/p
 
 while (1)
 {
  key = keypad ();
  IOPIN1=(hexCodes[key]<<16);
 }
}
