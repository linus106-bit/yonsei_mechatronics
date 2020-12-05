#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define LED_R 18
#define LED_Y 12
#define LED_G 17


char *pos_R;
char *pos_Y;
char *pos_G;
int time;
int move_pos;



int main(void)

{
    
    wiringPiSetupGpio();
    pinMode(LED_R,OUTPUT);
    pinMode(LED_Y,OUTPUT);
    pinMode(LED_G,OUTPUT);
    softPwmCreate(LED_R,0,100);
    softPwmCreate(LED_Y,0,100);
    softPwmCreate(LED_G,0,100);
    for (int i=1; i < 100; i++)
    {
        time = i;
        int leftov = i % 6;
        switch (leftov)
        {
            case 5:
                softPwmWrite(LED_R,100);
                softPwmWrite(LED_Y,0);
                softPwmWrite(LED_G,20);
                pos_R = "HIGH";
                pos_Y = "LOW";
                pos_G = "0";
                break;
            case 0:
                softPwmWrite(LED_R,20);
                softPwmWrite(LED_Y,0);
                softPwmWrite(LED_G,100);
                pos_R = "0";
                pos_Y = "LOW";
                pos_G = "HIGH";
                break;
            case 1:
                softPwmWrite(LED_R,0);
                softPwmWrite(LED_Y,20);
                softPwmWrite(LED_G,100);
                pos_R = "LOW";
                pos_Y = "0";
                pos_G = "HIGH";
                break;
            case 2:
                softPwmWrite(LED_R,0);
                softPwmWrite(LED_Y,100);
                softPwmWrite(LED_G,20);
                pos_R = "LOW";
                pos_Y = "HIGH";
                pos_G = "0";
                break;
            case 3:
                softPwmWrite(LED_R,20);
                softPwmWrite(LED_Y,100);
                softPwmWrite(LED_G,0);
                pos_R = "0";
                pos_Y = "HIGH";
                pos_G = "LOW";
                break;
            case 4:
                softPwmWrite(LED_R,100);
                softPwmWrite(LED_Y,20);
                softPwmWrite(LED_G,0);
                pos_R = "HIGH";
                pos_Y = "0";
                pos_G = "LOW";
                break;
        }
        printf("Time : %d sec, MOVING PART POS. : %d mm, Phase A: %s,Phase B: %s, Phase C: %s \n",i,i,pos_R,pos_Y,pos_G);
        delay(1000);
    }
    
    return 0;
}
