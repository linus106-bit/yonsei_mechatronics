#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>
#define LED_R 18
#define LED_Y 12
#define LED_G 17
#define PI 3.1415926535897

float pos_R;
float pos_Y;
float pos_G;
float time;
int move_pos;
float sin_R;
float sin_Y;
float sin_G;

double getRadian(int a)
{
        return a*(PI/180);
}
int main(void)

{
    
    wiringPiSetupGpio();
    pinMode(LED_R,OUTPUT);
    pinMode(LED_Y,OUTPUT);
    pinMode(LED_G,OUTPUT);
    softPwmCreate(LED_R,0,100);
    softPwmCreate(LED_Y,0,100);
    softPwmCreate(LED_G,0,100);
    for (int i=0; i < 10000; i++)
    {
        time = i*0.01;
        float num = getRadian(60);
        sin_R = 0.5*(sin(num*(time-3.5))+1);
        sin_Y = 0.5*(sin(num*(time-1.5))+1);
        sin_G = 0.5*(sin(num*(time+0.5))+1);
        
        pos_R = sin(num*(time-3.5));
        pos_Y = sin(num*(time-1.5));
        pos_G = sin(num*(time+0.5));
        
        printf("R: %f,Y: %f, G: %f \n",sin_R,sin_Y,sin_G);
        softPwmWrite(LED_R,sin_R*100);
        softPwmWrite(LED_Y,sin_Y*100);
        softPwmWrite(LED_G,sin_G*100);
        
        printf("Time : %.2f sec, MOVING PART POS. : %.2f mm, Phase A: %f,Phase B: %f, Phase C: %f \n",time,time,pos_R,pos_Y,pos_G);
        
        delay(10);
    }
    
    return 0;
}
