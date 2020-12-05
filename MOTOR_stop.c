#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR1 21
#define MOTOR2 20


int main(void)
{
    wiringPiSetupGpio();
    softPwmCreate(MOTOR1,0,100);
    softPwmCreate(MOTOR2,0,100);

    while (1)
    {
        int cnt = 0;
        for (; cnt < 100; cnt++)
        {
            softPwmWrite(MOTOR1, 0);
            softPwmWrite(MOTOR2, 0);
            delayMicroseconds(10000);
        }
        
        cnt = 0;
        for (; cnt < 100; cnt++)
        {
            softPwmWrite(MOTOR1, 0);
            softPwmWrite(MOTOR2, 0);
            delayMicroseconds(10000);
        }
        break;
    }
    return 0;
}

