#include <LPC213X.H>
void delay()
{
	unsigned int i;
	for(i=0;i<1275;i++);
}
unsigned char keypad (void)
{ 
 while(1)
 {
  IOCLR1 |= (1<<19);   // Port1.19=0 (rowA=0)
  IOSET1 |= (1<<20)|(1<<21)|(1<<22);    //Port1.20, 1.21, 1.22 =1 (rowB, rowC, rowD =1)
  if (!(IOPIN1&(1<<16))) 
   { while (!(IOPIN1&(1<<16))); return '1';}   // if pin0 goes low (if c1 = 0), display 1 on lcd  
  if (!(IOPIN1&(1<<17)))
   { while (!(IOPIN1&(1<<17))); return '2';}  // if pin1 goes low (if c2 = 0), display 2 on lcd
  if (!(IOPIN1&(1<<18)))
   { while (!(IOPIN1&(1<<18))); return '3';} // if pin1 goes low (if c3 = 0), display 3 on lcd
  
  IOCLR1 |= (1<<20);   // Port1.20=0 (rowB=0)
  IOSET1 |= (1<<19)|(1<<21)|(1<<22);    //Port1.19, 1.21, 1.22 =1 (rowA, rowC, rowD =1)
  if (!(IOPIN1&(1<<16))) 
   { while (!(IOPIN1&(1<<16))); return '4';}   
  if (!(IOPIN1&(1<<17)))
   { while (!(IOPIN1&(1<<17))); return '5';}  
  if (!(IOPIN1&(1<<18)))
   { while (!(IOPIN1&(1<<18))); return '6';} 
  
  IOCLR1 |= (1<<21);   // Port1.21=0 (rowC=0)
  IOSET1 |= (1<<19)|(1<<20)|(1<<22);    //Port1.19, 1.20, 1.22 =1 (rowA, rowB, rowD =1)
  if (!(IOPIN1&(1<<16))) 
   { while (!(IOPIN1&(1<<16))); return '7';}     
  if (!(IOPIN1&(1<<17)))
   { while (!(IOPIN1&(1<<17))); return '8';}  
  if (!(IOPIN1&(1<<18)))
   { while (!(IOPIN1&(1<<18))); return '9';} 
  
  IOCLR1 |= (1<<22);   // Port1.20=0 (rowD=0)
  IOSET1 |= (1<<19)|(1<<20)|(1<<21);    //Port1.19, 1.21, 1.22 =1 (rowA, rowB, rowC =1)
  if (!(IOPIN1&(1<<16))) 
   { while (!(IOPIN1&(1<<16))); return '*';}    
  if (!(IOPIN1&(1<<17)))
   { while (!(IOPIN1&(1<<17))); return '0';} 
  if (!(IOPIN1&(1<<18)))
   { while (!(IOPIN1&(1<<18))); return '#';} 
 }
}

