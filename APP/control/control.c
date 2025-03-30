#include "control.h"

u16 left[ROW],right[ROW],mid[ROW]; //左右边线中线数组
u16 correct_line=0;                //有效行
u16 lose_left=0;                   //左边丢线行数
u16 lose_right=0;                  //右边丢线行数
u16 shizi_start=0;                 //十字起始行全局变量

//限制行数
int limit_row(int x)
{
	int temp;
	if(x<=1) temp=1;
	else if(x>=ROW-1) temp=ROW-1;	
	return temp;
}
//限制列数
int limit_column(int x)
{
	int temp;
	if(x<=0) temp=0;
	else if(x>=COLUMN-1) temp=COLUMN-1;	
	return temp;
}
//简单的找出中心线
void get_mid(void)
{
	u16 i,j;
	u16 start;
	lose_left=lose_right=0; //左右丢线数清零
	for(i=0;i<ROW;i++)
	{
		left[i]=0;
		right[i]=COLUMN-1;
		mid[i]=COLUMN/2;
	}
	if(Image_Data[ROW-1][COLUMN/2]==0xff) start=COLUMN/2;
	else
	{
		if(Image_Data[ROW-1][limit_column(COLUMN/2+30)]==0xff) start=limit_column(COLUMN/2+30);
		else if(Image_Data[ROW-1][limit_column(COLUMN/2-30)]==0xff) start=limit_column(COLUMN/2-30);
	}
	for(i=ROW-1;i>ROW-3;i--)
	{
		for(j=start;j>0;j--)
		{
			if(Image_Data[i][j]==0) 
			{
				left[i]=j;
				break;
			}
		}
		for(j=start;j<COLUMN;j++)
		{
			if(Image_Data[i][j]==0) 
			{
				right[i]=j;
				break;
			}
		}
		mid[i]=(left[i]+right[i])/2;
		if(left[i]==0)  
		{
			lose_left++;  //丢线计数
		}
		if(right[i]==COLUMN-1) 
		{
			lose_right++;
		}
	} 
	for(i=ROW-3;i>0;i--)//不包括第0行
	{
		for(j=mid[i+1];j>0;j--)
		{
			if(Image_Data[i][j]==0) 
			{
				left[i]=j; 
				break;
			}
		}
		for(j=mid[i+1];j<COLUMN;j++)
		{
			if(Image_Data[i][j]==0) 
			{
				right[i]=j;
				break;
			}
		}
		mid[i]=(left[i]+right[i])/2;
		if(left[i]==0)  lose_left++;  //丢线计数
		if(right[i]==COLUMN-1) lose_right++;
  }	
	for(i=ROW-1;i>0;i--) //搜索有效行
	{
		if(Image_Data[i][mid[i]]==0||i==1||mid[i]<3||mid[i]>=COLUMN-4){correct_line=i;break;}	
	} 
}		
//十字处理
void shizi_handle(void)
{
	u16 i,ii,j;
	u16 left_offset=0,right_offset=0;
	u16 left_start=0,right_start=0;
	u16 max_xia=0,min_shang=0;
  u8 YuanHuan[5]={0,0,0,0,0};
	u8 YuanhHuanFirst=0;
	shizi_start=0; //每次十字起始清零
	for(i=ROW-1;i>0;i--) //正常情况
	{
		if(shizi_start==0&&left[i]==0&&right[i]==COLUMN-1&&left[i-1]==0&&right[i-1]==COLUMN-1&&left[i-2]==0&&right[i-2]==COLUMN-1
			&&left[i-3]==0&&right[i-3]==COLUMN-1&&left[i-4]==0&&right[i-4]==COLUMN-1&&left[i-5]==0&&right[i-5]==COLUMN-1&&i>=correct_line)  //在有效行以下判断左右连续三行丢线
		{
			shizi_start=i; //记录十字起始行
			break;
		}
	}
	if(shizi_start!=0&&shizi_start<ROW-8&&shizi_start>=30) //满足正常十字情况
	{
		for(i=shizi_start;i<ROW;i++)  //找出左下起始行和右下起始行
		{
			if(left_start==0&&left[i]==0&&left[i+1]!=0&&left[i+2]!=0) //找左下起始
			{
				for(ii=i+1;ii<ROW;ii++)
			  {
					if(left[ii]-left[ii+1]>0&&left[ii]-left[ii+2]>0&&left[ii]!=0&&left[ii+1]!=0&&left[ii+2]!=0)
					{
            left_start=ii;
						break;
					}						
				}
			}
			if(right_start==0&&right[i]==COLUMN-1&&right[i+1]!=COLUMN-1&&right[i+2]!=COLUMN-1) //找右下起始
			{
				for(ii=i+1;ii<ROW;ii++)
			  {
					if(right[ii]-right[ii+1]<0&&right[ii]-right[ii+2]<0&&right[ii]!=COLUMN-1&&right[ii+1]!=COLUMN-1&&right[ii+2]!=COLUMN-1)
					{
            right_start=ii;
						break;
					}						
				}
			}
		}
		if(left_start!=0&&right_start!=0)//左右拐点都存在
		{
			for(i=left_start;i>0;i--) //左斜线
			{
				if((i-left_start)%2)
				 left[i]=left[i+1]+1;
				else
					left[i]=left[i+1];
			}
			for(i=right_start;i>0;i--) //右斜线
			{
				if((i-right_start)%2)
				  right[i]=right[i+1]-1;
				else
				right[i]=right[i+1];
			}
			for(i=shizi_start;i>0;i--) //重新搜线
			{
				for(j=mid[i+1];j>0;j--)
				{
					if(Image_Data[i][j]==0) 
					{
						left[i]=j;
						break;
					}
				}
				for(j=mid[i+1];j<COLUMN;j++)
				{
					if(Image_Data[i][j]==0) 
					{
						right[i]=j;
						break;
					}
				}
				if(left[i]>left[left_start]&&right[i]<right[right_start]) mid[i]=(left[i]+right[i])/2;
			}
			for(i=shizi_start;i>5;i--) //上起始行
			{
				if(left[i]!=0&&right[i]!=COLUMN-1&&Image_Data[i][left[i]]==0&&Image_Data[i][right[i]]==0&&left[i]>left[left_start]&&right[i]<right[right_start])
				{
					min_shang=limit_row(i-2);
					break;
				}
			}	
			max_xia=left_start>=right_start?left_start:right_start; //确定下连线行
			for(i=min_shang;i<=max_xia;i++) //确定上连线行
			{
				left[i]=left[min_shang]+(int)((i-min_shang)*(left[max_xia]-left[min_shang])/(max_xia-min_shang));
				right[i]=right[min_shang]+(int)((i-min_shang)*(right[max_xia]-right[min_shang])/(max_xia-min_shang));
				mid[i]=(left[i]+right[i])/2;
			}
			for(i=min_shang;i>0;i--)
		  {
				for(j=mid[i+1];j>0;j--)
				{
					left[i]=j;
					if(Image_Data[i][j]==0) break;
				}
				for(j=mid[i+1];j<COLUMN;j++)
				{ 
					right[i]=j;
					if(Image_Data[i][j]==0) break;
				}
				mid[i]=(left[i]+right[i])/2;
			}
		}
		else if(left_start==0&&right_start!=0) //左拐点不存在
		{
			for(i=ROW-2;i>0;i--) //左斜线
			{
				left[i]=left[i+1];
			}
			for(i=right_start;i>0;i--) //右斜线
			{
				if((i-right_start)%2)
				  right[i]=right[i+1]-1;
				else
				right[i]=right[i+1];
			}
			for(i=shizi_start;i>0;i--) //重新搜线
			{
				for(j=mid[i+1];j>0;j--)
				{
					if(Image_Data[i][j]==0) 
					{
						left[i]=j;
						break;
					}
				}
				for(j=mid[i+1];j<COLUMN;j++)
				{
					if(Image_Data[i][j]==0) 
					{
						right[i]=j;
						break;
					}
				}
				if(right[i]<right[right_start]) mid[i]=(left[i]+right[i])/2;
			}
			for(i=shizi_start;i>5;i--) //确定上连线行
			{
				if(right[i]!=COLUMN-1&&Image_Data[i][right[i]]==0&&right[i]<right[right_start])
				{
					min_shang=limit_row(i-2);;
					break;
				}
			}	
			max_xia=right_start; //确定下连线行
			for(i=min_shang;i<ROW;i++) //重新计算左边线
			{
				left[i]=left[min_shang]+(int)((i-min_shang)*(0-left[min_shang])/(ROW-1-min_shang));
			}
			for(i=min_shang;i<=max_xia;i++) //重新计算右边线
			{
				right[i]=right[min_shang]+(int)((i-min_shang)*(right[max_xia]-right[min_shang])/(max_xia-min_shang));
			}
			for(i=max_xia;i>min_shang;i--) mid[i]=(left[i]+right[i])/2;
		}
		else if(left_start!=0&&right_start==0) //右拐点不存在
		{
			for(i=left_start;i>0;i--) //左斜线
			{
				if((i-left_start)%2)
				 left[i]=left[i+1]+1;
				else
					left[i]=left[i+1];
			}
			for(i=ROW-2;i>0;i--) //右斜线
			{
				right[i]=right[i+1];
			}
			for(i=shizi_start;i>0;i--) //重新搜线
			{
				for(j=mid[i+1];j>0;j--)
				{
					if(Image_Data[i][j]==0) 
					{
						left[i]=j;
						break;
					}
				}
				for(j=mid[i+1];j<COLUMN;j++)
				{
					if(Image_Data[i][j]==0) 
					{
						right[i]=j;
						break;
					}
				}
				if(left[i]>left[left_start]) mid[i]=(left[i]+right[i])/2;
			}
			for(i=shizi_start;i>0;i--)  //确定上连线行
			{
				if(left[i]!=0&&Image_Data[i][left[i]]==0&&left[i]>left[left_start])
				{
					min_shang=limit_row(i-2);
					break;
				}
			}	
			max_xia=left_start; //确定下连线行
			for(i=min_shang;i<=max_xia;i++) //重新计算左边线
			{
				left[i]=left[min_shang]+(int)((i-min_shang)*(left[max_xia]-left[min_shang])/(max_xia-min_shang));
			}
			for(i=min_shang;i<ROW;i++) //重新计算右边线
			{
				right[i]=right[min_shang]+(int)((i-min_shang)*((COLUMN-1)-right[min_shang])/(ROW-1-min_shang));
			}
			for(i=max_xia;i>min_shang;i--) mid[i]=(left[i]+right[i])/2;
	  }
	}
	else if(shizi_start!=0&&shizi_start>=ROW-8) //正入十字,已进入十字
	{
		for(i=ROW-1;i>correct_line+6;i--) //在有效行以下找左右跳变
		{
			if(left_start==0&&left[i]==0&&left[i-1]==0&&left[i-2]==0&&left[i-4]!=0&&left[i-5]!=0&&left[i-6]!=0) // 找左上跳变
			{
				left_start=limit_column(i-5); //左跳变行
				left_offset=left[i-6]-left[i-2];
			}
			if(right_start==0&&right[i]==COLUMN-1&&right[i-1]==COLUMN-1&&right[i-2]==COLUMN-1&&right[i-4]!=COLUMN-1&&right[i-5]!=COLUMN-1&&right[i-6]!=COLUMN-1) // 找右上跳变
			{
				right_start=limit_column(i-5); //右跳变行
				right_offset=right[i-2]-right[i-6];
			}
			if(left_start!=0&&right_start!=0&&(left_offset+right_offset>25)) break;
		}
		if(left_start!=0&&right_start!=0&&(left_offset+right_offset>25))//两边都存在跳变量则开始连线
		{
			min_shang=left_start<=right_start?left_start:right_start; //确定上起始行
			for(i=min_shang;i<ROW;i++) //连线
			{
				left[i]=left[min_shang]+(int)((i-min_shang)*(0-left[min_shang])/(ROW-1-min_shang));
				right[i]=right[min_shang]+(int)((i-min_shang)*(COLUMN-1-right[min_shang])/(ROW-1-min_shang));
				mid[i]=(left[i]+right[i])/2;
			}
		}
	}
	for(i=ROW-1;i>0;i--) //重新搜索有效行
	{
		if(Image_Data[i][mid[i]]==0||i==1||mid[i]<3||mid[i]>=COLUMN-4){correct_line=i;break;}	
	}
	if(correct_line==1) return; //十字补好线
	//圆环处理
	if(shizi_start>=10&&correct_line>5)
	{
		for(i=shizi_start-1;i>0;i--) 
		{
			for(j=0;j<COLUMN;j++)
		  {
				if(Image_Data[i][j]==0) 
				{
					if(YuanhHuanFirst==0) YuanhHuanFirst=i;
					if(YuanhHuanFirst-i<=4)YuanHuan[YuanhHuanFirst-i]++;
				}
			}
		}
		if(YuanhHuanFirst>=10&&YuanHuan[0]>=10)
		{
			if(YuanHuan[4]>YuanHuan[3])
				if(YuanHuan[3]>YuanHuan[2])
			    if(YuanHuan[2]>YuanHuan[1])
				    if(YuanHuan[1]>YuanHuan[0])
				      for(i=0;i<ROW;i++) mid[i]=0;
		}
	}
	
//	OLED_ShowNum(0,0,YuanHuan[4],2,12);
//	OLED_ShowNum(20,0,YuanHuan[3],2,12);
//	OLED_ShowNum(40,0,YuanHuan[2],2,12);
//	OLED_ShowNum(60,0,YuanHuan[1],2,12);
//	OLED_ShowNum(80,0,YuanHuan[0],2,12);
//	
//	OLED_ShowNum(0,30,YuanhHuanFirst,2,12);
}	


