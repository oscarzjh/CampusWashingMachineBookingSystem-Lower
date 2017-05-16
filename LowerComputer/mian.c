       		             				   						   			          
#include <reg52.h> 
#include <intrins.h>  
#include <math.h>    //Keil library    
#include <stdio.h>   //Keil library  
#include <LCD1602.h>   //Keil library  
#include<set.h>
//void tempconve();		

/* void motor_start();	   //电机开始转动
void motor_stop();	   //电机停止转动 */

//#include<bee.h>
#define uchar unsigned char 
#define uint unsigned int 
//uchar Currenttemp=0;
uint sec=0;
uint i;

uchar motorflag=1;
sbit LED1=P2^3;			  //洗衣状态指示灯1
sbit LED2=P2^2;			   //洗衣状态指示灯2
sbit LED3=P2^1;			  //洗衣状态指示灯3
//sbit relay=P3^2;




//sbit bee=P3^0;

/* sbit di=P3^7;
di=0;
 */
//void tempconve();
void ledjudje();
//void beep();

/* void motor_start()
{
    
	IN1=0;
	IN2=1;			//洗衣机电机转动

}

void motor_stop()
{
  
	IN1=0;
	IN2=0;			//洗衣机电机停止转动

} */
void main()
{
    TMOD=0X21;				  //定时器0为方式1，定时器1为方式2 自动重装
	TH0  = (65535-5000)/256;		//定时器零装初值
	TL0  = (65535-5000)%256;		//定时器零装初值
	
	
	
	//串口初值
	SCON=0x50; //设置串口为工作方式1
	PCON=0x00; //SMOD=0，32分频
	TH1=0xfd;
	TL1=0xfd; //波特率为9600 bit/s
/*	
	//中断优先级设置
	PS=1; //串口优先级
	PT1=1;
	PT0=0; */
	
	washflag=0;
	waterflag=0;
	IN1=0;
	IN2=0;  //初始不洗衣
	SBUF=0xfb;
	
	yuyue_flag=0;
	is_startkey_effect=1;
	
	//waterdoor=0;  //p1.7 盖板门默认关闭
	doorcloseflag=1;  //盖板门默认关闭
	waterdoorkeypress=0;
	
	IE = 0x9a; //ES=1串口接收中断,EA=1全局中断,ET1=1,ET0=1
	i=0;
	TR0  = 1;						//开定时器0
	TR1  = 1;						//开定时器1



	while (1)            //主循环
	{
		/* if (yuyue_flag==0)
			{ */
		while(yuyue_flag==0)					 
		{
			if(is_startkey_effect==1)
			{
				keyhandle();			  //按键检测·
				timer0_serv();			  //定时扫描按键
			}		      
			ledjudje();               //LED灯随着洗衣的过程跳动
			
			if(displaymode==0)		//显示全零，为开机后显示
			{
				Setdisplay(0);
			}
			else if(displaymode==1)		 	//显示设置洗衣时间
			{
				Setdisplay(setmaxtemp);
			}
			else if(displaymode==2)		  	//显示设置脱水时间
			{
				Setdisplay1(setmintemp);
			}
			
 			waterdoorkey();
			
			
			
			if(waterdoorkeypress_flag==1)
			{	
				waterdoorkeypress_flag=0;
				i=(i+1)%2;   //i代表按下waterdoorkey次数，按下一次为开门，再按一次为关门。初始为0
				if(i==1)
				{
					//SBUF=0xff;//给上位机发0xff代表门未关
					doorcloseflag=0;   //门打开
					IN1=0;
					IN2=0;
				}
				else
				{
					doorcloseflag=1;   //门关闭
					IN1=0;
					IN2=1;
				}
		
			}

	


/* 			if(waterdoor==1)					//脱水盖板打开
			{
				doorcloseflag=0;				   //停止洗衣  doorcloseflag=1为门开
				IN1=0;
				IN2=0;
			}
			else
			{
				doorcloseflag=1;
			} 
			
			 */
			
			
		}
			/* } */
		if(yuyue_flag==1&&washflag==0&&waterflag==0)    //yuyue_flag=1代表有预约，且当前没有衣服在洗
		{
/* 			doorcloseflag=1;  //盖板门默认关闭
			waterdoorkeypress=0;
			i=0;
			 */
			
			
			is_baoliu_flag=1;
			is_startkey_effect=0;

			//DelayMS(10000);  //等待10min，以10s为例演示
			displaymode=1;
			Setdisplay2();			
			
			//while(yuyue_flag)
				
			//上位机做等待10min,如果没有点开始，即不置is_baoliu_flag=0，跳出，中断置yuyue_flag=0
			
			
			while (is_baoliu_flag==1)   //上位机发送开始洗衣后置is_baoliu_flag=0，开始洗衣
			{
				//displaymode=1;
				Setdisplay2();	
				if(yuyue_flag==0)
				{
					/* IN1=0;
					IN2=0;  //电机停止转动
					washflag=0;
					waterflag=0;   //貌似多余，因为此状态下不可能为在洗 */
					displaymode=0;
					is_startkey_effect=1;
					setmintemp=10;
					setmaxtemp=50;
					SBUF = 0xfa;
					//while(!TI);
					//TI = 0;     //发送0xfa给上位机代表当前洗衣机空闲
					break;
				}					
			};

			
			if (yuyue_flag==1)
			{
				if (doorcloseflag==0) //门开时
				{
					SBUF = 0xff;
					//while(!TI);
					//TI = 0;     //发送0xff给上位机代表当前门未关
					while(doorcloseflag==0)//当门关进入循环
					{	
						waterdoorkey();
						if(waterdoorkeypress_flag==1)  //按下waterdoorkey
						{
							waterdoorkeypress_flag=0;
							SBUF=0xf9;//给上位机发0xff代表门已关
							doorcloseflag=1;  //初始总是门关才洗衣
						}
					
					}
				}
				
				DelayMS(10);  //延迟10ms为了使setmaxtemp、setmintemp都设置好
				washflag=1;
				
				SBUF = 0xfe;
				//while(!TI);
				//TI = 0;     //发送0xfe给上位机代表当前洗衣机有衣服在洗
				
				IN1=0;
				IN2=1;			//洗衣机电机转动
				timeflag=5;
				halftime= setmaxtemp/2;
				i=0;
			   
				while(yuyue_flag)   
				{
					ledjudje();
					if(displaymode==1)		 	//显示洗衣时间
					{
						Setdisplay(setmaxtemp);
					}
					else if(displaymode==2)		  	//显示脱水时间
					{
						Setdisplay1(setmintemp);
					}
					
					
					waterdoorkey();
					if(waterdoorkeypress_flag==1)
					{
						waterdoorkeypress_flag=0;
						i=(i+1)%2;   //i代表按下waterdoorkey次数，按下一次为开门，再按一次为关门。初始为0
						if(i==1)
						{
							SBUF=0xff;//给上位机发0xff代表门未关
							doorcloseflag=0;   //门打开
							IN1=0;
							IN2=0;
						}
						else
						{
							SBUF=0xf9;//给上位机发0xf9代表门已关
							doorcloseflag=1;   //门关闭
							IN1=0;
							IN2=1;
						}
						
					}

	
					
							
/* 					if(waterdoor==0)  //按下waterdoorkey
					{
						waterdoorkeypress=1;  //按下waterdoorkey
						i=(i+1)%2;   //i代表按下waterdoorkey次数，按下一次为开门，再按一次为关门。初始为0
					}

					 
					if(waterdoorkeypress==1)
					{
						if(i==1)
						{
							doorcloseflag=0;   //门打开
							IN1=0;
							IN2=0;
						}
						else
						{
							doorcloseflag=1;   //门关闭
							IN1=0;
							IN2=1;
						}
						waterdoorkeypress=0;
					}
					
					 */
					
/* 					if(waterdoor==1)					//脱水盖板打开
					{
						doorcloseflag=0;				   //停止洗衣
						IN1=0;
						IN2=0;
					}
					else
					{
						doorcloseflag=1;
					}
					 */
				}
			}
			
		}
	}
	
 }
 void ledjudje()				   //LED灯随着洗衣的过程跳动
 {
 	 if(IN1==1)					   
	 {
	  	LED1=0;
		LED2=1;
		LED3=1;
	 }
	 else if(IN2==1)
	 {
	  	LED1=1;
		LED2=0;
		LED3=1;
	 }
	 else if(IN1==0&&IN2==0)
	 {
	  	LED1=1;
		LED2=1;
		LED3=0;
	 }
 
 }




