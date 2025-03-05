//===== Servo Assignments =====
#include <Servo.h>

Servo Q1;
Servo Q2;
Servo Q3;
Servo Q4;
Servo Q5;
Servo Q6;

//===== Serial Parsing =====
const int buttonPin = 2;
const int inputLatency = 1000;   
int buttonState = 0;
int servoState = 0;

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing
int q[7] = {0,90,80,90,80,90,80};
boolean newData = false;
boolean randomMotion = false;

//===== Reset Joint Sequence =====
void reset(){
  q[1] = 90;
  q[2] = 90;
  q[3] = 90;
  q[4] = 20;
  q[5] = 90;
  q[6] = 90; 
  writeToServos(q);
  delay(1000);
  q[4] = 80;
  writeToServos(q);
}

void setup(){
  Serial.begin(9600);
  Q1.attach(3);
  Q2.attach(5);
  Q3.attach(6);
  Q4.attach(9);
  Q5.attach(10);
  Q6.attach(11);
  pinMode(buttonPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  reset();
  //Serial.println("Ready to receive joint values array in square brackets");
}


void loop(){
  buttonState = digitalRead(buttonPin);
  int jointLimBuffer = 20;
  int jointMinLim = 0+jointLimBuffer;
  int jointMaxLim = 180-jointLimBuffer;
  if (buttonState == HIGH) {
    reset();
    delay(inputLatency);   
  }
  recvWithStartEndMarkers();
  if (newData == true) {
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() used in parseData() replaces the commas with \0
      parseData();
      // showJointData();
      newData = false;
      writeToServos(q);
      // send msg "ready for new joint values"
      // 
  }
  else if (newData == false && randomMotion == true) {
    for(int i = 1; i < 7 ; i++){
      int a = q[i]-30;
      int b = q[i]+30;
      if (q[i]-30 < jointMinLim)
      {
        a = jointMinLim;
      }
      if (q[i]+30 > jointMaxLim)
      {
        b = jointMaxLim;
      }
      if (q[2]+30 > 80)
      {
        b = 80;
      }
      q[i] = random(a,b);
    }
    writeToServos(q);
    // showJointData();
    delay(random(200,2000));
  }
}

void writeToServos(int q[]) {
    Q1.write(q[1]);
    Q2.write(q[2]);
    Q3.write(q[3]);
    Q4.write(q[4]);
    Q5.write(q[5]);
    Q6.write(q[6]);
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '[';
    char endMarker = ']';
    char incomingData;

    if (Serial.available() > 0 && newData == false) {
        incomingData = Serial.read();

        if (recvInProgress == true) {
            if (incomingData != endMarker) {
                receivedChars[ndx] = incomingData;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (incomingData == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseData() {      // split the data into its parts

    char* strtokIndx; // this is used by strtok() as an index
 
    strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
    
    q[0] = atoi(strtokIndx);     // convert this part to an integer
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    q[1] = atoi(strtokIndx);     // convert this part to an integer
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    q[2] = atoi(strtokIndx);     // convert this part to an integer
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    q[3] = atoi(strtokIndx);     // convert this part to an integer
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    q[4] = atoi(strtokIndx);     // convert this part to an integer
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    q[5] = atoi(strtokIndx);     // convert this part to an integer
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    q[6] = atoi(strtokIndx);     // convert this part to an integer

}

void showJointData() {
    Serial.println("Joints Array: ");
    Serial.print("[");
    for(int i = 0; i < 6; i++){
      Serial.print(q[i]);
      Serial.print(", ");
    }
    Serial.print(q[6]);
    Serial.println("] ");
    Serial.println();

}