/************************另一种方式，因没有赛道在手，后续交由读者自行抉择********************************/
#ifdef inage_deal

#define POINT_COUNT 10

 u8 validline;    //最大有效行
 double slope;    //中线斜率
 int everage;     //中线平均偏差
 
 
int Round_flag=0;
int leftFindFlag;  
int rightFindFlag; 
  
u8 centerLine[ROW+1] = {0};          // 
u8 leftLine[ROW] ;  
u8 rightLine[ROW] ; 

void find_all_distence()
{
	

	
}
/******************************************
 ********最小二乘法生成有效点的斜率********
************不包括line这一点***************
 *******************************************/
double createSlope(int line)  
{  
    u8 *linePointer;  
    signed char tmp = 0;  
    double sumUp = 0;  
    double sumX = 0;  
    double sumY = 0;  
    double averageX = 0;  
    double averageY = 0;  
    double sumDown = 0;  
    double parameterA;  
    double parameterB;  
       
    linePointer = &centerLine[line];  
      
    // 对line一下的所有点进行拟合  
    while(++tmp <= (ROW-line-1)) 
    {  
        sumX += (line+tmp);  
        sumY += linePointer[tmp];  
    }  
    --tmp;  
    averageX = sumX/tmp;  
    averageY = sumY/tmp;  
    do  
    {  
        sumUp += (linePointer[tmp]-averageY) * (line+tmp-averageX);  
        sumDown += (line+tmp-averageX) * (line+tmp-averageX);  
    } while(--tmp > 0);  
      
    if(sumDown == 0)  
        parameterB = 0;  
    else  
        parameterB = sumUp/sumDown;  
    return (double)(averageY-parameterB*averageX);  
}  


