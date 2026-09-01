#include <LPC21xx.H>

#include "header.h"


void can1_init(void){

	//VPBDIV=1;//PCLK=60MHz

	PINSEL1|=0x40000;//P0.25-->RD1

	C1MOD=1;//Select reset mode

	C1BTR=0x001C001D;//125Kbps baudrate

	AFMR=2;//accept all receiving msgs

	C1MOD=0;//release reset mode	

}



#define TCS ((C1GSR>>3)&1)

void can1_tx(CAN1 v){

	C1TID1=v.id;

	C1TFI1=v.dlc<<16;//set dlc,rtr=0,ff=0(std version)

	if(v.rtr==0){//if data-frame

		C1TDA1=v.byteA;

		C1TDB1=v.byteB;

	}

	else

		C1TFI1|=(1<<30);//rtr=1

	

	C1CMR=0x21;//Select Txbuf1 & start Xmission

	while(TCS==0);

}


void can1_parameter(u8 t,u8 w,u8 d)
{
CAN1 MSG;
MSG.id=0x301;
MSG.rtr=0;
MSG.dlc=8;
MSG.byteA=0;
MSG.byteA|=t;
MSG.byteA|=w<<8;
MSG.byteA|=d<<16;
can1_tx(MSG);
}

