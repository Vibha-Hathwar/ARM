#include <lpc214x.h>
void delay(unsigned long x)
{
  unsigned char i;
  while(x--)
    for(i=0;i<250;i++);
}
int main()
{
  unsigned long i;
  unsigned char j;
  PINSEL1 = 0; // Configure P1 as GPIO
  IODIR1 = 0X00FF0000; // Set P1 pins 16 to 23 as output
  while(1)
  {
    //to display square waveform
    for(i=0;i<1000;i++)
    {
      IOSET1 = 0X00FF0000; // Send FFH on P1 for some delay
      delay(10);
      IOCLR1 = 0X00FF0000; //Send 0 on P1 for some delay
      delay(10);
    }
    // to display triangular waveform
    for(i=0;i<1000;i++)
    {
      for(j=0;j<255;j++)
        IOPIN1 = j<<16;
      for(j=255;j>0;j--)
        IOPIN1 = j<<16;
    }
  }
  return 0;
}