/**********************************
 ********获取中线平均偏差**********
 ***********去除最大行*************/
int find_everage(int topline,int bottomline)
{
	int i;
	int sum_line=0;
	for(i=bottomline;i>topline;i--)
	sum_line=sum_line+(COLUMN/2-centerLine[i]);
	return (sum_line/(bottomline-topline));
}



void get_centerline_new () 
{
//	
//    int i,j;   
//    for(i=ROW-1;i> ROW-6;i--)  
//    {  
//        leftFindFlag = 0;  
//        rightFindFlag = 0;  
//        for(j = COLUMN/2;j > 0;j--)  
//        {  
//            if(leftFindFlag == 0 && Image_Data[i][j] == 0 && Image_Data[i][j+1] == 0xff) 
//            {  
//                leftLine[i] = j;  
//                leftFindFlag = 1;  
//            }   
//            if(rightFindFlag == 0 && Image_Data[i][COLUMN-1-j] == 0 && Image_Data[i][COLUMN-j] == 0xff)   
//            {  
//                rightLine[i] = j;  
//                rightFindFlag = 1;  
//            }  
//            if(leftFindFlag == 1 && rightFindFlag == 1)  
//                break;  
//        }   
//        if(leftFindFlag == 0)  
//            leftLine[i] = 0;  
//        if(rightFindFlag == 0)  
//            rightLine[i] = COLUMN-1;   
//        centerLine[i] = (leftLine[i]+rightLine[i])/2;
//    }  
//       
//    for(i = ROW-6; ROW >= 0; i--)  
//    {  
//        leftFindFlag = 0;  
//        rightFindFlag = 0;       
//        for(j = 0; j < 5*2+1; j++)  
//        {  
//            if(leftFindFlag != 0)  
//                 break;  
//            else if((leftLine[i+1]-j+8) > COLUMN-1)  
//                 continue;  
//            else if((leftLine[i+1]-j+5) < 0)  
//                 break;  
//            else if(Image_Data[i][leftLine[i+1]-j+5] == 0 && Image_Data[i][leftLine[i+1]-j+6] == 0xff)  
//            {  
//               leftLine[i] = leftLine[i+1]-j+5;  
//               leftFindFlag = 1;  
//            }  
//        }  
//       for(j = 0; j < 5*2+1; j++)  
//        {  
//            if(rightFindFlag != 0)  
//                break;  
//            else if((rightLine[i+1]+j-5) < 0)  
//                continue;  
//            else if(rightLine[i+1]+j-5 > COLUMN-1)  
//                break;  
//            else if(Image_Data[i][rightLine[i+1]+j-5] == 0xff && Image_Data[i][rightLine[i+1]+j-4] == 0 )  
//           {  
//                rightLine[i] = rightLine[i+1]+j-5;  
//                rightFindFlag = 1;  
//           }  
//        }  
//          
//        if(leftFindFlag == 0)  
//            leftLine[i] =  leftLine[i+1];  
//        if(rightFindFlag == 0)  
//            rightLine[i] = rightLine[i+1];  
//				centerLine[i] = (leftLine[i]+rightLine[i])/2;
//			}
//		
//	
}

