#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR1 21
#define MOTOR2 20
#define ENCODERA 23
#define ENCODERB 24

int encA;
int encB;



void funcEncoderA()
{
    printf("funcENCODERA() ");
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    printf("%d %d\n", encA, encB);
}

void funcEncoderB()
{
    printf("funcENCODERB() ");
    encA = digitalRead(ENCODERA);
    encB = digitalRead(ENCODERB);
    printf("%d %d\n", encA, encB);
}

int main(void)
{
    wiringPiSetupGpio();
    pinMode(ENCODERA, INPUT);
    pinMode(ENCODERB, INPUT);

    wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
    wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);
    while (1)
    {
        // Loop Forever
    }
    return 0;
}

