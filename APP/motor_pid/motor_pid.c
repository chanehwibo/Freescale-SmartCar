#include "motor_pid.h"

//初始化左电机Pid参数
struct MotorPid Left=
{
	42, //Kp
	26, //Ki
	10, //Kd
	0,
	0,
	0,
	0,
	0,
	0,0,0,
	0,
	0,
};

//初始化右电机Pid参数
struct MotorPid Right=
{
	42, //Kp
	26, //Ki
	10, //Kd
	0,
	0,
	0,
	0,
	0,
	0,0,0,
	0,
	0,
};

void SendWave(u16 Pluse)
{
	uart_sendbyte(UART_Printf,0X03);
	uart_sendbyte(UART_Printf,0XFC);

	uart_sendbyte(UART_Printf,Pluse);
	uart_sendbyte(UART_Printf,Pluse>>8);
	
	uart_sendbyte(UART_Printf,0XFC);
	uart_sendbyte(UART_Printf,0X03);
}

//左电机增量式PID算法
void LeftMotorPID(void)
{
	Left.Error[2]=Left.Error[1]; //误差更新
	Left.Error[1]=Left.Error[0];
	Left.Pluse = dma_get_counter(DMA_Channel1); //获取脉冲值
  Left.Error[0] = Left.Speed - Left.Pluse; //算误差
	if(Left.Error[0]>30) ftm_duty_change(FTM0,ftm_ch0,1700);
	Left.Pout = (float)Left.Kp * (Left.Error[0] - Left.Error[1]); 
	Left.Iout = (float)Left.Ki * Left.Error[0]; 
	Left.Dout = (float)Left.Kd * (Left.Error[0] - 2*Left.Error[1] + Left.Error[2]);
	Left.Out = Left.LastOut + (Left.Pout + Left.Iout + Left.Dout);
	if(Left.Out>=1874) Left.Out=1874; 
	if(Left.Out<10) Left.Out=10;
	Left.LastOut=Left.Out; //迭代
	ftm_duty_change(FTM0,ftm_ch0,Left.Out);	
}
//右电机增量式PID算法
void RightMotorPID(void)
{
	Right.Error[2]=Right.Error[1]; //误差更新
	Right.Error[1]=Right.Error[0];
	Right.Pluse = dma_get_counter(DMA_Channel2); //获取脉冲值
	Right.Error[0] = Right.Speed - Right.Pluse; //算误差
	if(Right.Error[0]>30) ftm_duty_change(FTM0,ftm_ch2,1700);
	Right.Pout = (float)Right.Kp * (Right.Error[0] - Right.Error[1]); 
	Right.Iout = (float)Right.Ki * Right.Error[0]; 
	Right.Dout = (float)Right.Kd * (Right.Error[0] - 2*Right.Error[1] + Right.Error[2]);
	Right.Out = Right.LastOut + (Right.Pout + Right.Iout + Right.Dout);	
	if(Right.Out>=1874) Right.Out=1874; 
	if(Right.Out<10) Right.Out=10;
	Right.LastOut=Right.Out; //迭代
	ftm_duty_change(FTM0,ftm_ch2,Right.Out);	
}


/**********************笔者将两版本均提供*******************************/

#ifdef motor_control_way2

#include "control.h"
#include "imagedel.h"
#include "oled.h"

 u16 aim_speed;
int i;
int SteerSum=0; 
int i;

////float Error;
//float Ps=100,Ds=100;
//float Pe=4 ,Ie=0,De=10;
//float s_fDirectionControlOut1,s_fDirectionControlOutNew,s_fDirectionControlOut2,s_fDirectionControlOutOld;
//float e_fDirectionControlOut1,e_fDirectionControlOutNew,e_fDirectionControlOut2,e_fDirectionControlOutOld;
//u16 aim_speed=90;

//typedef struct PID
//{
//	float thiserror;
//	float lasterror;
//	float preserror;
//}PID;

