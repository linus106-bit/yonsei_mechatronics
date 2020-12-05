#include <stdio.h>
#include <wiringPi.h>

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
    for (int i=0; i < 100; i++)
    {
        time = i;
        int leftov = i % 6;
        switch (leftov)
        {
            case 5:
                digitalWrite(LED_R,HIGH);
                digitalWrite(LED_Y,LOW);
                digitalWrite(LED_G,LOW);
                pos_R = "HIGH";
                pos_Y = "LOW";
                pos_G = "LOW";
                break;
            case 0:
                digitalWrite(LED_R,HIGH);
                digitalWrite(LED_Y,LOW);
                digitalWrite(LED_G,HIGH);
                pos_R = "HIGH";
                pos_Y = "LOW";
                pos_G = "HIGH";
                break;
            case 1:
                digitalWrite(LED_R,LOW);
                digitalWrite(LED_Y,LOW);
                digitalWrite(LED_G,HIGH);
                pos_R = "LOW";
                pos_Y = "LOW";
                pos_G = "HIGH";
                break;
            case 2:
                digitalWrite(LED_R,LOW);
                digitalWrite(LED_Y,HIGH);
                digitalWrite(LED_G,HIGH);
                pos_R = "LOW";
                pos_Y = "HIGH";
                pos_G = "HIGH";
                break;
            case 3:
                digitalWrite(LED_R,LOW);
                digitalWrite(LED_Y,HIGH);
                digitalWrite(LED_G,LOW);
                pos_R = "LOW";
                pos_Y = "HIGH";
                pos_G = "LOW";
                break;
            case 4:
                digitalWrite(LED_R,HIGH);
                digitalWrite(LED_Y,HIGH);
                digitalWrite(LED_G,LOW);
                pos_R = "HIGH";
                pos_Y = "HIGH";
                pos_G = "LOW";
                break;
        }
        printf("Time : %d sec, MOVING PART POS. : %d mm, Phase A: %s,Phase B: %s, Phase C: %s \n",i,i,pos_R,pos_Y,pos_G);
        delay(1000);
    }
    
    return 0;
}