void DSY_Refresh() interrupt 1			  //定时器0中断程序，用来计算洗衣时间，脱水时间
{
    //ET0=0;  //自身中断关掉不响应,可以不写此句
 	TH0  = (65535-1000)/256;
	TL0  = (65535-1000)%256;   //初始装65535-5000，即5ms，每次Interrupt后装初值65535-1000，即以后系统每1ms中断一次
	if (doorcloseflag==1)  //门关时
	{
		if(washflag==1)   //准备洗衣
		{
			is_startkey_effect=0;
			sec++;     //初始sec=0
			if(sec>=1000)   //1ms*1000即每1s为一周期
			{
				sec=0;    		
				timeflag++;    //初始timeflag=5,每秒timeflag++
				
				if(motorflag==1)   //初始motorflag=1
				{
				   if(timeflag>=5)  //每5秒电机反转
				   { 
					 IN1=!IN1;
					 IN2=!IN2;			//洗衣机电机反向转动
					 timeflag=0;
				   }
				}
				 
	/* 			else   //motorflag==0,
				{
				   if(timeflag>=7)    //每7秒电机反转
				   { 
					 IN1=!IN1;
					 IN2=!IN2;			//洗衣机电机反向转动
					 timeflag=0;
				   }
				}
				*/
				setmaxtemp--;
				
	/* 			if(halftime==setmaxtemp)
				{
					motorflag=0;		 
				}  */
				 
				if(setmaxtemp==0)   //洗衣时间结束
				{
					washflag=0;
					setmaxtemp=50;
					waterflag=1;    //开始脱水标志置1
					sec=0;  
					displaymode=2;  //切换至脱水时间显示模式
					//waterflag=0; 错误句子
					IN1=0;
					IN2=0;
				}
		  
			}
		}
		
		if(waterflag==1)   //开始脱水
		{
			if(doorcloseflag==1)  //门关时
			{
				sec++; //sec在setmaxtemp==0时候已经置0
				IN1=0;
				IN2=1;   //一直正转
				if(sec>=1000)  //每秒
				{
				  sec=0;
				  setmintemp--;
				  
				   if(setmintemp==0)
					{
						waterflag=0;
						setmintemp=10;
						sec=0;
						IN1=0;
						IN2=0;
						DelayMS(1000);// 等待1s
						displaymode=0;  //切换至开始显示模式，此时应该全为0
						
						is_baoliu_flag=0;   //此句可不写
						is_startkey_effect=1;
						//beep(); beep代表整个洗衣过程结束
						if (yuyue_flag==1)
							SBUF = 0xfd;  //预约的结束洗衣
						else 
							SBUF = 0xfb;  //非预约的结束洗衣
						yuyue_flag=0;
						//while(!TI);
						//TI = 0;     //发送0x55给上位机代表当前洗衣机空闲
					}
				}	  
			}
		}
	}
	//ET0=1;
}

