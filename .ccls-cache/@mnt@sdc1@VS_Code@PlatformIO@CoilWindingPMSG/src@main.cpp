#include <Arduino.h>
#include <AccelStepper.h>

#define PWMA 7
#define AIN2 8
#define AIN1 9
#define STBY 10
#define BIN1 11
#define BIN2 12
#define PWMB 13

#define SPR 200
#define SPEED 150
#define ACCEL 200
#define WAIT 2000

const int turns = 80;
const int pauseDiv = 10;
int n = 0;

void stepSetup();
AccelStepper stepper(AccelStepper::FULL4WIRE, AIN1,AIN2,BIN1,BIN2);

void setup()
{
  stepSetup();
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(SPEED);
  stepper.setCurrentPosition(0);
  stepper.setAcceleration(ACCEL);
  stepper.moveTo(SPR*pauseDiv);

  delay(WAIT);
}

void loop()
{
  stepper.run();

  if (!stepper.isRunning()) {
    n++;
    while (n > turns / pauseDiv - 1)  stepper.disableOutputs();
    delay(WAIT);
    stepper.setCurrentPosition(0);
    stepper.moveTo(SPR*pauseDiv);
  }
}

void stepSetup() {
  pinMode(PWMA, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(PWMA, HIGH);
  digitalWrite(PWMB, HIGH);
  digitalWrite(STBY, HIGH);
}
