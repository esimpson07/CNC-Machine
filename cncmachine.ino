#include "StepperController.h"

StepperController sMotor1(33,25,22,true,200000);
StepperController sMotor2(26,27,1,true,10000);
StepperController sMotor3(14,12,23,true,10000);

int motorTime = 1000;
int sMotor1Target = 0;
int sMotor2Target = 0;
int sMotor3Target = 0;

void setup() {
  Serial.begin(115200);
  sMotor1.begin();
  sMotor2.begin();
  sMotor3.begin();
}

void readSerial() {
  if (Serial.available() > 0) {
    String str = Serial.readString();
    if(str.indexOf("M1") >= 0){
      sMotor1Target = str.substring(str.indexOf("M1") + 3,str.indexOf("M2")).toInt();
    }
    if(str.indexOf("M2") >= 0){
      sMotor2Target = str.substring(str.indexOf("M2") + 3,str.indexOf("M3")).toInt();
    }
    if(str.indexOf("M3") >= 0){
      sMotor3Target = str.substring(str.indexOf("M3") + 3,str.indexOf("S")).toInt();
    } else if(str.indexOf("S") >= 0){
      motorTime = str.substring(str.indexOf("S") + 2,str.indexOf(";")).toInt();
    }
  }
}

void loop() {
  readSerial();
  if(millis() % 2000 == 0) {
    if(sMotor1Target != 0){
      sMotor1.setTarget(sMotor1Target,abs(sMotor1Target) / (int)((double)motorTime / 1000.0));
      sMotor1Target = 0;
    }
    if(sMotor2Target != 0){
      sMotor2.setTarget(sMotor2Target,abs(sMotor2Target) / (int)((double)motorTime / 1000.0));
      sMotor2Target = 0;
    }
    if(sMotor3Target != 0){
      sMotor3.setTarget(sMotor3Target,abs(sMotor3Target) / (int)((double)motorTime / 1000.0));
      sMotor3Target = 0;
    }
  }
  sMotor1.process();
  sMotor2.process();
  sMotor3.process();
}
