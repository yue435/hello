 /****************************************************
 波形发生器
 ****************************************************/
#include <AT89X51.H>
#include "lcd.h"

/***********************************************************
宏定义参数
**********************************************************/
#define ZHENGXUAN   1
#define JUCHI		 2
#define FANG         3

/*******************************************************************************
全局变量定义和数组定义
*******************************************************************************/
uchar code sin[]={ 0x7F,0x87,0x8F,0x97,0x9F,0xA6,0xAE,0xB5,0xBC,0xC3,0xCA,0xD0,0xD6,0xDC,0xE1,0xE6
                  ,0xEB,0xEF,0xF2,0xF6,0xF8,0xFA,0xFC,0xFD,0xFE,0xFE,0xFE,0xFD,0xFC,0xFA,0xF8,0xF6
                  ,0xF2,0xEF,0xEB,0xE6,0xE1,0xDC,0xD6,0xD0,0xCA,0xC3,0xBC,0xB5,0xAE,0xA6,0x9F,0x97
                  ,0x8F,0x87,0x7F,0x77,0x6F,0x67,0x5F,0x58,0x50,0x49,0x42,0x3B,0x34,0x2E,0x28,0x22
                  ,0x1D,0x18,0x13,0x0F,0x0C,0x08,0x06,0x04,0x02,0x01,0x00,0x00,0x00,0x01,0x02,0x04
                  ,0x06,0x08,0x0C,0x0F,0x13,0x18,0x1D,0x22,0x28,0x2E,0x34,0x3B,0x42,0x49,0x50,0x58
                  ,0x5F,0x67,0x6F,0x77};
uchar code shn[]={ 0x05,0x0a,0x0f,0x14,0x19,0x1e,0x23,0x28,0x2d,0x32,0x37,0x3c,0x41,0x46,0x4b,0x50,
                   0x55,0x5a,0x5f,0x64,0x69,0x6e,0x73,0x78,0x7d,0x82,0x87,0x8c,0x91,0x96,0x9b,0xa0,
				   0xa5,0xaa,0xaf,0xb4,0xb9,0xbe,0xc3,0xc8,0xcd,0xd2,0xd7,0xdc,0xe1,0xe6,0xeb,0xf0,
				   0xf5,0xfa,0xfa,0xf5,0xf0,0xeb,0xe6,0xe1,0xdc,0xd7,0xd2,0xcd,0xc8,0xc3,0xbe,0xb9,
				   0xb4,0xaf,0xaa,0xa5,0xa0,0x9b,0x96,0x91,0x8c,0x87,0x82,0x7d,0x78,0x73,0x6e,0x69,
				   0x64,0x5f,0x5a,0x55,0x50,0x4b,0x46,0x41,0x3c,0x37,0x32,0x2d,0x28,0x23,0x1e,0x19,
				   0x14,0x0f,0x0a,0x05};
uchar code fan[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				  0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
				  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
				  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
				  0xff,0xff,0xff,0xff};
//ucahr code table1[]={"please choose wave"};
uchar code table1[]={"frequ:"};//频率
uchar code table2[]={"ampli:"};//振幅
uchar code table3[]={"wave:"};//波形
uchar code table4[]={"Hz"};
uchar code table5[]={"0123456789"};
uchar code table6[]={"zx"};//正弦波
uchar code table7[]={"sa"};//锯齿波
uchar code table8[]={"fb"};	//方波


//uchar code table9[]={"and press enter"};
uchar table10[5];
uchar state=1;
uint  n=0;
uchar count=1;
uint th0;
uint tl0;
uint frequency;
uint amplitude;
bit FLAG=0;
/*********************************************************************************
管脚定义
*********************************************************************************/




/////////////////////////////////////////////////////////////////////////////////
//波形发送：方波部分
////////////////////////////////////////////////////////////////////////////////

void timer0(void) interrupt 1 using 2
{TL0=tl0;
 TH0=th0;
 //TH0=(65535-5)/256;
 //TL0=(65535-5)%256;
 //scan=1;
 //counter++;
 //if(counter==20)
  //{counter=0;
  //enabledis=1;
  //}
  FLAG=1;
}

void init(void)
{TMOD=0x01;   //16位定时器
 EA=1;
 ET0=1;
 frequency=5;
 //th0=(65535-25)/256;
 //tl0=(65535-25)%256;
 th0=(65535-20000/frequency)>>8;
 tl0=(65535-20000/frequency)%256;
 TH0=th0;
 TL0=tl0;
 //SCON=0X00;
		}





/*///////////////////////////////////////////////////////////////////////
 函数名： ACSII转换函数
 功能：    
 返回值： 无
 注意：	  无

//////////////////////////////////////////////////////////////////////*/
asc_change(int f) 
 {
 table10[3]=0x00;
 table10[2]=f%10+0x30;
 table10[1]=f/10%10+0x30;
 table10[0]=f/100+0x30;
 
 }


