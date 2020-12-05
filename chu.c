#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define REFERENCE 5

#define ENCODERB 23 // BLUE
#define ENCODERA 24 // PURPLE
#define ENC2GEAR 216

#define MOTOR1 20
#define MOTOR2 21

#define PGAIN 1120
#define IGAIN 26000
#define DGAIN 12
#define LOOPTIME 1

int encA;
int encB;
int encoderPosition = 0;
float GearPosition = 0;
float input_value = 0;

int referencePosition = REFERENCE;
float errorPosition;
float error_prev;
float I_control =0;

float startTime;
float checkTime;
float checkTimeBefore;

float ITAE_func = 0;

void funcEncoderA()
{
   encA = digitalRead(ENCODERA);
   encB = digitalRead(ENCODERB);

   if (encA == HIGH) // If A is rising
   {
      if (encB == LOW)  // A HIGH, B LOW
         encoderPosition++;
      else      // A HIGH, B HIGH
         encoderPosition--;
   }
   else // If A is falling
   {
      if (encB == LOW)  // A LOW, B LOW
         encoderPosition--;
      else      // A LOW, B HIGH
         encoderPosition++;
   }
   GearPosition = (float)encoderPosition / ENC2GEAR;
   errorPosition = referencePosition - GearPosition;
}

void funcEncoderB()
{
   encA = digitalRead(ENCODERA);
   encB = digitalRead(ENCODERB);

   if (encB == HIGH) // If B is rising
   {
      if (encA == LOW)  // A LOW, B HIGH
         encoderPosition--;
      else      // A HGIH, B HIGH
         encoderPosition++;
   }
   else
   {
      if (encA == LOW)   // A LOW, B LOW
         encoderPosition++;
      else      // A HIGH, B LOW
         encoderPosition--;
   }
   GearPosition = (float)encoderPosition / ENC2GEAR;
   errorPosition = referencePosition - GearPosition;
}

int main()
{
//   printf("Write # of revolution: "); 
//   scanf("%d", &referencePosition);
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

   FILE*fp = fopen("2016145028.txt", "w");

    while(1)
    {   
        checkTime = millis();
                
        if(checkTime - checkTimeBefore >=LOOPTIME)
        {
            float P_control = PGAIN * errorPosition;
            I_control += errorPosition * (LOOPTIME * 0.001);
            float D_control = DGAIN * (errorPosition - error_prev) / LOOPTIME * 1000;
            fprintf(fp, "%0.3f %f\n", (checkTime - startTime) / 1000, GearPosition);
            fprintf(fp,"P: %f, I: %f, D: %f \n",P_control, I_control, D_control);
            fprintf(fp,"error: %f, position: %f\n", errorPosition, GearPosition);           
            if(errorPosition < 0)
            {
                softPwmWrite(MOTOR1, (-1) * (P_control + IGAIN * I_control + D_control));
                softPwmWrite(MOTOR2, 0);
                
                ITAE_func -= errorPosition * LOOPTIME * (checkTime - checkTimeBefore) / 1000;
            }
            else
            {
                softPwmWrite(MOTOR1, 0);
                softPwmWrite(MOTOR2, (P_control + IGAIN * I_control + D_control));
                
                ITAE_func += errorPosition * LOOPTIME * (checkTime - checkTimeBefore) / 1000;
            }
            
            
            
            error_prev = errorPosition;
            checkTimeBefore = checkTime;
            fprintf(fp,"error2: %f, position2: %f\n", errorPosition, GearPosition);

            
            
            if((checkTime - startTime) / 1000 >= 5)
            {      
                fclose(fp);
                
                printf("ITAE : %f ", ITAE_func);
                
                break;

            }
        }
    }
    

return 0;
}