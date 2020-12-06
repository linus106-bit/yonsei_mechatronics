#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

#define ENCODERA 23 
#define ENCODERB 24 
#define ENC2GEAR 216

#define MOTOR1 21
#define MOTOR2 20

#define PGAIN 1100
#define IGAIN 24400
#define DGAIN 12.5
#define LOOPTIME 1
#define tau 0.001

int encA;
int encB;
int encoderPosition = 0;
float GearPosition = 0;

float referencePosition;
float errorPosition;
float error_prev;


float startTime;
float checkTime;
float checkTimeBefore;

float IC = 0;
float control = 0;

float lpf;
float lpf_prev;

float t;
float t_s;


void funcEncoderA()
{
	encA = digitalRead(ENCODERA);
	encB = digitalRead(ENCODERB);

	if (encA == HIGH) // If A is rising
	{
		if (encB == LOW)  // A HIGH, B LOW
			encoderPosition++;
		else		// A HIGH, B HIGH
			encoderPosition--;
	}
	else // If A is falling
	{
		if (encB == LOW)  // A LOW, B LOW
			encoderPosition--;
		else		// A LOW, B HIGH
			encoderPosition++;
	}
	GearPosition = (float)encoderPosition / ENC2GEAR;
}

void funcEncoderB()
{
	encA = digitalRead(ENCODERA);
	encB = digitalRead(ENCODERB);

	if (encB == HIGH) // If B is rising
	{
		if (encA == LOW)  // A LOW, B HIGH
			encoderPosition--;
		else		// A HGIH, B HIGH
			encoderPosition++;
	}
	else
	{
		if (encA == LOW)	// A LOW, B LOW
			encoderPosition++;
		else		// A HIGH, B LOW
			encoderPosition--;
	}
	GearPosition = (float)encoderPosition / ENC2GEAR;
}

int main(void)
{
	FILE * fp = fopen("2016145028.txt", "w");
	
	referencePosition = 0;
	lpf_prev = 0;
	error_prev = referencePosition;
	errorPosition = referencePosition;

	wiringPiSetupGpio();
	pinMode(ENCODERA, INPUT);
	pinMode(ENCODERB, INPUT);

	softPwmCreate(MOTOR1, 0, 100);
	softPwmCreate(MOTOR2, 0, 100);

	wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
	wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);

	startTime = millis();
	checkTimeBefore = millis();


while(1)
{	
	checkTime = millis();
	t = (checkTime - startTime)/1000;
	referencePosition = 3*(0.1*t*sin(0.1*t)+(0.1*t-1)*cos(2*t))+3;
	float lpf = (tau*lpf_prev + (LOOPTIME*0.001)*GearPosition)/(tau + (LOOPTIME*0.001));
	errorPosition = referencePosition - lpf;

	if(checkTime - checkTimeBefore >= LOOPTIME)
	{
		float PC = PGAIN * errorPosition;
		float IC = IC + IGAIN * errorPosition * LOOPTIME * 0.001;
		if(IC < -100)
		{
			IC = -100;
		}
		else if(IC > 100)
		{
			IC = 100;
		}
		
		float DC = DGAIN * (errorPosition - error_prev) * 1000 / LOOPTIME;
		
		float control = PC + IC + DC;
		
		if(errorPosition < 0)
		{	
			softPwmWrite(MOTOR1, (-1) * (control));
			softPwmWrite(MOTOR2, 0);
		
		} 
		else
		{
			softPwmWrite(MOTOR1, 0);
			softPwmWrite(MOTOR2, (control));
			
		}
		
		fprintf(fp, "%0.3f %f\n", (checkTime - startTime) / 1000, GearPosition);

		printf("referencePosition: %f, error: %f, position: %f\n",referencePosition, errorPosition, GearPosition);	

		lpf_prev = lpf;

		error_prev = errorPosition;
		checkTimeBefore = checkTime;
		
		
		if((checkTime - startTime) / 1000 >= 15)
		{	
			fclose(fp);
			
			break;

		}
	
	}
}

return 0;
}