/**********************************
 ************获取中线**************
 **********************************/
void get_centerline()    
{
	u16 i,j;
  for(i=ROW-1;i>ROW-3;i--)
  {
     for(j=COLUMN/2;j>0;j--)  
     {
      if(Image_Data[i][j]==0xff)
      {
        leftLine[i]=j; 
      }
			else break;
     }
     for(j=COLUMN/2;j<COLUMN-1;j++)  
     {
      if(Image_Data[i][j]==0xff)
      {
				
        rightLine[i]=j; 
      }
			else break;
     }
		 centerLine[i]=(leftLine[i]+rightLine[i])/2;
	}	
  for(i=ROW-3;i>0;i--)
  {
     for(j=centerLine[i+1];j>2;j--)  
     {
      if(Image_Data[i][j]==0xff)
      {
        leftLine[i]=j; 
				leftFindFlag=1;
      }
			else 
			{
				leftFindFlag=0;
				break;
			}
				
     }
     for(j=centerLine[i+1];j<COLUMN-1;j++)  
     {
      if(Image_Data[i][j]==0xff)
      {
        rightLine[i]=j;   
				rightFindFlag=1;				
      }
			else 
			{
				rightFindFlag=0;
				break;
			}
     }
		 //环形赛道处理
		 if(leftFindFlag==0 && rightFindFlag==0)
		 {}
		 	if(i>=25 && Round_flag==1 && leftFindFlag==0)
	   {
			 if(Round_flag==1)
			 {
				 ftm_duty_change(FTM2,ftm_ch1,750);
			   delay_ms(3);
			 }
	   }			
     centerLine[i]=(leftLine[i]+rightLine[i])/2;		 
	}		
	
} 

