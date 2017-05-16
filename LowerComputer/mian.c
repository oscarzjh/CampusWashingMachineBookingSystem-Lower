       		             				   						   			          
#include <reg52.h> 
#include <intrins.h>  
#include <math.h>    //Keil library    
#include <stdio.h>   //Keil library  
#include <LCD1602.h>   //Keil library  
#include<set.h>
//void tempconve();		

/* void motor_start();	   //�����ʼת��
void motor_stop();	   //���ֹͣת�� */

//#include<bee.h>
#define uchar unsigned char 
#define uint unsigned int 
//uchar Currenttemp=0;
uint sec=0;
uint i;

uchar motorflag=1;
sbit LED1=P2^3;			  //ϴ��״ָ̬ʾ��1
sbit LED2=P2^2;			   //ϴ��״ָ̬ʾ��2
sbit LED3=P2^1;			  //ϴ��״ָ̬ʾ��3
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
	IN2=1;			//ϴ�»����ת��

}

void motor_stop()
{
  
	IN1=0;
	IN2=0;			//ϴ�»����ֹͣת��

} */
void main()
{
    TMOD=0X21;				  //��ʱ��0Ϊ��ʽ1����ʱ��1Ϊ��ʽ2 �Զ���װ
	TH0  = (65535-5000)/256;		//��ʱ����װ��ֵ
	TL0  = (65535-5000)%256;		//��ʱ����װ��ֵ
	
	
	
	//���ڳ�ֵ
	SCON=0x50; //���ô���Ϊ������ʽ1
	PCON=0x00; //SMOD=0��32��Ƶ
	TH1=0xfd;
	TL1=0xfd; //������Ϊ9600 bit/s
/*	
	//�ж����ȼ�����
	PS=1; //�������ȼ�
	PT1=1;
	PT0=0; */
	
	washflag=0;
	waterflag=0;
	IN1=0;
	IN2=0;  //��ʼ��ϴ��
	SBUF=0xfb;
	
	yuyue_flag=0;
	is_startkey_effect=1;
	
	//waterdoor=0;  //p1.7 �ǰ���Ĭ�Ϲر�
	doorcloseflag=1;  //�ǰ���Ĭ�Ϲر�
	waterdoorkeypress=0;
	
	IE = 0x9a; //ES=1���ڽ����ж�,EA=1ȫ���ж�,ET1=1,ET0=1
	i=0;
	TR0  = 1;						//����ʱ��0
	TR1  = 1;						//����ʱ��1



	while (1)            //��ѭ��
	{
		/* if (yuyue_flag==0)
			{ */
		while(yuyue_flag==0)					 
		{
			if(is_startkey_effect==1)
			{
				keyhandle();			  //������⡤
				timer0_serv();			  //��ʱɨ�谴��
			}		      
			ledjudje();               //LED������ϴ�µĹ�������
			
			if(displaymode==0)		//��ʾȫ�㣬Ϊ��������ʾ
			{
				Setdisplay(0);
			}
			else if(displaymode==1)		 	//��ʾ����ϴ��ʱ��
			{
				Setdisplay(setmaxtemp);
			}
			else if(displaymode==2)		  	//��ʾ������ˮʱ��
			{
				Setdisplay1(setmintemp);
			}
			
 			waterdoorkey();
			
			
			
			if(waterdoorkeypress_flag==1)
			{	
				waterdoorkeypress_flag=0;
				i=(i+1)%2;   //i������waterdoorkey����������һ��Ϊ���ţ��ٰ�һ��Ϊ���š���ʼΪ0
				if(i==1)
				{
					//SBUF=0xff;//����λ����0xff������δ��
					doorcloseflag=0;   //�Ŵ�
					IN1=0;
					IN2=0;
				}
				else
				{
					doorcloseflag=1;   //�Źر�
					IN1=0;
					IN2=1;
				}
		
			}

	


/* 			if(waterdoor==1)					//��ˮ�ǰ��
			{
				doorcloseflag=0;				   //ֹͣϴ��  doorcloseflag=1Ϊ�ſ�
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
		if(yuyue_flag==1&&washflag==0&&waterflag==0)    //yuyue_flag=1������ԤԼ���ҵ�ǰû���·���ϴ
		{
/* 			doorcloseflag=1;  //�ǰ���Ĭ�Ϲر�
			waterdoorkeypress=0;
			i=0;
			 */
			
			
			is_baoliu_flag=1;
			is_startkey_effect=0;

			//DelayMS(10000);  //�ȴ�10min����10sΪ����ʾ
			displaymode=1;
			Setdisplay2();			
			
			//while(yuyue_flag)
				
			//��λ�����ȴ�10min,���û�е㿪ʼ��������is_baoliu_flag=0���������ж���yuyue_flag=0
			
			
			while (is_baoliu_flag==1)   //��λ�����Ϳ�ʼϴ�º���is_baoliu_flag=0����ʼϴ��
			{
				//displaymode=1;
				Setdisplay2();	
				if(yuyue_flag==0)
				{
					/* IN1=0;
					IN2=0;  //���ֹͣת��
					washflag=0;
					waterflag=0;   //ò�ƶ��࣬��Ϊ��״̬�²�����Ϊ��ϴ */
					displaymode=0;
					is_startkey_effect=1;
					setmintemp=10;
					setmaxtemp=50;
					SBUF = 0xfa;
					//while(!TI);
					//TI = 0;     //����0xfa����λ������ǰϴ�»�����
					break;
				}					
			};

			
			if (yuyue_flag==1)
			{
				if (doorcloseflag==0) //�ſ�ʱ
				{
					SBUF = 0xff;
					//while(!TI);
					//TI = 0;     //����0xff����λ������ǰ��δ��
					while(doorcloseflag==0)//���Źؽ���ѭ��
					{	
						waterdoorkey();
						if(waterdoorkeypress_flag==1)  //����waterdoorkey
						{
							waterdoorkeypress_flag=0;
							SBUF=0xf9;//����λ����0xff�������ѹ�
							doorcloseflag=1;  //��ʼ�����Źز�ϴ��
						}
					
					}
				}
				
				DelayMS(10);  //�ӳ�10msΪ��ʹsetmaxtemp��setmintemp�����ú�
				washflag=1;
				
				SBUF = 0xfe;
				//while(!TI);
				//TI = 0;     //����0xfe����λ������ǰϴ�»����·���ϴ
				
				IN1=0;
				IN2=1;			//ϴ�»����ת��
				timeflag=5;
				halftime= setmaxtemp/2;
				i=0;
			   
				while(yuyue_flag)   
				{
					ledjudje();
					if(displaymode==1)		 	//��ʾϴ��ʱ��
					{
						Setdisplay(setmaxtemp);
					}
					else if(displaymode==2)		  	//��ʾ��ˮʱ��
					{
						Setdisplay1(setmintemp);
					}
					
					
					waterdoorkey();
					if(waterdoorkeypress_flag==1)
					{
						waterdoorkeypress_flag=0;
						i=(i+1)%2;   //i������waterdoorkey����������һ��Ϊ���ţ��ٰ�һ��Ϊ���š���ʼΪ0
						if(i==1)
						{
							SBUF=0xff;//����λ����0xff������δ��
							doorcloseflag=0;   //�Ŵ�
							IN1=0;
							IN2=0;
						}
						else
						{
							SBUF=0xf9;//����λ����0xf9�������ѹ�
							doorcloseflag=1;   //�Źر�
							IN1=0;
							IN2=1;
						}
						
					}

	
					
							
/* 					if(waterdoor==0)  //����waterdoorkey
					{
						waterdoorkeypress=1;  //����waterdoorkey
						i=(i+1)%2;   //i������waterdoorkey����������һ��Ϊ���ţ��ٰ�һ��Ϊ���š���ʼΪ0
					}

					 
					if(waterdoorkeypress==1)
					{
						if(i==1)
						{
							doorcloseflag=0;   //�Ŵ�
							IN1=0;
							IN2=0;
						}
						else
						{
							doorcloseflag=1;   //�Źر�
							IN1=0;
							IN2=1;
						}
						waterdoorkeypress=0;
					}
					
					 */
					
/* 					if(waterdoor==1)					//��ˮ�ǰ��
					{
						doorcloseflag=0;				   //ֹͣϴ��
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
 void ledjudje()				   //LED������ϴ�µĹ�������
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




void DSY_Refresh() interrupt 1			  //��ʱ��0�жϳ�����������ϴ��ʱ�䣬��ˮʱ��
{
    //ET0=0;  //�����жϹص�����Ӧ,���Բ�д�˾�
 	TH0  = (65535-1000)/256;
	TL0  = (65535-1000)%256;   //��ʼװ65535-5000����5ms��ÿ��Interrupt��װ��ֵ65535-1000�����Ժ�ϵͳÿ1ms�ж�һ��
	if (doorcloseflag==1)  //�Ź�ʱ
	{
		if(washflag==1)   //׼��ϴ��
		{
			is_startkey_effect=0;
			sec++;     //��ʼsec=0
			if(sec>=1000)   //1ms*1000��ÿ1sΪһ����
			{
				sec=0;    		
				timeflag++;    //��ʼtimeflag=5,ÿ��timeflag++
				
				if(motorflag==1)   //��ʼmotorflag=1
				{
				   if(timeflag>=5)  //ÿ5������ת
				   { 
					 IN1=!IN1;
					 IN2=!IN2;			//ϴ�»��������ת��
					 timeflag=0;
				   }
				}
				 
	/* 			else   //motorflag==0,
				{
				   if(timeflag>=7)    //ÿ7������ת
				   { 
					 IN1=!IN1;
					 IN2=!IN2;			//ϴ�»��������ת��
					 timeflag=0;
				   }
				}
				*/
				setmaxtemp--;
				
	/* 			if(halftime==setmaxtemp)
				{
					motorflag=0;		 
				}  */
				 
				if(setmaxtemp==0)   //ϴ��ʱ�����
				{
					washflag=0;
					setmaxtemp=50;
					waterflag=1;    //��ʼ��ˮ��־��1
					sec=0;  
					displaymode=2;  //�л�����ˮʱ����ʾģʽ
					//waterflag=0; �������
					IN1=0;
					IN2=0;
				}
		  
			}
		}
		
		if(waterflag==1)   //��ʼ��ˮ
		{
			if(doorcloseflag==1)  //�Ź�ʱ
			{
				sec++; //sec��setmaxtemp==0ʱ���Ѿ���0
				IN1=0;
				IN2=1;   //һֱ��ת
				if(sec>=1000)  //ÿ��
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
						DelayMS(1000);// �ȴ�1s
						displaymode=0;  //�л�����ʼ��ʾģʽ����ʱӦ��ȫΪ0
						
						is_baoliu_flag=0;   //�˾�ɲ�д
						is_startkey_effect=1;
						//beep(); beep��������ϴ�¹��̽���
						if (yuyue_flag==1)
							SBUF = 0xfd;  //ԤԼ�Ľ���ϴ��
						else 
							SBUF = 0xfb;  //��ԤԼ�Ľ���ϴ��
						yuyue_flag=0;
						//while(!TI);
						//TI = 0;     //����0x55����λ������ǰϴ�»�����
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
	unsigned char temp;          //������ʱ���� 
	if(RI)                        //�ж��ǽ����жϲ���
    {
		RI=0;                //��־λ����
		if (washflag==0&&waterflag==0)   //��ǰû��ϴ��
		{
			temp=SBUF;                 //���뻺������ֵ
			if (temp==0xff)  //���յ���λ��ԤԼ�����ź�0xff
			{
				yuyue_flag=1;
			}
			else if (temp==0xfe)  //���յ���λ����ʱ��ȡ��ԤԼ(����;�ж�ϴ��)�ź�0x��֮ǰ����д��0xf8<temp<0xff��������
			{
				yuyue_flag=0;
			}
			else if(temp==0xfb)
			{
				startflag=1;         //��λ����0xfb�������ϴ�£��ֶ�����ϴ�µĽ���ʱ�������ԤԼ��ʼʱ���ͻ
			}	
			else if(temp==0xfa)
			{
				startflag=0;         //��λ����0xfa����error�źţ��ֶ�����ϴ�µĽ���ʱ�������ԤԼ��ʼʱ���ͻ
			}
			else  //���͵�Ϊʱ������֡������Ϊ������֡���м�delay����λ�����
			{
				if(temp<128)   //ϴ��ʱ�������120min���ź�Ϊ��0��ͷ������7λΪʱ��
				{setmaxtemp=temp;}
				else          //��ˮʱ�������120min���ź�Ϊ��1��ͷ������7λΪʱ��
				{
					setmintemp=temp-128;
					is_baoliu_flag=0;
				}			
			}
		}
	}
	
   if(TI)      {while(!TI);TI=0;}                  //����Ƿ��ͱ�־λ������
   
		
	//EA=1;
}







