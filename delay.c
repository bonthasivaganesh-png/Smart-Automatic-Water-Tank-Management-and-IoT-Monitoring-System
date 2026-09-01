#include<lpc21xx.h>
#include "header.h"
void lcd_data(unsigned char data)
{
	unsigned int temp;
	IOCLR1=0XFE<<16;
	temp=((data&0xF0)<<16);
	IOSET1=temp;
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;

	IOCLR1=0xFE<<16;
	temp=((data&0x0f)<<20);
	IOSET1=temp;
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;

}
void lcd_cmd(unsigned int cmd)
{
	unsigned int temp;
	IOCLR1=0xFE<<16;
	temp=((cmd&0xf0)<<16);
	IOSET1=temp;
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;

	IOCLR1=0xFE<<16;
	temp=((cmd&0x0f)<<20);
	IOSET1=temp;
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;


}
void lcd_init()
{
	IODIR1=0xFE<<16;
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);

}
void lcd_string(char *ptr)
{
	while(*ptr!='\0')
	{
		lcd_data(*ptr);
		ptr++;
	}
}
void lcd_integer(int num) 
{
int a[10],i;
if(num==0)
{
lcd_data('0');
}
if(num<0)
{
num=-num;
lcd_data('-');
}
for(i=0;num;num/=10,i++)
{
a[i]=num%10+48;
}
for(i=i-1;i>=0;i--)
{
lcd_data(a[i]);
}
}

void lcd_float(float f)
{
int num,n1;
if(f==0)
{
lcd_data('0');
return ;
}
if(f<0)
{
f=-f;
lcd_data('-');
}
num=f;
lcd_integer(num);
lcd_data('.');
n1=(f-num)*100000;
lcd_integer(n1);
}


