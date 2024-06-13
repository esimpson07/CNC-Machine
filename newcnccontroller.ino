
// * 80 mm / 128,000 steps!!!!

bool mm = true;
int F = 2; //mm or inch / s

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available() > 0) {
    processCommand(Serial.readString().toUpperCase()); //COULD BECOME AN ISSUE IN THE FUTURE!!!!!!!!!!!!!!!!!!!!!!!!
  }
}

void zeroStepper(byte stepperMotor) {
  //give either stepper motor 1, 2, or 3 and just run it in reverse until it bottoms out
  
}

void stepperMove(byte stepperMotor, int feedRate, int posMM) {
  //code for stepper motor movement
}

void processCommand(String command) {
  int b = 0; //UNDESIRABLE
  for(int i = 0; i < command.length(); i ++) {
    if(b == 0) {
      if(
    }
  }
}

bool isLetter(char character) {
  return((character >= 65  &&  character <= 90)); //IF CHARACTER IS UPPERCASE ONLY!!!
}
