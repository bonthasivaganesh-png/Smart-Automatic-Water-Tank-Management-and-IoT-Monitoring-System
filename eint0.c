#include<lpc21xx.h>
#include"header.h"
int mode;
void EINT0_Handler(void) __irq
{
mode=!mode;
EXTINT=1;
VICVectAddr=0;
}

void config_for_eint0(void)
{
PINSEL1|=1;
EXTMODE=1;
EXTPOLAR=0;
VICIntSelect=0;
VICVectCntl0=14|(1<<5);
VICVectAddr0=(unsigned int)EINT0_Handler;
VICIntEnable=1<<14;
}




