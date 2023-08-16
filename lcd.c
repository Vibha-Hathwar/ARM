#include <lpc214x.h>
void delay(unsigned long x)
{
  unsigned char i;
  while(x--)
    for(i=0;i<250;i++);
}
void LCD_Command(unsigned char cmd)
{
  IOCLR0 = 0X00018000;//P0.15-RS=0,P0.16-RW=0;CMD register & write operation
  IOPIN1 = cmd << 16; //P1.23-P1.16 of P1 to send data or command to LCD
  IOSET0 = 0X00020000; //Send High to low pulse
  delay(2);
  IOCLR0 = 0x00020000;
  delay(250);
}
void LCD_init(void)
{
  LCD_Command(0x38); // Function set 8-bit, 2 line 5x7 font
  LCD_Command(0x0c); // Display on off control: Display on, cursor off
  LCD_Command(0x01); //Clear the LCD display
}
void LCD_Data(unsigned char data)
{
  IOSET0 = 0X00008000; //P0.15-RS=1 Data register
  IOCLR0 = 0X00010000; // P0.16 - RW =0 write operation
  IOPIN1=data << 16; //P1.23-P1.16 of P1 to send data or command to LCD
  IOSET0 = 0X00020000; //Send high to low pulse
  delay(2);
  IOCLR0 = 0x00020000;
  delay(250);
}
int main()
{
  unsigned char str[]="Hello World";
  unsigned char i;
  PINSEL0 = 0; // Configure P0 as GPIO port
  PINSEL1 = 0; // Configure P1 as GPIO port
  IODIR0 = 0X00038000; // Set P0 pins 15, 16 and 17 as output
  IODIR1 = 0X00FF0000; // Set P1 pins 16 to 23 as output
  LCD_init();
  LCD_Command(0x80);
  for(i=0;str[i]!='\0';i++)
    LCD_Data(str[i]);
  while(1);
  return 0;
}
