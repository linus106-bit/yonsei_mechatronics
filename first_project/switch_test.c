#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SWITCH3 13 // stop
#define SWITCH2 19 // Low
#define SWITCH1 26 // Fast

#define LED_R 22 // Stop
#define LED_Y 4 // CCW
#define LED_G 27 // CW

#define MOTOR1 21
#define MOTOR2 20

#define ENCODERA 23
#define ENCODERB 24
#define ENC2GEAR 216 //12*18 = 216

int encA;
int encB;
int pos_a;
int encoderPosition = 0;
float GearPosition = 0;
int switch_1 = 0;
int switch_2 = 0;
int switch_3 = 0;

void MOTOR_STOP()
{
    softPwmWrite(MOTOR1,0);
    softPwmWrite(MOTOR2,0);
    softPwmWrite(LED_R,100);
    softPwmWrite(LED_G,0);
    softPwmWrite(LED_Y,0);
}


void MOTOR_LOW_CW()
{

    softPwmWrite(MOTOR1,0);
    softPwmWrite(MOTOR2,30);
    softPwmWrite(LED_R,0);
    softPwmWrite(LED_G,30);
    softPwmWrite(LED_Y,0);
}
    
void MOTOR_LOW_CCW()
{

    softPwmWrite(MOTOR2,0);
    softPwmWrite(MOTOR1,30);
    softPwmWrite(LED_R,0);
    softPwmWrite(LED_G,0);
    softPwmWrite(LED_Y,30);
}

void MOTOR_FAST_CW()
{
    softPwmWrite(MOTOR1,0);
    softPwmWrite(MOTOR2,100);
    softPwmWrite(LED_R,0);
    softPwmWrite(LED_G,100);
    softPwmWrite(LED_Y,0);
    printf("Fast \n");

}

void MOTOR_FAST_CCW()
{
    softPwmWrite(MOTOR2,0);
    softPwmWrite(MOTOR1,100);
    softPwmWrite(LED_R,0);
    softPwmWrite(LED_G,0);
    softPwmWrite(LED_Y,100);
    printf("Fast \n");

}

int main(void){
    wiringPiSetupGpio();
 
    // INPUT
    
    pinMode(SWITCH1, INPUT);
    pinMode(SWITCH2, INPUT);
    pinMode(SWITCH3, INPUT); 
    
    // OUTPUT
    pinMode(LED_R, OUTPUT); 
    pinMode(LED_Y, OUTPUT); 
    pinMode(LED_G, OUTPUT);
    // PWM
    softPwmCreate(LED_R,0,100);
    softPwmCreate(LED_Y,0,100);
    softPwmCreate(LED_G,0,100);
    softPwmCreate(MOTOR1,0,100);
    softPwmCreate(MOTOR2,0,100);    

    softPwmWrite(LED_R,0);
    while(1){
        if(digitalRead(SWITCH1) == HIGH){
            switch_1++;
            switch_2 = 0;
            switch_3 = 0;
            
            MOTOR_STOP();
            if(digitalRead(SWITCH3) == HIGH || digitalRead(SWITCH2) == HIGH)
            {
                break;
            }
            else if(digitalRead(SWITCH1) == HIGH)
            {
                printf("Stop \n");
            }
        
        }
        else if(digitalRead(SWITCH2) == HIGH){
            switch_2++;
            printf("Button2 was pressed\n");
            printf("switch_2 : %d \n", switch_2);
            
            if(digitalRead(SWITCH1) == HIGH || digitalRead(SWITCH3) == HIGH)
            {
                break;
            }
            else if(switch_2 % 2 == 0)
            {
                if(switch_3 % 2 == 0)
                {
                    MOTOR_LOW_CCW();
                }
                else if(switch_3 % 1 == 0)
                {
                    MOTOR_LOW_CW();
                }
            }
            else if(switch_2 % 2 == 1)
            {
                if(switch_3 % 2 == 0)
                {
                    MOTOR_LOW_CW();
                }
                else if(switch_3 % 1 == 0)
                {
                    MOTOR_LOW_CCW();
                }
            }
        }
        else if(digitalRead(SWITCH3) == HIGH){
            switch_3++;
            printf("Button3 was pressed\n");
            printf("switch_3 : %d \n", switch_3);
            
            
            if(digitalRead(SWITCH1) == HIGH || digitalRead(SWITCH2) == HIGH)
            {
                break;
            }
            else if(switch_3 % 2 == 0)
            {
                if(switch_2 % 2 == 0)
                {
                    MOTOR_FAST_CW();
                }
                else if(switch_2 % 1 == 0)
                {
                    MOTOR_FAST_CCW();
                }
            }
            else if(switch_3 % 2 == 1)
            {
                if(switch_2 % 2 == 0)
                {
                    MOTOR_FAST_CCW();
                }
                else if(switch_2 % 1 == 0)
                {
                    MOTOR_FAST_CW();
                }
            }            
        }
        else{
            
        }
    
        delay(300);
       
    }
    return 0;
}