/* void beep()										
{
	uchar i,j;
	for(i=0;i<100;i++)
	{
	     bee=0;
		 DelayMS(50);
		 bee=1;
		DelayMS(50);
	}

} */


void uart() interrupt 4
{
	//EA=0;
	unsigned char temp;          //定义临时变量 
	if(RI)                        //判断是接收中断产生
    {
		RI=0;                //标志位清零
		if (washflag==0&&waterflag==0)   //当前没有洗衣
		{
			temp=SBUF;                 //读入缓冲区的值
			if (temp==0xff)  //接收到上位机预约来临信号0xff
			{
				yuyue_flag=1;
			}
			else if (temp==0xfe)  //接收到上位机超时、取消预约(、中途中断洗衣)信号0x。之前错误写成0xf8<temp<0xff！！！！
			{
				yuyue_flag=0;
			}
			else if(temp==0xfb)
			{
				startflag=1;         //上位机发0xfb代表可以洗衣，手动设置洗衣的结束时间和他人预约开始时间冲突
			}	
			else if(temp==0xfa)
			{
				startflag=0;         //上位机发0xfa代表error信号，手动设置洗衣的结束时间和他人预约开始时间冲突
			}
			else  //发送的为时间设置帧，必须为连续两帧，中间delay由上位机完成
			{
				if(temp<128)   //洗衣时间最长设置120min，信号为以0开头，后面7位为时间
				{setmaxtemp=temp;}
				else          //脱水时间最长设置120min，信号为以1开头，后面7位为时间
				{
					setmintemp=temp-128;
					is_baoliu_flag=0;
				}			
			}
		}
	}
	
   if(TI)      {while(!TI);TI=0;}                  //如果是发送标志位，清零
   
		
	//EA=1;
}







