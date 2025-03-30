#include "servo_pd.h"
#include "motor_pid.h"

int ServoThisError = 0,ServoLastError = 0;
float ServoKp = 3.8,ServoKd = 10;		
float ServoOut;

u8 speed=150;

//¶æ»úPD¿ØÖÆ
void ServoPD(void)
{
	if(correct_line<20)
	  ServoThisError=COLUMN/2-(	mid[20]*0.2	+
															mid[25]*0.2	+
															mid[30]*0.2	+
															mid[35]*0.2	+
															mid[40]*0.2	);
	else 
	  ServoThisError=COLUMN/2-(	mid[limit_row(correct_line+1)]*0.2 + 
															mid[limit_row(correct_line+6)]*0.2 + 
															mid[limit_row(correct_line+11)]*0.2 + 
															mid[limit_row(correct_line+16)]*0.2 + 
															mid[limit_row(correct_line+21)]*0.2  );
	//speed=(150-ServoThisError*ServoThisError/20)<120?120:(150-ServoThisError*ServoThisError/20);
	if(ServoThisError>=0)
	{
		ServoOut = SERVO_MID + ServoThisError * ServoThisError / ServoKp+ServoKd*(ServoThisError-ServoLastError); 
	  Left.Speed = (u8)(speed*( 1-( ServoOut-SERVO_MID) / 800 ));
		Right.Speed = (u8)(speed*( 1+(ServoOut-SERVO_MID)/800 ));
	}	
	else 
	{
		ServoOut = SERVO_MID - ServoThisError * ServoThisError / ServoKp + ServoKd * (ServoThisError - ServoLastError); 
	  Left.Speed = (u8)(speed*( 1 - (ServoOut-SERVO_MID) / 800 ));
		Right.Speed = (u8)(speed * (1 + (ServoOut-SERVO_MID) / 800 ));	 
	}	
	if(ServoOut > SERVO_LEFT_MAX ) 	ServoOut = SERVO_LEFT_MAX;
  else if ( ServoOut < SERVO_RIGHT_MAX ) ServoOut = SERVO_RIGHT_MAX;
	
	ftm_duty_change(FTM2,ftm_ch0,ServoOut);
}
