void autoBot() {
  // concept is: topsensor is val 1, front is 2, bottom is 4
  
  int sensorVals = 0;  
  int bottom = readBottomSensor();      // Bauch, SRF02
  int front = readFrontSensor();       // Augen, SHARP 


  
  // Calibaration to room 
  int frontRelaxed = 1700;            // front value without obstical
  int bottomRelaxed = 137;            // bottom value without obstical
  
  if(front > frontRelaxed + 300) sensorVals += 1;   
  if(bottom < 20) sensorVals += 2;  
 
  Serial.println("# # # # # # VALUES # # # #"); Serial.println("Front  :" + String(front)); Serial.println("BottomSensor =" + String(bottom)); Serial.println(" ");//Serial.println("SensorVals : " + String(sensorVals));
 
   
//  if(sensorVals > 0) stopAutoBot(); //attach after intervention
  switch (sensorVals) {

    case 1:
      //front 
      Serial.println("Case1: Hindernis Vorne ! Also R(500/0) und dann R(0/500) ! S(95)"); Serial.println(" ");
      setBackwardDir(); 
      //Serial.println("front");
      setLeftMotor(500);
      delay(500);
      setLeftMotor(0);
      delay(1000);
      setRightMotor(500);
      delay(100);
      setBothMotors(0);
      break;
    case 2:
      //bottom
      Serial.println("Case2! Hindernis Unten! Also R(500/500) und dann R(0/0) ! S(?)");Serial.println(" ");
      setUpwardDir();
      setBothMotors(250);
      delay(500);
      setBothMotors(0);     
      break;

    case 3:
      //front&bottom
      Serial.println("Case3! Hindernis Vorne + Unten ! Also R(800/800) und dann R(0/500) ! S(110)");Serial.println(" ");
      myServo.write(180);  
       setBothMotors(800);
      delay(500);
      setLeftMotor(0);
      setBackwardDir();
      delay(500);
     setBothMotors(0);
      break;

    default:
      long randNumber = random(100);
      if(randNumber > 90 && randNumber < 95) {
        setForwardDir();
        setBothMotors(500);
        delay(500);
        setRightMotor(0);
        delay(300);
        setBothMotors(0);
      }
      break;
  }
}

void stopPilot() {
}

void resumePilot() {
}

 void pingBottomSensor() {
  ultra1.StartRanging();
  bottomTicker.once(0.5, getBottomSensor);
 }

void getBottomSensor() {
 bottomDistance = ultra1.GetDistance();
}

int readFrontSensor() {

  int irDistance = analogRead(IR_SENSOR);
  return irDistance; Serial.println("readFrontSensor = " + irDistance );
}
int readBottomSensor() {
  ultra1.StartRanging();
  delay(500);
  int tmpDist = ultra1.GetDistance();
  return tmpDist;
}