/**********************************
 ***找到视野最远点用于路况分析*****
 **********************************/

u8 find_Valid_Line()
{
	u8 useline;
	int i,j;
	for(i=ROW-1;i>=1;i--)
	{
		if( (Image_Data[i-1][COLUMN/2]==0xff) 
			   &&(Image_Data[i][COLUMN/2]==0) 
		     &&(Image_Data[i+1][COLUMN/2]==0) )
			return i;		
	}
	return 0;
}



double createSlope1(int line)  
{  
    u8 *linePointer;  
    signed char tmp = 0;  
    double sumUp = 0;  
    double sumX = 0;  
    double sumY = 0;  
    double sumXY = 0;  
    double sumX2 = 0;  
    double sumDown = 0;  
    double k;   
       
    linePointer = &centerLine[line];  
      
    // 对line一下的所有点进行拟合  
    while(++tmp <= (ROW-1-line)) 
    {  
        sumX += (line+tmp);  
        sumY += linePointer[tmp];
        sumXY += ((line+tmp) * linePointer[tmp]);
        sumX2 += 	((line+tmp)*(line+tmp));		
    }  
    --tmp;  
 
        sumUp = (tmp*sumXY - sumX*sumY);  
        sumDown = tmp*sumX2 - sumX * sumX;  
  
    if(sumDown == 0)  
        k		= 0;  
    else  
        k = sumUp/sumDown;  
    return (double)k;  
} 


