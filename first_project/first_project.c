#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>


#define LED_R 17 // Stop
#define LED_Y 27 // CCW
#define LED_G 22 // CW
#define BUTTON_L 6 // LOW 30%
#define BUTTON_F 5 // Fast
#define BUTTON_S 26 // Stop
#define MOTOR_A 21 //
#define MOTOR_B 20 // 


void MOTOR_STOP()
{
    softPwmWrite(MOTOR_A,0);
    softPwmWrite(MOTOR_B,0);
    softPwmWrite(LED_R,100);
    softPwmWrite(LED_G,0);
    softPwmWrite(LED_Y,0);
    printf("STOP \n");
}


void MOTOR_LOW()
{
    while(1)
    {
        softPwmWrite(MOTOR_A,30);
        softPwmWrite(MOTOR_B,0);
        softPwmWrite(LED_R,0);
        softPwmWrite(LED_G,30);
        softPwmWrite(LED_Y,0);
        printf("Low \n");
    }
}
    

void MOTOR_FAST()
{
    softPwmWrite(MOTOR_A,100);
    softPwmWrite(MOTOR_B,0);
    softPwmWrite(LED_R,0);
    softPwmWrite(LED_G,0);
    softPwmWrite(LED_Y,0);
    printf("Fast \n");

}

int main(void)

{
    wiringPiSetupGpio();
    // Input
    pinMode(BUTTON_S, INPUT);
    pinMode(BUTTON_F, INPUT);
    pinMode(BUTTON_L, INPUT);

    // Output
    pinMode(LED_R, OUTPUT); 
    pinMode(LED_Y, OUTPUT); 
    pinMode(LED_G, OUTPUT); 
    pinMode(MOTOR_A, OUTPUT); 
    pinMode(MOTOR_B, OUTPUT);
    // PWM
    softPwmCreate(LED_R,0,100);
    softPwmCreate(LED_Y,0,100);
    softPwmCreate(LED_G,0,100);
    softPwmCreate(MOTOR_A,0,100);
    softPwmCreate(MOTOR_B,0,100);

    while(1)
    {
        if(digitalRead(BUTTON_S) == HIGH) // Stop
        {
            MOTOR_STOP();
        }

        else if(digitalRead(BUTTON_L) == HIGH) // Low
        {
            MOTOR_LOW();
        }

        else if(digitalRead(BUTTON_F) == HIGH) // Fast
        {
            MOTOR_FAST();
        }

        else
        {
            // pass
        }
    }

    return 0;
}



