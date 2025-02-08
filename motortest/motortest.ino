#include <Servo.h>

Servo Q1;
Servo Q2;
Servo Q3;
Servo Q4;
Servo Q5;
Servo Q6;
const int buttonPin = 2;
int buttonState = 0;
int servoState = 0;
int motorangle = 90;

void setup() 
{
  Serial.begin(9600);
  Q1.attach(3);
  Q2.attach(5);
  Q3.attach(6);
  Q4.attach(9);
  Q5.attach(10);
  Q6.attach(11);
  pinMode(buttonPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Q1.write(90);
  Q2.write(90);
  Q3.write(90);
  Q4.write(90);
  Q5.write(90);
  Q6.write(90);
}
void loop() 
{
  buttonState = digitalRead(buttonPin);  //read button
  int inputLatency = 1000;   
  if(buttonState == HIGH)                //swap states
  {
    motorangle = motorangle + 45;
    delay(inputLatency);
  }
  if (motorangle > 180)
  {
    motorangle = 0;
  }
  Q2.write(motorangle);

}