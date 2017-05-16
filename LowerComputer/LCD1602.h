
#include <intrins.h>
#define      LCD_DB        P0 
#define uchar unsigned char 
#define uint unsigned int 




sbit cs4=P2^4;
sbit cs3=P2^5;
sbit cs2=P2^6;
sbit cs1=P2^7;

uchar  seg7[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x86,0x8e,0x89,0xbf};		  //共阳数码管段码显示,0-9(0x90),E(0x86),F(0x8e),0xbf代表‘-’
void Segdisplay(uchar num);

void Setdisplay(uchar num);
void Setdisplay1(uchar num);
void Setdisplay2();
void DelayMS(uint x);
void Delayk(uint x);

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	for(t=120;t>0;t--);
}


void Delayk(uint x)  //0.05ms
{
 	uchar t;
	while(x--)
	for(t=6;t>0;t--);
}


void Setdisplay(uchar num)				   //数码管显示程序
{
   	 LCD_DB=seg7[num/100];
	 cs1=1;
	 cs2=0; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;


	 LCD_DB=seg7[num%100/10];
	 cs1=0;
	 cs2=1; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[num%10];
	 cs1=1;
	 cs2=1; 
	 cs3=0;
	 cs4=1;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[11];
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=0;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;
	  

}

void Setdisplay1(uchar num)				   //数码管显示程序
{
   	 LCD_DB=seg7[num/100];
	 cs1=1;
	 cs2=0; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;


	 LCD_DB=seg7[num%100/10];
	 cs1=0;
	 cs2=1; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[num%10];
	 cs1=1;
	 cs2=1; 
	 cs3=0;
	 cs4=1;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[12];
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=0;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;
	  

}

void Setdisplay2()				   //数码管显示程序
{
   	 LCD_DB=seg7[13];
	 cs1=1;
	 cs2=0; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;


	 LCD_DB=seg7[13];
	 cs1=0;
	 cs2=1; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[13];
	 cs1=1;
	 cs2=1; 
	 cs3=0;
	 cs4=1;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[13];
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=0;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;
}

void Setdisplay3()				   //数码管显示程序EEEE
{
   	 LCD_DB=seg7[10];
	 cs1=1;
	 cs2=0; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;


	 LCD_DB=seg7[10];
	 cs1=0;
	 cs2=1; 
	 cs3=1;
	 cs4=1;
	 Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[10];
	 cs1=1;
	 cs2=1; 
	 cs3=0;
	 cs4=1;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;

	 LCD_DB=seg7[10];
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=0;
     Delayk(1);
	 cs1=1;
	 cs2=1; 
	 cs3=1;
	 cs4=1;	 
}

















/* 

sbit cs4=P2^4;
sbit cs3=P2^5;
sbit cs2=P2^6;
sbit cs1=P2^7;

uchar  seg7[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x86,0x8e,0x89,0xbf};		  //共阳数码管段码显示,0-9(0x90),E(0x86),F(0x8e),0xbf代表‘-’

//uchar  seg7[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0XC6,0x8e,0x89,0xbf};		  //共阳数码管段码显示,0-9(0x90),F(0x8e),0xbf代表‘-’
void Segdisplay(uchar num);
void DelayMS(uint x);
void Setdisplay(uchar num);
void Setdisplay1(uchar num);
void Setdisplay2();

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	for(t=120;t>0;t--);
}



void Setdisplay(uchar num)				   //数码管显示程序
{
   	 LCD_DB=seg7[num/100];
	 cs1=0;
	 cs2=1; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;


	 LCD_DB=seg7[num%100/10];
	 cs1=1;
	 cs2=0; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[num%10];
	 cs1=0;
	 cs2=0; 
	 cs3=1;
	 cs4=0;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[11];
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=1;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;
	  

}
void Setdisplay1(uchar num)			   //数码管显示程序
{
   	 LCD_DB=seg7[num/100];
	 cs1=0;
	 cs2=1; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;


	 LCD_DB=seg7[num%100/10];
	 cs1=1;
	 cs2=0; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[num%10];
	 cs1=0;
	 cs2=0; 
	 cs3=1;
	 cs4=0;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[12];
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=1;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;
	  
}

void Setdisplay2()
{
   	 LCD_DB=seg7[13];
	 cs1=0;
	 cs2=1; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;


	 LCD_DB=seg7[13];
	 cs1=1;
	 cs2=0; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[13];
	 cs1=0;
	 cs2=0; 
	 cs3=1;
	 cs4=0;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[13];
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=1;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;	  
}


void Setdisplay3()   //数码管显示程序EEEE
{
   	 LCD_DB=seg7[10];
	 cs1=0;
	 cs2=1; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;


	 LCD_DB=seg7[10];
	 cs1=1;
	 cs2=0; 
	 cs3=0;
	 cs4=0;
	 DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[10];
	 cs1=0;
	 cs2=0; 
	 cs3=1;
	 cs4=0;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;

	 LCD_DB=seg7[10];
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=1;
     DelayMS(1);
	 cs1=0;
	 cs2=0; 
	 cs3=0;
	 cs4=0;	  
}

 */






