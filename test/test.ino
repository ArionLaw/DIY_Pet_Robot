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
  Q2.write(80);
  Q3.write(90);
  Q4.write(10);
  Q5.write(90);
  Q6.write(80);
  delay(1000);
  Q1.write(90);
  Q2.write(80);
  Q3.write(90);
  Q4.write(80);
  Q5.write(90);
  Q6.write(80);

}
void loop() 
{
   buttonState = digitalRead(buttonPin);  //read button
   int inputLatency = 1000;   
   if(buttonState == HIGH)                //swap states
   {
      if(servoState == 0)
      {
        //Serial.println("1");
        Q1.write(60);
        Q2.write(60);
        Q3.write(60);
        Q4.write(60);
        Q5.write(60);
        Q6.write(60);
        servoState = 1;
        delay(inputLatency);
      }
      else if(servoState ==1)
      {
        //Serial.println("0");
        Q1.write(120);
        Q2.write(60);
        Q3.write(120);
        Q4.write(60);
        Q5.write(120);
        Q6.write(60);
        delay(inputLatency);
        servoState = 0;
      }
      
   } 

}