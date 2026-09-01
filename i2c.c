#include <LPC21xx.H>

#include "header.h"


void i2c_init(void){

	PINSEL0|=0x50;//P0.2->SCL, P0.3->SDA

	I2CONSET=(1<<6);//i2c interface is enabled & master mode selected

	I2SCLH=I2SCLL=75;//100Kbps freq
}
#define SI ((I2CONSET>>3)&1)

void i2c_write(u8 sa, u8 mr, u8 data){

	/*1. generate start condi*/

	I2CONSET=(1<<5);//STA=1 (generates start condi)

	I2CONCLR=(1<<3);//SI=0

	while(SI==0);//waiting for start condi to generate

	I2CONCLR=(1<<5);//STA=0*

	

  /*2. send sa+w & wait for ack (check status code)*/

	I2DAT=sa;//send SA+W

	I2CONCLR=(1<<3);//clear SI

	while(SI==0);  //waiting for sa+w to transmit

	if(I2STAT==0x20){

		uart0_tx_string("\r\nErr: SA+W\r\n");

		goto exit;

	}

	
	/*3. send memory addr & check ack*/

	I2DAT=mr;//send m/r location

	I2CONCLR=(1<<3);//clear SI

	while(SI==0);//waiting for sa+w to transmit

	if(I2STAT==0x30){

		uart0_tx_string("\r\nErr: Memory Addr\r\n");

		goto exit;

	}

	

	/*4. send data & wait for ack*/

	I2DAT=data;//send data 

	I2CONCLR=(1<<3);//clear SI

	while(SI==0);//waiting for sa+w to transmit

	if(I2STAT==0x30){

		uart0_tx_string("\r\nErr: Data\r\n");

		goto exit;

	}

	

	/*5. generate stop condi*/

	exit:

			I2CONSET=(1<<4);//STO=1(generate stop condi)

			I2CONCLR=(1<<3);//SI*

}


u8 i2c_read(u8 sa,u8 mr){

	u8 temp;

	/*1.generate start condi*/

	I2CONSET=(1<<5);//STA=1 (generates start condi)

	I2CONCLR=(1<<3);//SI=0

	while(SI==0);//waiting for start condi to generate

	I2CONCLR=(1<<5);//STA=0*

	

	/*2.send sa+w & check ack*/

	I2DAT=sa&0xFE;//send SA+W

	I2CONCLR=(1<<3);//clear SI

	while(SI==0);//waiting for sa+w to transmit

	if(I2STAT==0x20){

		uart0_tx_string("\r\nErr: SA+W\r\n");

		goto exit;

	}

	

	/*3.send memory addr & check ack*/

	I2DAT=mr;//send m/r location

	I2CONCLR=(1<<3);//clear SI

	while(SI==0);//waiting for sa+w to transmit

	if(I2STAT==0x30){

		uart0_tx_string("\r\nErr: Memory Addr\r\n");

		goto exit;

	}

	

	/*4.generate restart*/

	I2CONSET=(1<<5);//STA=1 (generates start condi)

	I2CONCLR=(1<<3);//SI=0

	while(SI==0);//waiting for start condi to generate

	I2CONCLR=(1<<5);//STA=0*

	

	/*5.send sa+r & check ack*/

	I2DAT=sa;//send sa+r

	I2CONCLR=(1<<3);//clear SI

	while(SI==0);

	if(I2STAT==0x48){

		uart0_tx_string("\r\nErr: SA+R\r\n");

		goto exit;

	}

	

	/*6.read data & send noack*/

	I2CONCLR=(1<<3);//clear SI

	while(SI==0);//waiting for data to receive

	temp=I2DAT;

	

	/*7.generate stop condi*/

	exit:

			I2CONSET=(1<<4);//STO=1(generate stop condi)

			I2CONCLR=(1<<3);//SI*

	/*8.return received data*/

		return temp;

}              






                     						                                                                                                                                                       