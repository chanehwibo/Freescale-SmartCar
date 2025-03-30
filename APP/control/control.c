#include "control.h"

u16 left[ROW],right[ROW],mid[ROW]; //���ұ�����������
u16 correct_line=0;                //��Ч��
u16 lose_left=0;                   //��߶�������
u16 lose_right=0;                  //�ұ߶�������
u16 shizi_start=0;                 //ʮ����ʼ��ȫ�ֱ���

//��������
int limit_row(int x)
{
	int temp;
	if(x<=1) temp=1;
	else if(x>=ROW-1) temp=ROW-1;	
	return temp;
}
//��������
int limit_column(int x)
{
	int temp;
	if(x<=0) temp=0;
	else if(x>=COLUMN-1) temp=COLUMN-1;	
	return temp;
}
//�򵥵��ҳ�������
void get_mid(void)
{
	u16 i,j;
	u16 start;
	lose_left=lose_right=0; //���Ҷ���������
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
			lose_left++;  //���߼���
		}
		if(right[i]==COLUMN-1) 
		{
			lose_right++;
		}
	} 
	for(i=ROW-3;i>0;i--)//��������0��
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
		if(left[i]==0)  lose_left++;  //���߼���
		if(right[i]==COLUMN-1) lose_right++;
  }	
	for(i=ROW-1;i>0;i--) //������Ч��
	{
		if(Image_Data[i][mid[i]]==0||i==1||mid[i]<3||mid[i]>=COLUMN-4){correct_line=i;break;}	
	} 
}		
//ʮ�ִ���
void shizi_handle(void)
{
	u16 i,ii,j;
	u16 left_offset=0,right_offset=0;
	u16 left_start=0,right_start=0;
	u16 max_xia=0,min_shang=0;
  u8 YuanHuan[5]={0,0,0,0,0};
	u8 YuanhHuanFirst=0;
	shizi_start=0; //ÿ��ʮ����ʼ����
	for(i=ROW-1;i>0;i--) //�������
	{
		if(shizi_start==0&&left[i]==0&&right[i]==COLUMN-1&&left[i-1]==0&&right[i-1]==COLUMN-1&&left[i-2]==0&&right[i-2]==COLUMN-1
			&&left[i-3]==0&&right[i-3]==COLUMN-1&&left[i-4]==0&&right[i-4]==COLUMN-1&&left[i-5]==0&&right[i-5]==COLUMN-1&&i>=correct_line)  //����Ч�������ж������������ж���
		{
			shizi_start=i; //��¼ʮ����ʼ��
			break;
		}
	}
	if(shizi_start!=0&&shizi_start<ROW-8&&shizi_start>=30) //��������ʮ�����
	{
		for(i=shizi_start;i<ROW;i++)  //�ҳ�������ʼ�к�������ʼ��
		{
			if(left_start==0&&left[i]==0&&left[i+1]!=0&&left[i+2]!=0) //��������ʼ
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
			if(right_start==0&&right[i]==COLUMN-1&&right[i+1]!=COLUMN-1&&right[i+2]!=COLUMN-1) //��������ʼ
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
		if(left_start!=0&&right_start!=0)//���ҹյ㶼����
		{
			for(i=left_start;i>0;i--) //��б��
			{
				if((i-left_start)%2)
				 left[i]=left[i+1]+1;
				else
					left[i]=left[i+1];
			}
			for(i=right_start;i>0;i--) //��б��
			{
				if((i-right_start)%2)
				  right[i]=right[i+1]-1;
				else
				right[i]=right[i+1];
			}
			for(i=shizi_start;i>0;i--) //��������
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
			for(i=shizi_start;i>5;i--) //����ʼ��
			{
				if(left[i]!=0&&right[i]!=COLUMN-1&&Image_Data[i][left[i]]==0&&Image_Data[i][right[i]]==0&&left[i]>left[left_start]&&right[i]<right[right_start])
				{
					min_shang=limit_row(i-2);
					break;
				}
			}	
			max_xia=left_start>=right_start?left_start:right_start; //ȷ����������
			for(i=min_shang;i<=max_xia;i++) //ȷ����������
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
		else if(left_start==0&&right_start!=0) //��յ㲻����
		{
			for(i=ROW-2;i>0;i--) //��б��
			{
				left[i]=left[i+1];
			}
			for(i=right_start;i>0;i--) //��б��
			{
				if((i-right_start)%2)
				  right[i]=right[i+1]-1;
				else
				right[i]=right[i+1];
			}
			for(i=shizi_start;i>0;i--) //��������
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
			for(i=shizi_start;i>5;i--) //ȷ����������
			{
				if(right[i]!=COLUMN-1&&Image_Data[i][right[i]]==0&&right[i]<right[right_start])
				{
					min_shang=limit_row(i-2);;
					break;
				}
			}	
			max_xia=right_start; //ȷ����������
			for(i=min_shang;i<ROW;i++) //���¼��������
			{
				left[i]=left[min_shang]+(int)((i-min_shang)*(0-left[min_shang])/(ROW-1-min_shang));
			}
			for(i=min_shang;i<=max_xia;i++) //���¼����ұ���
			{
				right[i]=right[min_shang]+(int)((i-min_shang)*(right[max_xia]-right[min_shang])/(max_xia-min_shang));
			}
			for(i=max_xia;i>min_shang;i--) mid[i]=(left[i]+right[i])/2;
		}
		else if(left_start!=0&&right_start==0) //�ҹյ㲻����
		{
			for(i=left_start;i>0;i--) //��б��
			{
				if((i-left_start)%2)
				 left[i]=left[i+1]+1;
				else
					left[i]=left[i+1];
			}
			for(i=ROW-2;i>0;i--) //��б��
			{
				right[i]=right[i+1];
			}
			for(i=shizi_start;i>0;i--) //��������
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
			for(i=shizi_start;i>0;i--)  //ȷ����������
			{
				if(left[i]!=0&&Image_Data[i][left[i]]==0&&left[i]>left[left_start])
				{
					min_shang=limit_row(i-2);
					break;
				}
			}	
			max_xia=left_start; //ȷ����������
			for(i=min_shang;i<=max_xia;i++) //���¼��������
			{
				left[i]=left[min_shang]+(int)((i-min_shang)*(left[max_xia]-left[min_shang])/(max_xia-min_shang));
			}
			for(i=min_shang;i<ROW;i++) //���¼����ұ���
			{
				right[i]=right[min_shang]+(int)((i-min_shang)*((COLUMN-1)-right[min_shang])/(ROW-1-min_shang));
			}
			for(i=max_xia;i>min_shang;i--) mid[i]=(left[i]+right[i])/2;
	  }
	}
	else if(shizi_start!=0&&shizi_start>=ROW-8) //����ʮ��,�ѽ���ʮ��
	{
		for(i=ROW-1;i>correct_line+6;i--) //����Ч����������������
		{
			if(left_start==0&&left[i]==0&&left[i-1]==0&&left[i-2]==0&&left[i-4]!=0&&left[i-5]!=0&&left[i-6]!=0) // ����������
			{
				left_start=limit_column(i-5); //��������
				left_offset=left[i-6]-left[i-2];
			}
			if(right_start==0&&right[i]==COLUMN-1&&right[i-1]==COLUMN-1&&right[i-2]==COLUMN-1&&right[i-4]!=COLUMN-1&&right[i-5]!=COLUMN-1&&right[i-6]!=COLUMN-1) // ����������
			{
				right_start=limit_column(i-5); //��������
				right_offset=right[i-2]-right[i-6];
			}
			if(left_start!=0&&right_start!=0&&(left_offset+right_offset>25)) break;
		}
		if(left_start!=0&&right_start!=0&&(left_offset+right_offset>25))//���߶�������������ʼ����
		{
			min_shang=left_start<=right_start?left_start:right_start; //ȷ������ʼ��
			for(i=min_shang;i<ROW;i++) //����
			{
				left[i]=left[min_shang]+(int)((i-min_shang)*(0-left[min_shang])/(ROW-1-min_shang));
				right[i]=right[min_shang]+(int)((i-min_shang)*(COLUMN-1-right[min_shang])/(ROW-1-min_shang));
				mid[i]=(left[i]+right[i])/2;
			}
		}
	}
	for(i=ROW-1;i>0;i--) //����������Ч��
	{
		if(Image_Data[i][mid[i]]==0||i==1||mid[i]<3||mid[i]>=COLUMN-4){correct_line=i;break;}	
	}
	if(correct_line==1) return; //ʮ�ֲ�����
	//Բ������
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


/************************��һ�ַ�ʽ����û���������֣��������ɶ������о���********************************/
#ifdef inage_deal

#define POINT_COUNT 10

 u8 validline;    //�����Ч��
 double slope;    //����б��
 int everage;     //����ƽ��ƫ��
 
 
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
 ********��С���˷�������Ч���б��********
************������line��һ��***************
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
      
    // ��lineһ�µ����е�������  
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
 ********��ȡ����ƽ��ƫ��**********
 ***********ȥ�������*************/
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
 ************��ȡ����**************
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
		 //������������
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
 ***�ҵ���Ұ��Զ������·������*****
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
      
    // ��lineһ�µ����е�������  
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
 *************ͣ�����*************
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
			ftm_duty_change(FTM0,ftm_ch1,0);//����ӿ�2	
	    ftm_duty_change(FTM0,ftm_ch0,0);//����ӿ�1 
	    ftm_duty_change(FTM0,ftm_ch2,0);//����ӿ�3
	    ftm_duty_change(FTM0,ftm_ch3,0);//����ӿ�4 
		}
 }
}
	
/**********************************
 *************���δ���*************
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
