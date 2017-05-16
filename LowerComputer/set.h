	   
#define uchar unsigned char
#define uint  unsigned int
sbit startkey =P1^3;
sbit stopkey =P1^4;
sbit zerokey =P1^5 ; 
sbit guangbiaooffkey =P1^6 ; 
sbit IN1=P1^1;
sbit IN2=P1^0;   //电机控制引脚定义	
uchar startkeypress=0;  //开始按键按下标志位   
uchar stopkeypress=0;  //停止按键按下标志位   
uchar guangbiaokeypress=0;  //归零按键按下标志位 

uchar doorcloseflag;   //洗衣机门关标志

sbit waterdoor=P1^7;	 //洗衣机盖板
bit key_temp4;
bit waterdoorkeypress=0;
bit waterdoorkeypress_flag;

bit is_baoliu_flag;			//代表当前洗衣是否在被预约保留时间内
bit is_startkey_effect;		   //startkey按下是否有效
bit yuyue_flag;  //洗衣人是预约的人来=1 用串口发洗衣时间数据，是未预约的随机使用者=0 用keyhandle()
 
uchar zerokeypress=0; 
uchar key_temp0;
uchar key_temp1;
uchar key_temp2;
uchar key_temp3;
//uchar keycan=0;
uchar startkeypress_flag=0;  //开始按键按下标志位   
uchar stopkeypress_flag=0;  //停止按键按下标志位   
uchar zerokeypress_flag=0;  //归零按键按下标志位 
uchar guangbiaokeypress_flag=0;  //归零按键按下标志位 
//uchar guangbiaoflag=0;
uchar washflag;    //开始洗衣标志
uchar waterflag;  //开始脱水标志
uchar setmintemp=10;
uchar setmaxtemp=50;
uchar displaymode=0;
uint timeflag;
uchar halftime;
void DelayShow(uint x);
uchar startflag=20;//随意设置初值

void DelayMSShow(uint x)
{
 	uchar t;
	while(x--)
	{
		for(t=120;t>0;t--)
		{Setdisplay3();}
	}
}

void keyscale()						//按键扫描
{
	if(startkey==0)
	{
		 startkeypress=1;
		 
	}
	else
	{
		  startkeypress=0;
	}
	if(stopkey==0)
	{
		 stopkeypress=1;
	}
	else
	{
		  stopkeypress=0;
	}
	if(zerokey==0)
	{
		 zerokeypress=1;
	}
	else
	{
		  zerokeypress=0;
	}
	if(guangbiaooffkey==0)
	{
		guangbiaokeypress=1;
	}
	else
	{
		guangbiaokeypress=0;
	}
		
 }

void keyhandle()				 //设定洗衣和脱水时间
{	
	startflag=20;
	if (washflag==0&&waterflag==0)  //仅当当前未在洗衣、脱水且按键有效标志为有效时
	{
		if(startkeypress_flag==1)		 //设置按键按下
		{		  
			startkeypress_flag=0;	
			displaymode++;
			if(displaymode>=3)
			{
				displaymode=0;
			}		
		}
		if(stopkeypress_flag==1)		 //时间+按键按下
		{		  
			stopkeypress_flag=0;	
			if(displaymode==1)
			{
			   setmaxtemp++;   //设定洗衣时间
			   if(setmaxtemp>120)
			   {
			   	   setmaxtemp=0;
			   }	
			}
			else if(displaymode==2)
			{
			   setmintemp++;   //设定脱水时间；
			   if(setmintemp>120)
			   {
			   	   setmintemp=0;
			   }	
			}
			
			
					
		}
		if(zerokeypress_flag==1)		 //时间-按键按下
		{
			zerokeypress_flag=0;
			if(displaymode==1)
			{
			   setmaxtemp--;   //设定洗衣时间
			   if(setmaxtemp<=0)
			   {
			   	   setmaxtemp=120;
			   }	
			}		
			else if(displaymode==2)
			{
			   setmintemp--;    //设定脱水时间；
			   if(setmintemp<=0)
			   {
			   	   setmintemp=120;
			   }	
			}							
		}
		if(guangbiaokeypress_flag==1&&doorcloseflag==1)		//洗衣开始时间按下,门关
		{		   
			guangbiaokeypress_flag=0;
			
			SBUF = setmaxtemp;
			//while(!TI);
			Delayk(20);
			SBUF = setmintemp+0x80;
			//while(!TI);//不能写！！
			while(startflag==20);   //等待上位机置startflag为 0或1
			if (startflag==0)  //上位机不允许发
			{
				setmintemp=10;
				setmaxtemp=50;
				//Setdisplay3();     
				DelayMSShow(3); //数码管显示EEEE
				displaymode=0;

			}
			else if(startflag==1)
			{
				displaymode=1;	
				washflag=1;
			
				SBUF = 0xfc;
			//while(!TI);
			//TI = 0;     //发送0xfc给上位机代表当前洗衣机有衣服在洗  
			
				IN1=0;
				IN2=1;			//洗衣机电机转动
				timeflag=5;
				halftime= setmaxtemp/2;
			}
		}
	}			
}


void timer0_serv()						 //按键检测
{
     key_temp0=startkeypress;	
	 key_temp1=stopkeypress;
	 key_temp2=zerokeypress;
	 key_temp3=guangbiaokeypress;	 	 	
	 keyscale();
	 if(key_temp0!=startkeypress)
	 {
	     if(startkeypress==1)
		 {
	 	     startkeypress_flag=1;
		 }
	 }
	  if(key_temp1!=stopkeypress)
	 {
	     if(stopkeypress==1)
		 {
	 	   stopkeypress_flag=1;
		 }
	 }
	  if(key_temp2!=zerokeypress)
	 {
	     if(zerokeypress==1)
		 {
	 	 zerokeypress_flag=1;
		 }
	 }
	 if(key_temp3!=guangbiaokeypress)
	 {
	     if(guangbiaokeypress==1)
		 {
	 	 guangbiaokeypress_flag=1;
		 }
	 }
}


void waterdoorkey()
{
	key_temp4=waterdoorkeypress;
	
	if(waterdoor==0)  //按下waterdoorkey
	{
		waterdoorkeypress=1;  //按下waterdoorkey
		
	}
	else
	{
		waterdoorkeypress=0;
	}
	
	if(key_temp4!=waterdoorkeypress)
	{
		if(waterdoorkeypress==1)
		{
			waterdoorkeypress_flag=1;
		}
	}
			
}

