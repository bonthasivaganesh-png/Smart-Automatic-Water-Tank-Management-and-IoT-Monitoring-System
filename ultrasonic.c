#include<lpc21xx.h>
#include "header.h"
#define TRIG (1<<10)
#define ECHO (1<<11)
void ultrasonic_init(void)
{
IODIR0 |= TRIG;
IODIR0 &= ~ECHO;
}
u32 ultrasonic_read(void)
{
u32 count=0;
IOCLR0=TRIG;
delay_us(2);
IOSET0=TRIG;
delay_us(10);
IOCLR0=TRIG;//

while(!(IOPIN0 & ECHO));
while(IOPIN0 & ECHO)
{
count++;
delay_us(1);
/*
if(count>30000)
{
uart0_tx_string("timeout\n");
return 0;
} */
}
return (count/58) ;
}
