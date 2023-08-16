#include<lpc214x.h>
void writeSeg(unsigned char x)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    if(x & (0x80 >> i))
      IOSET0 = 0X00008000; // Send 1 via P0.15
    else
      IOCLR0 = 0X00008000; // Send 0 via P0.15
    //Send high to low pulse via P0.2
    IOSET0 = 0X00000004; //Send 1 via P0.2
    IOCLR0 = 0X00000004; //Send 0 via P0.2
  }
}
void delay(unsigned int x)
{
  unsigned char i;
  while(x--)
    for(i=0;i<250;i++);
}
int main()
{
  unsigned char LIFE[4]={0XC7,0xCF,0x8E,0x86};
  unsigned char HELP[4]={0x89,0x86,0xC7,0x8C};
  unsigned char i;
  PINSEL0 = 0X00000000; //Configure P0 as GPIO port
  IODIR0 = 0X00008004; // Set P0.15 and P0.2 as Output pins
  while(1)
  {
    for(i=0;i<4;i++)
      writeSeg(LIFE[i]);
    delay(10000);
    for(i=0;i<4;i++)
      writeSeg(HELP[i]);
    delay(10000);
  }
  return 0;
}
