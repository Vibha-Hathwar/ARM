#include<stdio.h>
#include<lpc214x.h>
void delay(unsigned int x)
{
  unsigned char i;
  while(x--)
    for(i=0;i<200;i++);
}
int main()
{
  unsigned long i;
  unsigned char clk,aclk;
  PINSEL1 = 0X00000000; //Configure P1 as GPIO port
  IODIR1 = 0X000F0000; // Set P1.16 to P1.19 as Output pins
  while(1)
  {
    clk=200; //No. of steps required for clockwise rotation
    aclk=100; //No. of steps required for anti-clockwise rotation
    while(1)
    {
      for(i=0x00080000;i>=0x00010000;i>>=1)
      {
        IOSET1 = i;
        delay(10000);
        IOCLR1 = 0X000F0000;
        if(--clk==0) break;
      }
      if(clk==0) break;
    }
    while(1)
    {
      for(i=0x00010000;i<=0x00080000;i<<=1)
      {
        IOSET1 = i;
        delay(10000);
        IOCLR1 = 0X000F0000;
        if(--aclk==0) break;
      }
      if(aclk==0) break;
    }
  }
  return 0;
}
