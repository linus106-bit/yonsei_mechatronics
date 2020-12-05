#include <stdio.h>
#include <wiringPi.h>

#define LED_R 18
#define LED_Y 12
#define LED_G 17


int pos_R;
int pos_Y;
int pos_G;
int time;
int move_pos;



int main(void)

{
    
    wiringPiSetupGpio();
    pinMode(LED_R,OUTPUT);
    pinMode(LED_Y,OUTPUT);
    pinMode(LED_G,OUTPUT);
    for (int i=0; i < 100; i++)
    {
        time = i;
        digitalWrite(LED_R,LOW);
        digitalWrite(LED_Y,LOW);
        digitalWrite(LED_G,LOW);

        pos_R = digitalRead(LED_R);
        pos_Y = digitalRead(LED_Y);
        pos_G = digitalRead(LED_G);
        printf("Time : %d sec, MOVING PART POS. : %d mm, Phase A: %c \n",i,i,pos_R);
    }
    
    return 0;
}
