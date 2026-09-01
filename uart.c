#include<lpc21xx.h>
#include "header.h"

void uart0_init(unsigned int baud)
{
int pclk,result=0;

if(VPBDIV==0)
pclk=15000000;
else if(VPBDIV==1)
pclk=60000000;
else if(VPBDIV==2)
pclk=30000000;

result=pclk/(16*baud);
PINSEL0|=0x00050005;
U0LCR=0x83;
U0DLL=(result &0xff);
U0DLM=((result>>8)&0xff);
U0LCR=0x03;
}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}

#define RDR (U0LSR&1)
unsigned char uart0_rx()
{
while(RDR==0);
return U0RBR;
}


void uart0_tx_string(char *ptr)

{
while(*ptr!='\0')
{
uart0_tx(*ptr);
ptr++;
}
}

void uart0_binary(int num)
{
int pos,temp;
for(pos=31;pos>=0;pos--)
{
temp=(num>>pos&1);
uart0_tx(temp+48);
}
}

void uart0_integer(int num)
{
int a[20],i;
if(num<0)
{
num=-num;
uart0_tx('-');
}
if(num==0)
{
uart0_tx('0');
return ;
}
for(i=0;num;num/=10,i++)
{
a[i]=num%10+48;
//a[i]=(t+48);
}
for(i=i-1;i>=0;i--)
{
uart0_tx(a[i]);
}
}
void uart0_float(float f)
{
int num,n1;
if(f==0)
{
uart0_tx(0);
return ;
}
if(f<0)
{	 
f=-f;
uart0_tx('-');
}
num=(int)f;
uart0_integer(num);

uart0_tx('.');

n1=(f-num)*100;
uart0_integer(n1);
}

