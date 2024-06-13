#include "StepperController.h"
#define INCH false
#define MM true
/*
 * 2 mm per rotation of the stepper motor
 * 1.8 degree stepper: theoretical 200 steps : 2 mm
 * 100 mm = 10000 steps??
 * NOPE!!!
 * 80 mm / 128,000 steps!!!!
 * thread pitch 2 mm BUT quadruple threaded!!!!!!
 * 12800 steps / rotation because 6400 steps per rotation 
 * on stepper driver + 2x multiplier because toggle on and off
 */

StepperController sMotor1(33,25,18,true,2000000);
StepperController sMotor2(26,27,5,true,1000000);
StepperController sMotor3(14,12,19,false,1000000);

int motorTime = 1000;
double xTarget; //all targets are in mm
double yTarget;
double zTarget;
/*int sMotor1Target = 0;
int sMotor2Target = 0;
int sMotor3Target = 0;*/

/*String possibleCommands[21] = {"G21","G40","G49","G80","G90",
                              "M5","T1","M6","S","M3",
                              "G54","G0","B-90","C-180","G17",
                              "X","Y","Z","I","K","M30"};

String parseCommands[5] = {"G21","G40","G49","G80","G90"};*/

/*enum Command {G21,G40,G49,G80,G90,M5,T1,M6,S,M3,G54,
                      G0,A,B,C,G17,X,Y,Z,I,K,M30};
*/
void setup() {
  Serial.begin(115200);
  /*pinMode(16,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(16,LOW);
  digitalWrite(4,HIGH);
  ledcAttachPin(17,5);
  ledcSetup(5,40000,8);
  ledcWrite(5,255);*/
  sMotor1.begin();
  sMotor2.begin();
  sMotor3.begin();
  sMotor1.calibrate();
  sMotor2.calibrate();
  sMotor3.calibrate();
  sMotor1.setMode(MM);
  sMotor2.setMode(MM);
  sMotor3.setMode(MM);
  Serial.print("$cc");
}

void processGCode() {
  String commandString = waitForSerial();
  Command cmd = G0;

  switch(cmd)
  {
    case G0: break;
    case G21: break;
    case G40: break;
    case G49: break;
    case G54: break;
    case G80: break;
    case G90: break;
    case M3: break;
    case M5: break;
    case M6: break;
    case M30: break;
    case T1: break;
    case S: break;
    case A: break;
    case B: break;
    case C: break;
    case G17: break;
    case X: 
      setXTarget(commandString.subString(indexOf("X"),
      commandString.subString(indexOf("X"),commandString.length)
      .indexOf(" ")).toInt());
    break;
    case Y: 
      setYTarget(commandString.subString(indexOf("Y"),
      commandString.subString(indexOf("Y"),commandString.length)
      .indexOf(" ")).toInt());
    break;
    case Z:
      setZTarget(commandString.subString(indexOf("Z"),
      commandString.subString(indexOf("Z"),commandString.length)
      .indexOf(" ")).toInt());
    break;
    case I: break;
    case K: break;
    default: Serial.print("!uc"); break;
  }
  
  Serial.print("&ca");
}*/

void setXTarget(double target) {
  xTarget = target;
}

void setYTarget(double target) {
  yTarget = target;
}

void setZTarget(double target) {
  zTarget = target;
}

String waitForSerial() {
  while(true) {
    if (Serial.available() > 0) {
      return(Serial.readString);
    }
  }
}
/*
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
    }
    if(str.indexOf("S") >= 0){
      motorTime = str.substring(str.indexOf("S") + 2,str.indexOf(";")).toInt();
    }
  }
}*/

void loop() {
  readSerial();
  if(millis() % 2000 == 0) {
    if(sMotor1Target != 0){
      sMotor1.setTarget(sMotor1Target,(int)((double)abs(sMotor1Target) / ((double)motorTime / 1000.0)));
      Serial.println(sMotor1Target);
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