/**********************************
 *************停车检测*************
 **********************************/
void park_car()
{
	int i,j,left_flag,right_flag,stop_flag=0;
	if(Image_Data[ROW-1][COLUMN/2]==0xff)
	{
		for(i=COLUMN/2;i<COLUMN;i++)
		{
			if(Image_Data[ROW-1][i]==0xff)
				right_flag=i;
			else
				break;		
		}
	  for(i=COLUMN/2;i>0;i--)
		{
			if(Image_Data[ROW-1][i]==0xff)
				left_flag=i;
			else
				break;		
		}
		
		if((right_flag-left_flag)<=5) stop_flag=1;
  }
	else 
		if(Image_Data[ROW-1][COLUMN/2]==0)
	{
		for(i=COLUMN/2;i<COLUMN;i++)
		{
			if(Image_Data[ROW-1][i]==0)
				right_flag=i;
			else
				break;		
		}
	  for(i=COLUMN/2;i>0;i--)
		{
			if(Image_Data[ROW-1][i]==0)
				left_flag=i;
			else
				break;		
		}
		
		if((right_flag-left_flag)<=5) stop_flag=1;
  }
	if(stop_flag==1) 
	{
		while(1)
		{
			ftm_duty_change(FTM0,ftm_ch1,0);//电机接口2	
	    ftm_duty_change(FTM0,ftm_ch0,0);//电机接口1 
	    ftm_duty_change(FTM0,ftm_ch2,0);//电机接口3
	    ftm_duty_change(FTM0,ftm_ch3,0);//电机接口4 
		}
 }
}
	
/**********************************
 *************环形处理*************
 **********************************/
void Round_handle()
{
	int maxline,bottomline,top_line;
	int i,flag=0;
	maxline=find_Valid_Line();
	if((Round_flag==0)&&(maxline>=10))
	{
//			for(i=ROW-1;i>0;i--)
//		{
//			if((leftLine[i]<1) && (rightLine[i]>COLUMN-2) && (leftLine[i+3]>2) && (rightLine[i+3]<COLUMN-3))
//				bottomline=i+1;
//			else
//				bottomline=ROW-1;
//		}
//		for(i=bottomline+1;i>maxline;i--)
//		{
//			leftLine[i]=(COLUMN/2-leftLine[bottomline])/(maxline-bottomline)*(i-bottomline+leftLine[bottomline]);
//		}	
		while(1)
		ftm_duty_change(FTM2,ftm_ch1,750);
		delay_ms(3);
		flag++;
    if(flag==6) Round_flag = 1;  
	}

}

#endif 