//static PID sPID;
//static PID *Sptr=&sPID;
//static PID ePID;
//static PID *Eptr=&ePID;

//void PID_Init(void)
//{
//	Sptr->lasterror=0;
//	Sptr->preserror=0;
//  Eptr->lasterror=0;
//	Eptr->preserror=0;
//}
//float SPID_caculate(u16 Set_Value,float Get_Value)     
//{     
//        float s_fDirectionControlOut1=0; 
//        Sptr->thiserror=Get_Value-Set_Value;
//        //????μ±?°ê?3???á?
//        s_fDirectionControlOut1= Ps * (Sptr->thiserror-Sptr->lasterror) + Ds*(Sptr->thiserror-2*Sptr->lasterror+Sptr->preserror); 
//       
//	      Sptr->preserror = Sptr->lasterror;              
//        Sptr->lasterror = Sptr->thiserror;       
//        s_fDirectionControlOut2   += s_fDirectionControlOut1; //é?ò?′?ê?3?á??óé??a′?μ?ê?3???á?
//        s_fDirectionControlOutOld = s_fDirectionControlOutNew;   
//        s_fDirectionControlOutNew = s_fDirectionControlOut2; 
//	      return s_fDirectionControlOutNew;
//} 


float KPe=3,KDe=6;     //???ù?μμ?PD
float KPs=10,KDs=5;    //D±?êμ?PD 6   14
float PWM_e,PWM_s;
int Servo_PWM,Error1,Error2,Error,LastError,LastSlope;
int servo_control(void)
{
	int i,sum;
	validline = find_Valid_Line();
	for(i=20;i<=25;i++)      //25   30
	sum+=centerLine[i];
	sum+=(centerLine[22]+centerLine[22]+centerLine[24]);
	Error=(COLUMN/2-sum/9);

	//Error=find_everage(validline);
	slope =(50*createSlope1(validline));
	
  //Error=COLUMN/2-centerLine[ROW/2-4];
	//printf("\n%d    %f",Error,slope);
	aim_speed=(170-Error*Error/3.2)<130?130:(170-Error*Error/3.2);    //170  110  180  120
	if(Error>=0)          //×ó×a
	{
	   R_aim_speed=aim_speed+Error*Error/600;
	   L_aim_speed=aim_speed-Error*Error/600;
     PWM_e=servo_pwm_middle+(Error+3)*(Error+2)/KPe+KDe*(Error-LastError);
		 PWM_s=slope*slope/KPs+KDs*(slope-LastSlope);
		 Servo_PWM=(int)(PWM_e+PWM_s);
	}
	else                 //óò×a
	{
		 R_aim_speed=aim_speed-Error*Error/600;
	   L_aim_speed=aim_speed+Error*Error/600;
	  PWM_e=servo_pwm_middle-(Error+2)*(Error+3)/KPe-KDe*(LastError-Error);
		PWM_s=(-slope*slope/KPs-KDs*(slope-LastSlope));
		Servo_PWM=(int)(PWM_e+PWM_s);
	}
  LastError=Error;
	LastSlope=slope;
	if(Servo_PWM > servo_pwm_max) 
    Servo_PWM = servo_pwm_max;
  
  if(Servo_PWM < servo_pwm_min)
    Servo_PWM = servo_pwm_min; 
	//printf("\n%d",Servo_PWM);
  return Servo_PWM;
}

