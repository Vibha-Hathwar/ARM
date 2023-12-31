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
  unsigned char data[]={0xff,0xff,0xff,0xff,0xA1,0x86,0x8c,0x87,0xff,0xc0,0x8e,0xff,0xc6,0x92,0x86,0xff,0xff,0xff,0xff};
  char i,j;
  PINSEL0 = 0X00000000; //Configure P0 as GPIO port
  IODIR0 = 0X00008004; // Set P0.15 and P0.2 as Output pins
  while(1)
  {
    for(i=0;i<16;i++) //Right to Left
    {
      for(j=i;j<i+4;j++)
        writeSeg(data[j]);
      delay(10000);
    }
    for(i=14;i>=0;i--) //Left to Right
    {
      for(j=i;j<i+4;j++)
        writeSeg(data[j]);
      delay(10000);
    }
  }
  return 0;
}
