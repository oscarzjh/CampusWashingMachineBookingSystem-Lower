	   
#define uchar unsigned char
#define uint  unsigned int
sbit startkey =P1^3;
sbit stopkey =P1^4;
sbit zerokey =P1^5 ; 
sbit guangbiaooffkey =P1^6 ; 
sbit IN1=P1^1;
sbit IN2=P1^0;   //����������Ŷ���	
uchar startkeypress=0;  //��ʼ�������±�־λ   
uchar stopkeypress=0;  //ֹͣ�������±�־λ   
uchar guangbiaokeypress=0;  //���㰴�����±�־λ 

uchar doorcloseflag;   //ϴ�»��Źر�־

sbit waterdoor=P1^7;	 //ϴ�»��ǰ�
bit key_temp4;
bit waterdoorkeypress=0;
bit waterdoorkeypress_flag;

bit is_baoliu_flag;			//����ǰϴ���Ƿ��ڱ�ԤԼ����ʱ����
bit is_startkey_effect;		   //startkey�����Ƿ���Ч
bit yuyue_flag;  //ϴ������ԤԼ������=1 �ô��ڷ�ϴ��ʱ�����ݣ���δԤԼ�����ʹ����=0 ��keyhandle()
 
uchar zerokeypress=0; 
uchar key_temp0;
uchar key_temp1;
uchar key_temp2;
uchar key_temp3;
//uchar keycan=0;
uchar startkeypress_flag=0;  //��ʼ�������±�־λ   
uchar stopkeypress_flag=0;  //ֹͣ�������±�־λ   
uchar zerokeypress_flag=0;  //���㰴�����±�־λ 
uchar guangbiaokeypress_flag=0;  //���㰴�����±�־λ 
//uchar guangbiaoflag=0;
uchar washflag;    //��ʼϴ�±�־
uchar waterflag;  //��ʼ��ˮ��־
uchar setmintemp=10;
uchar setmaxtemp=50;
uchar displaymode=0;
uint timeflag;
uchar halftime;
void DelayShow(uint x);
uchar startflag=20;//�������ó�ֵ

void DelayMSShow(uint x)
{
 	uchar t;
	while(x--)
	{
		for(t=120;t>0;t--)
		{Setdisplay3();}
	}
}

void keyscale()						//����ɨ��
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

void keyhandle()				 //�趨ϴ�º���ˮʱ��
{	
	startflag=20;
	if (washflag==0&&waterflag==0)  //������ǰδ��ϴ�¡���ˮ�Ұ�����Ч��־Ϊ��Чʱ
	{
		if(startkeypress_flag==1)		 //���ð�������
		{		  
			startkeypress_flag=0;	
			displaymode++;
			if(displaymode>=3)
			{
				displaymode=0;
			}		
		}
		if(stopkeypress_flag==1)		 //ʱ��+��������
		{		  
			stopkeypress_flag=0;	
			if(displaymode==1)
			{
			   setmaxtemp++;   //�趨ϴ��ʱ��
			   if(setmaxtemp>120)
			   {
			   	   setmaxtemp=0;
			   }	
			}
			else if(displaymode==2)
			{
			   setmintemp++;   //�趨��ˮʱ�䣻
			   if(setmintemp>120)
			   {
			   	   setmintemp=0;
			   }	
			}
			
			
					
		}
		if(zerokeypress_flag==1)		 //ʱ��-��������
		{
			zerokeypress_flag=0;
			if(displaymode==1)
			{
			   setmaxtemp--;   //�趨ϴ��ʱ��
			   if(setmaxtemp<=0)
			   {
			   	   setmaxtemp=120;
			   }	
			}		
			else if(displaymode==2)
			{
			   setmintemp--;    //�趨��ˮʱ�䣻
			   if(setmintemp<=0)
			   {
			   	   setmintemp=120;
			   }	
			}							
		}
		if(guangbiaokeypress_flag==1&&doorcloseflag==1)		//ϴ�¿�ʼʱ�䰴��,�Ź�
		{		   
			guangbiaokeypress_flag=0;
			
			SBUF = setmaxtemp;
			//while(!TI);
			Delayk(20);
			SBUF = setmintemp+0x80;
			//while(!TI);//����д����
			while(startflag==20);   //�ȴ���λ����startflagΪ 0��1
			if (startflag==0)  //��λ��������
			{
				setmintemp=10;
				setmaxtemp=50;
				//Setdisplay3();     
				DelayMSShow(3); //�������ʾEEEE
				displaymode=0;

			}
			else if(startflag==1)
			{
				displaymode=1;	
				washflag=1;
			
				SBUF = 0xfc;
			//while(!TI);
			//TI = 0;     //����0xfc����λ������ǰϴ�»����·���ϴ  
			
				IN1=0;
				IN2=1;			//ϴ�»����ת��
				timeflag=5;
				halftime= setmaxtemp/2;
			}
		}
	}			
}


void timer0_serv()						 //�������
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
	
	if(waterdoor==0)  //����waterdoorkey
	{
		waterdoorkeypress=1;  //����waterdoorkey
		
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

