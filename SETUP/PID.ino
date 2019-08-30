int defaultRPM = 200;
float target = 10.0;

float maxdist = 20.0;

float oneSide_errorR = 0;
float oneSide_errorL = 0;

float bothSide_errorR = 0;
float bothSide_errorL = 0;

void one_sided_pid(int side) { //One-sided test algorithm
  //side == 1 (right) and -1 (left)

  float gainR = 20.0;
  float gainL = 10.0;
  float gainDR = 10.0;
  float gainDL = 10.0;


  //Writing default states
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);

  if (side == 1) {
    float oneSide_errorR_Past = oneSide_errorR;

    float d = getDistance(3);
    oneSide_errorR = d - target;

    float edr = oneSide_errorR_Past - oneSide_errorR;

    //right turning bot, so create correction term
    float correctionR = constrain(defaultRPM - gainR * oneSide_errorR, 120,  255);
    correctionR += gainDR * edr;

    analogWrite(re, correctionR);

    float correctionL = constrain(defaultRPM + gainL * oneSide_errorR, 120, 255);
    correctionL -= gainDL * edr;
    analogWrite(le, correctionL);
  }

  if (side == -1) {
    //declare error term
    float oneSide_errorL_Past = oneSide_errorL;

    float d = getDistance(2);
    oneSide_errorL = d - target;

    float edl = oneSide_errorL_Past - oneSide_errorL;
    //left turning bot, so create correction term
    float correctionL = constrain(defaultRPM + gainL * oneSide_errorR, 120,  255);
    correctionL -= gainDL * edl;
    analogWrite(le, correctionL);

    float correctionR = constrain(defaultRPM - gainR * oneSide_errorR, 120, 255);
    correctionL += gainDL * edl;
    analogWrite(le, correctionL);
    analogWrite(re, correctionR);
  }
  side = 0;
}





//******** this is not edited yet

void pid() { //The algorithm to be actually used
  float gainR = 10.0;
  float gainL = 10.0;
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);

  float errorR = getDistance(3) - target;
  float turnR = constrain(defaultRPM - gainR * errorR, 0 , 255);
  analogWrite(re, turnR);

  float errorL = getDistance(2) - target;
  float turnL = constrain(defaultRPM - gainL * errorL, 0, 255);
  analogWrite(le, turnL);
}





void brake() { //use data from front sensor to avoid collision
  float head_on = 20.0;
  Serial.println(getDistance(1));
  if (getDistance(1) < head_on) {
    digitalWrite(rf, HIGH);
    digitalWrite(rb, HIGH);
    digitalWrite(lf, HIGH);
    digitalWrite(lb, HIGH);
    delay(100); //reduce this as much as possible (depends on how much the bot skids while braking)
    resetEncoderValues();
  }

}













void left_rotation() {
  int rWheels = 5; //distance between wheels is 10 cm (rough assumption, check validity while testing). Change to a float variable if required.
  resetEncoderValues();
  while (measureR() - measureL() < 11) {
    analogWrite(re, 255);
    analogWrite(le, 255);
    digitalWrite(rf, LOW);
    digitalWrite(rb, HIGH);
    digitalWrite(lf, HIGH);
    digitalWrite(lb, LOW);
    Serial.print(measureL());
    Serial.print("  ");
    Serial.println(measureR());
  }
  analogWrite(re, 0);
  analogWrite(le, 0);
  digitalWrite(rf, LOW);
  digitalWrite(rb, LOW);
  digitalWrite(lf, LOW);
  digitalWrite(lb, LOW);
  delay(1000);
}

void right_rotation() {
  int rWheels = 5; //distance between wheels is 10 cm (rough assumption, check validity while testing). Change to a float variable if required.
  resetEncoderValues();
  while (measureL() - measureR() < 11) {
    analogWrite(re, 255);
    analogWrite(le, 255);
    digitalWrite(rf, HIGH);
    digitalWrite(rb, LOW);
    digitalWrite(lf, LOW);
    digitalWrite(lb, HIGH);
    Serial.print(measureL());
    Serial.print("  ");
    Serial.println(measureR());
  }
  analogWrite(re, 0);
  analogWrite(le, 0);
  digitalWrite(rf, LOW);
  digitalWrite(rb, LOW);
  digitalWrite(lf, LOW);
  digitalWrite(lb, LOW);
  delay(1000);
}











void traverse_cell() {
  float cellsize = 25.0;
  resetEncoderValues();
  while (measureR() + measureL() < 2 * cellsize) {
    Serial.println(measureL());
    Serial.print("   ");
    Serial.println(measureR());
    pid();
    /*do
      {
      pid();
      } while ((getDistance(1) <= maxdist) || (getDistance(2) <= maxdist));
      if (getDistance(1) > maxdist)
      {
      one_sided_pid(1);
      }
      if (getDistance(2) > maxdist) {
      one_sided_pid(2);
      }*/
  }
  digitalWrite(re, LOW);
  digitalWrite(le, LOW);

}
