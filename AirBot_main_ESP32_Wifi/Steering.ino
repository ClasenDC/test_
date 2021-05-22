
int forwardStory[] = {};

void storyboardTimer(int chapterTime) {
  
}

void setForwardDir() {
 myServo.write(35);
}
void setBackwardDir() {
  myServo.write(95);
}
void setDownwardDir() {
  myServo.write(0);
}
void setUpwardDir() {
  myServo.write(60);
}

void pulseDown() {
  setDownwardDir();
  setBothPulse(500, 1);
}
void pulseUp() {
  setUpwardDir();
  setBothPulse(500, 1);
}
void pulseLeft() {
  setLeftMotor(500);
  myPulse.once(1, setLeftMotor, 0);
}
void pulseRight() {
  setRightMotor(500);
  myPulse.once(1, setRightMotor, 0);
}

void pulseFwd() {
  setForwardDir();
  setBothMotors(500);
  myPulse.once(0.5 ,setBothMotors, 0);
}
void pulseBck() {
  setBackwardDir();
  setBothPulse(500, 1);
}

void setBothPulse(int st, int dur) {
  setBothMotors(st);
  myPulse.once(dur,setBothMotors, 0);
}

void removePulse() {
  setBothMotors(0);
  setForwardDir();
}

void setBothMotors(int val) {
  analogWrite(LEFT_ROTOR, val);
  analogWrite(RIGHT_ROTOR, val);
}
void setRightMotor(int val) {
  analogWrite(RIGHT_ROTOR, val);
}
void setLeftMotor(int val) {
  analogWrite(LEFT_ROTOR, val);
}