/*///////////////////////////////////////////////////////////////////////
 函数名： 数字选择函数
 功能：    
 返回值： 无
 注意：	  count对应的是频率设置还是幅度设置

//////////////////////////////////////////////////////////////////////*/
select(uchar x)
{while((P1&0xf0)!=0xf0);
 n=n*10+x;
 asc_change( n);
 
 if(count=1)
 {
  frequency=0.41048421+n*0.98452722+(n*n)*(0.00031684079);
  
 lcd_dis(table10,0x86);}
 
 else if(count=2)
 {amplitude=n;
 lcd_dis(table10,0xc5);}
 }
/*///////////////////////////////////////////////////////////////////////
 函数名： 波形选择显示
 功能：    
 返回值： 无
 注意：	  state是指当前对应的是什么波形

//////////////////////////////////////////////////////////////////////*/
 wave(uchar t)
 {while((P1&0xf0)!=0xf0);
 if(t==1)
 lcd_dis(table6,0xce); //方波
 else if(t==2)
 lcd_dis(table7,0xce); //锯齿波
 else if(t==3)
 lcd_dis(table8,0xce); //正弦波
 state=t;//状态为t
 }
 /*///////////////////////////////////////////////////////////////////////
 函数名： 确定函数
 功能：    
 返回值： 无
 注意：	  无

//////////////////////////////////////////////////////////////////////*/
enter()
{
 while((P1&0xf0)!=0xf0);
if(count==1)
{//frequency=100;
 th0=(65535-20000/frequency)>>8;
 tl0=(65535-20000/frequency)%256;
 TH0=th0;
 TL0=tl0;
 TR0=1;
 n=0;}
else if(count==2)
{}
}
/*///////////////////////////////////////////////////////////////////////
 函数名： 键盘扫描函数
 功能：    
 返回值： 无
 注意：	  返回具体键位地址

//////////////////////////////////////////////////////////////////////*/
uchar key(void)    //键盘扫描
{uchar sccode,recode;
 //P1=0xf0;
if((P1&0xf0)!=0xf0)
{delay(10);
if((P1&0xf0)!=0xf0)
{delay(10);
if((P1&0xf0)==0xf0);
sccode=0xfe;
while((sccode&0x10)!=0)
{P1=sccode;
if((P1&0xf0)!=0xf0)
{recode=(P1&0xf0)|0x0f;
P1=0xf0;
return((~sccode)+(~recode));
    }
 else
 sccode=(sccode<<1)|0x01;
 }
     }
        }
P1=0xf0;
	return(0);
	}
/*///////////////////////////////////////////////////////////////////////
 函数名： 键位对应函数
 功能：    
 返回值： 无
 注意：	  无

//////////////////////////////////////////////////////////////////////*/
sweep()
{uchar i;
i=key();

{
switch(i)
{
case 0x11:TR0=0;select(1);break; 
case 0x21:TR0=0;select(2);break;
case 0x41:TR0=0;select(3);break;
case 0x81:TR0=0;wave(1);  break; //方波
case 0x12:TR0=0;select(4);break;
case 0x22:TR0=0;select(5);break;
case 0x42:TR0=0;select(6);break;
case 0x82:TR0=0;wave(2);  break; //正弦波
case 0x14:TR0=0;select(7);break;
case 0x24:TR0=0;select(8);break;
case 0x44:TR0=0;select(9);break;
case 0x84:TR0=0;wave(3);  break;
case 0x18:TR0=0;enter();  break; //确定
case 0x28:TR0=0;select(0);break;
case 0x48:TR0=0;count=2;  break;
//case 0x88:TR0=0;wave(3); break;
}										
  
    }}

/*///////////////////////////////////////////////////////////////////////
 函数名： 主函数
 功能：    
 返回值： 无
 注意：	  无

//////////////////////////////////////////////////////////////////////*/
 main()
{

 uchar k,out;
 init();
    lcdinit();
    delay(3);
   lcd_dis(table1,0x80);//频率
   lcd_dis(table2,0xc0);//振幅
   lcd_dis(table3,0xc9);  //波形
  
   wave(1); //默认是正弦波
    P2=0X00;
  	TR0=1;
	P1=0XF0;
  while(1)
 {
 
   
    if(state==1)//正弦波
       {for(k=0;k<100;)
         {
		 if(P1!=0xf0)
		 { sweep();}
	      if(FLAG==1)
         {out=sin[k];
             FLAG=0;
			 //P2_4=0;
			 //delay(255);
             P0=out;
              k++; }
                     }      }

 
 
    else if(state==2) //三角波
    {for(k=0;k<100;)
         {
		 if(P1!=0xf0)
		 { sweep();}
	      if(FLAG==1)
         {out=shn[k];
             FLAG=0;
			 //P2_4=0;
			 //delay(255);
             P0=out;
              k++; }
                     }   }  
 	else if(state==3) //方波
    {for(k=0;k<100;)
         {
		 if(P1!=0xf0)
		 { sweep();}
	     
		 if(FLAG==1)
         {out=fan[k];
             FLAG=0;
			 //P2_4=0;
			 //delay(255);
             P0=out;
              k++; }
                     }   }   
					 
					 
					 }	   }
 
 
 
 