#include "StepperController.h"
#include "Arduino.h"

StepperController::StepperController(short dirPin, short pulsePin, short endstopPin, bool endstopDir, int maxSteps) {
  m_pulsePin = pulsePin;
  m_dirPin = dirPin;
  m_endstopPin = endstopPin;
  m_endstopDir = endstopDir;
  m_maxSteps = maxSteps;
  m_switchCycles = 0;
}

void StepperController::begin() {
  pinMode(m_endstopPin,INPUT_PULLUP);
  pinMode(m_pulsePin,OUTPUT);
  pinMode(m_dirPin,OUTPUT);
}

void StepperController::calibrate() {
  if(m_endstopDir == true) {
    setTarget(m_maxSteps,10000);
  } else {
    setTarget(-m_maxSteps,10000);
  }
  while(readSwitch() == 0) {
    process();
  }
  if(m_endstopDir == true) {
    setTarget(-m_maxSteps,5000);
  } else {
    setTarget(m_maxSteps,5000);
  }
  while(readSwitch() == 1) {
    process();
  }
  setTarget(0,1000);
  Serial.println("Calibration complete on a motor");
}

void StepperController::setTarget(int target, int stepsPerSecond) {
  m_delay = 1000000 / stepsPerSecond;
  m_pastTime = m_micros;
  m_target = target;
}

bool StepperController::readSwitch() {
  if(digitalRead(m_endstopPin) == 0 && m_switchCycles <= 45) {
    m_switchCycles += 2;
  } else if(m_switchCycles > 0) {
    m_switchCycles --;
  }
  if(m_switchCycles > 20) {
    return(true);
  } else {
    return(false);
  }
}

bool StepperController::process() {
  m_micros = micros();
  if(m_target != 0) {
    if(m_micros >= m_pastTime + m_delay && m_state == true) {
      digitalWrite(m_dirPin,0.5 * (m_target / abs(m_target) + 1));
      m_pastTime = m_pastTime + m_delay;
      m_state = false;
      m_target -= (m_target / abs(m_target));
      digitalWrite(m_pulsePin, HIGH);
    } else if(m_micros >= m_pastTime + m_delay && m_state == false) {
      digitalWrite(m_dirPin,0.5 * (m_target / abs(m_target) + 1));
      m_pastTime = m_pastTime + m_delay;
      m_state = true;
      m_target -= (m_target / abs(m_target));
      digitalWrite(m_pulsePin, LOW);
    }
    return(false);
  } else {
    return(true);
  }
}

void StepperController::eStop() {
  
}
