#include<lpc21xx.h>
#include "header.h"
u32 add;
void eeprom(u8 t)
{
u8 temp;
i2c_write(0xa0,add,t);
delay_ms(30);
temp=i2c_read(0xa1,add++);
if(temp==t)
{
uart0_tx_string("\r\nEEPROM STATUS:DATA SAVED\r\n");
uart0_tx(add/10+48);
uart0_tx(add%10+48);
}
else
{
uart0_tx_string("\r\nEEPROM STATUS:DATA NOT SAVED\r\n");
uart0_tx(add/10+48);
uart0_tx(add%10+48);
}
}


