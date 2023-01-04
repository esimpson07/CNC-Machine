#include "StepperController.h"
#include "Arduino.h"

StepperController::StepperController(short dirPin, short pulsePin, short endstopPin, bool endstopDir, int maxSteps) {
  m_pulsePin = pulsePin;
  m_dirPin = dirPin;
  m_endstopPin = endstopPin;
  m_endstopDir = endstopDir;
  m_maxSteps = maxSteps;
}

void StepperController::begin() {
  pinMode(m_endstopPin,INPUT_PULLUP);
  pinMode(m_pulsePin,OUTPUT);
  pinMode(m_dirPin,OUTPUT);
}

void StepperController::calibrate() {
  process();
  digitalRead(m_endstopPin);
}

void StepperController::setTarget(int target, int stepsPerSecond) {
  m_delay = 1000000 / stepsPerSecond;
  Serial.print("delay = ");
  Serial.println(m_delay);
  m_target = target;
  process();
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