//int servo_control(void)
//{
//  Error=find_everage(validline);
//	//Error1=COLUMN/2-centerLine[ROW/2-4]; 
//	//printf("\n%d      %d",Error,Error1);
//	
//	aim_speed=(130-Error*Error/3)<100?100:(130-Error*Error/3);
//	if(Error<0)
//	{
//	   R_aim_speed=aim_speed+Error*Error/1000;
//	   L_aim_speed=aim_speed-Error*Error/1000;
//		 Sptr->thiserror=(Error-COLUMN/2);//????μ±?°ê?3???á?
//     //s_fDirectionControlOut2   +=Ps * (Sptr->thiserror-Sptr->lasterror) + Ds*(Sptr->thiserror-2*Sptr->lasterror+Sptr->preserror); 
//     PWM_e=servo_pwm_middle+(4*Error*Error)/Pe+De*(Error-LastError);
//		 //PWM_s=servo_pwm_middle+(4*Error*Error)/KPs+KDs*(Error-LastError);
//		 //Error_e=servo_pwm_middle+Error*Error/KP+KD*(Error-LastError);
//		 Servo_PWM=PWM_e;
//		printf("\n%d",Servo_PWM);
//	}
//	else
//	{
//		 R_aim_speed=aim_speed-Error*Error/1000;
//	   L_aim_speed=aim_speed+Error*Error/1000;
//		 PWM_e =servo_pwm_middle + Ps * (Sptr->thiserror-Sptr->lasterror) + Ds*(Sptr->thiserror-2*Sptr->lasterror+Sptr->preserror); 
//	   //PWM_e=servo_pwm_middle-(4*Error*Error)/KPe-KDe*(Error-LastError);
//		Servo_PWM=PWM_e;
//	}
//   Sptr->preserror = Sptr->lasterror;              
//   Sptr->lasterror = Sptr->thiserror;       
//  //s_fDirectionControlOut2   += s_fDirectionControlOut1; //é?ò?′?ê?3?á??óé??a′?μ?ê?3???á?
//   s_fDirectionControlOutOld = s_fDirectionControlOutNew;   
//   s_fDirectionControlOutNew = s_fDirectionControlOut2; 
//	if(Servo_PWM > servo_pwm_max) 
//    Servo_PWM = servo_pwm_max;  
//  if(Servo_PWM < servo_pwm_min)
//    Servo_PWM = servo_pwm_min; 
//  return Servo_PWM;
// 
//}


//μ??úPID
u16  L_aim_speed=90;
u16  L_current_count=0, L_MotorPIDOut;
int  L_this_error=0, L_last_error=0, L_prethis_error=0, L_prelast_error=0;
float L_motor_Kp=40,L_motor_Ki=10,L_motor_Kd=20;   //2.5   1.3   14
void L_MotorPIDControl(void)
{
	L_this_error=L_aim_speed-L_current_count;
	L_current_count=0;
	L_prethis_error=L_this_error-L_last_error;
	L_MotorPIDOut+=L_motor_Kp*(L_this_error-L_last_error)+L_motor_Ki*L_this_error+L_motor_Kd*(L_prethis_error-L_prelast_error);//μ??úpid1?ê?
	if(L_MotorPIDOut>1800) L_MotorPIDOut=1800;
	else if(L_MotorPIDOut<50) L_MotorPIDOut=50;	
	ftm_duty_change(FTM0,ftm_ch2,L_MotorPIDOut);
  L_last_error=L_this_error;
	L_prelast_error=L_prethis_error;
}

//μ??úPID
u16  R_aim_speed=90;
u16  R_current_count=0, R_MotorPIDOut;
int  R_this_error=0, R_last_error=0, R_prethis_error=0, R_prelast_error=0;
float R_motor_Kp=40,R_motor_Ki=10,R_motor_Kd=20;
void R_MotorPIDControl(void)
{
	R_this_error=R_aim_speed-R_current_count;
	R_current_count=0;
	R_prethis_error=R_this_error-R_last_error;
	R_MotorPIDOut+=R_motor_Kp*(R_this_error-R_last_error)+R_motor_Ki*R_this_error+R_motor_Kd*(R_prethis_error-R_prelast_error);//μ??úpid1?ê?
	if(R_MotorPIDOut>1800) R_MotorPIDOut=1800;
	else if(R_MotorPIDOut<50) R_MotorPIDOut=50;	
    ftm_duty_change(FTM0,ftm_ch0,R_MotorPIDOut);	
	R_last_error=R_this_error;
	R_prelast_error=R_prethis_error;
}


#endif

