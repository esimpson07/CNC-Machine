#include "StepperController.h"

StepperController sMotor1(33,25,22,true,10000);
StepperController sMotor2(26,27,1,true,10000);
StepperController sMotor3(14,12,23,true,10000);

int motorSpeed = 3000;

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
      sMotor1.setTarget(str.substring(3,str.indexOf(";")).toInt(),motorSpeed);
    } else if(str.indexOf("M2") >= 0){
      sMotor1.setTarget(str.substring(3,str.indexOf(";")).toInt(),motorSpeed);
    } else if(str.indexOf("M3") >= 0){
      sMotor1.setTarget(str.substring(3,str.indexOf(";")).toInt(),motorSpeed);
    } else if(str.indexOf("S") >= 0){
      motorSpeed = str.substring(2,str.indexOf(";")).toInt();
    }
  }
}

void loop() {
  readSerial();
  sMotor1.process();
  sMotor2.process();
  sMotor3.process();
}
