#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

#define REFERENCE 10

#define MOTOR1 21
#define MOTOR2 20

#define ENCODERA 23
#define ENCODERB 24
#define ENC2GEAR 216 //12*18 = 216

#define PGAIN 1000// 850
#define IGAIN 19000
#define DGAIN 12

#define LOOPTIME 1 // unit : millisec

int encA;
int encB;
int encoderPosition = 0;
float GearPosition = 0;

int referencePosition;
float errorPosition;
float error_prev;


float I = 0;
float I_past = 0;
float itea = 0;


float startTime;
float checkTime;
float checkTimeBefore;
float t;

void funcEncoderA()
{
    
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    
    if (encA == HIGH)
    {
		if (encB == LOW)
			encoderPosition++;
		else
			encoderPosition--;
	}
	
	else
	{
		if (encB == LOW)
			encoderPosition--;
		else
			encoderPosition++;
	}
	GearPosition = (float)encoderPosition / ENC2GEAR;
	errorPosition = referencePosition -GearPosition;
}

void funcEncoderB()
{
    
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    
    if (encB == HIGH)
    {
		if (encA == LOW)
			encoderPosition--;
		else
			encoderPosition++;
	}
	
	else
	{
		if (encA == LOW)
			encoderPosition++;
		else
			encoderPosition--;
	}
	GearPosition = (float)encoderPosition / ENC2GEAR;
	errorPosition = referencePosition - GearPosition;
}

int main(void)
{
	referencePosition = REFERENCE;
	FILE* fp = fopen("2016145122.txt", "w");
	error_prev = referencePosition;
	errorPosition = referencePosition;
	
    wiringPiSetupGpio();
    pinMode(ENCODERA, INPUT);
    pinMode(ENCODERB, INPUT);
    softPwmCreate(MOTOR1,0,100);
    softPwmCreate(MOTOR2,0,100);
	
    wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
    wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);
	startTime = millis();
    checkTimeBefore = millis();
    while (1)
    {
        checkTime = millis();
		
        //unsigned int interval = checkTime - checkTimeBefore;
        // unsigned int time_now = checkTime - startTime;
        if (checkTime - checkTimeBefore >= LOOPTIME)
        {
            float P = PGAIN * errorPosition;        	
			I = I_past + error_prev * (LOOPTIME * 0.001)* IGAIN  ;
			if(I > 100)
			{
				I = 100;
			}
			else if(I < -100)
			{
				I = -100;
			}
            float D = DGAIN * (errorPosition - error_prev) * 1000;
			float PID = (P+I+D);


			if(errorPosition < 0)
			{
				softPwmWrite(MOTOR1, (-1)*(PID));
				softPwmWrite(MOTOR2, 0);
				
			}
			else
			{
				softPwmWrite(MOTOR1, 0);
				softPwmWrite(MOTOR2, (PID));
				
			}
			fprintf(fp, "%0.3f %f\n", (checkTime - startTime) / 1000, GearPosition);
			// fprintf(fp, "%0.3f PID: %f\n", (checkTime - startTime) / 1000, PID);
			// fprintf(fp, "P: %f, I: %f, D: %f \n", P, I, D);
			printf("error: %f, position: %f\n", errorPosition, GearPosition);
			error_prev = errorPosition;
			checkTimeBefore = checkTime;
			I_past = I;
			// itea += abs(errorPosition)*LOOPTIME*(checkTime - startTime)*0.001*0.001;
			
		}
		if((checkTime - startTime) / 1000 >= 15)
			{
				break;
			}  
	
   	}
	printf("itea = %f \n",itea);
	fclose(fp);
    return 0;
}