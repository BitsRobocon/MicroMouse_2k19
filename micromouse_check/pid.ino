int defaultRPM = 100;
float target = 7.3;

float error_both = 0;
float error_both_past = 0;

float maxdist = 25.0;

float oneSide_errorR = 0;
float oneSide_errorL = 0;

float bothSide_errorR = 0;
float bothSide_errorL = 0;

//******** this is not edited yet

void pid() { //The algorithm to be actually used
  float gainR = 4.0;
  float gainL = 20.0;
  float gainDR = 0.0;
  float gainDL = 0.0;

  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);

  error_both = getDistance(3) - getDistance(2);
  float dt = 0.01;
  float ed = (error_both - error_both_past)/dt;

  //  Serial.print("error : ");
  float corr = gainR*error_both + gainDR*ed;

  float turnR = constrain(defaultRPM - corr/2, 80, 255);
  analogWrite(re, turnR);
  float turnL = constrain(defaultRPM + corr/2, 80, 255);
  analogWrite(le, turnL);
  error_both_past = error_both;
}





void brake() { //use data from front sensor to avoid collision
  float head_on = 10.0;
  float overshoot = 2.0;
  Serial.println(getDistance(1));
  if (getDistance(1) < head_on + overshoot) {
    digitalWrite(rf, LOW);
    digitalWrite(rb, LOW);
    digitalWrite(lf, LOW);
    digitalWrite(lb, LOW);
    delay(100); //reduce this as much as possible (depends on how much the bot skids while braking)
    resetEncoderValues();
    /*while(getDistance(1) < head_on){
     *pid(); 
     *defaultRPM--;
     }*/
  }

}













void left_rotation() {
  int turnSpeed = 200;
  int rWheels = 5.0; //distance between wheels is 10 cm (rough assumption, check validity while testing). Change to a float variable if required.
  resetEncoderValues();
  while (measureR() - measureL() < 10.0) {
    analogWrite(re, turnSpeed);
    analogWrite(le, turnSpeed+20);    //left motor seems weak
    digitalWrite(lf, LOW);
    digitalWrite(lb, HIGH);
    digitalWrite(rf, HIGH);
    digitalWrite(rb, LOW);
    Serial.print(measureL());
    Serial.print("  ");
    Serial.println(measureR());
  }
  stopMotors();
  delay(1000);
}

void right_rotation() {
  int turnSpeed = 200;
  int rWheels = 5.0; //distance between wheels is 10 cm (rough assumption, check validity while testing). Change to a float variable if required.
  resetEncoderValues();
  while (measureL() - measureR() < 10.0) {
    analogWrite(re, turnSpeed);
    analogWrite(le, turnSpeed+20);    //left motor seems weak
    digitalWrite(lf, HIGH);
    digitalWrite(lb, LOW);
    digitalWrite(rf, LOW);
    digitalWrite(rb, HIGH);
    Serial.print(measureL());
    Serial.print("  ");
    Serial.println(measureR());
  }
stopMotors();
  delay(1000);
}










int overshoot = 15.0;
void traverse_cell() {
  float cellsize = 25.0;
  resetEncoderValues();
  while (measureR() + measureL() < 2 * (cellsize - overshoot)) {
    pid();
    Serial.print(measureL());
    Serial.print(" ");
    Serial.println(measureR());
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
stopMotors();
}

void stopMotors() {
  digitalWrite(rf, LOW);
  digitalWrite(rb, LOW);
  digitalWrite(lf, LOW);
  digitalWrite(lb, LOW);
  analogWrite(re, 0);
  analogWrite(le, 0);
}
/*CURRENTLY USING THIS ALGORITHM
 * 1. CHECK IF WALL IS PRESENT
 * WHATEVER SIDE IT'S PRESENT, FOLLOW THAT (FOR 1 CELL, SO IT SHOULD BE FINE)
 */
void one_sided_pid(int side) { //One-sided test algorithm
  //side == 1 (right) and -1 (left)

  float gainR = 10.0;
  float gainL = 10.0;
  float gainDR = 2.0;
  float gainDL = 2.0;

  if (side == 1) {
    float oneSide_errorR_Past = oneSide_errorR;

    float d = getDistance(3);
    oneSide_errorR = d - target;

    float edr = oneSide_errorR_Past - oneSide_errorR;

    //right turning bot, so create correction term
    float correctionR = constrain(defaultRPM - gainR * oneSide_errorR, 20, 255);
    correctionR += gainDR * edr;
    analogWrite(re, correctionR);

    float correctionL = constrain(defaultRPM + gainL * oneSide_errorR, 20, 255);
    correctionL -= gainDL * edr;
    analogWrite(le, correctionL);
  }

  if (side == -1) {
    float oneSide_errorL_Past = oneSide_errorL;

    float d = getDistance(2);
    oneSide_errorL = d - target;

    float edl = oneSide_errorL_Past - oneSide_errorL;
    //left turning bot, so create correction term
    float correctionL = constrain(defaultRPM - gainL * oneSide_errorL, 20,  255);
    correctionL += gainDL * edl;
    analogWrite(le, correctionL);

    float correctionR = constrain(defaultRPM + gainR * oneSide_errorL, 20, 255);
    correctionR -= gainDR * edl;
    analogWrite(re, correctionR);
  }
  Serial.print("Right error: ");
  Serial.print(oneSide_errorR);
  Serial.print("    Left error");
  Serial.println(oneSide_errorL);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  side = 0;
}

void moveForward(/*int times*/){
  float cellSize = 25.0;
  if(isRightWall() == 1)
  while(measureR() + measureL() < 2*cellSize)
    one_sided_pid(1);
    
  if(isLeftWall == 1)
  while(measureR() + measureL() < 2*cellSize)
    one_sided_pid(-1);
//  else{
//    while(measureR() + measureL() < 2*cellSize){
//    motorWrite(1, 100, 1);
//    motorWrite(-1, 100, 1);}}
  Serial.print("Right ");
  Serial.print(measureR());
  Serial.print("    Left:");
  Serial.println(measureL());
  stopMotors();
  resetEncoderValues();
  }

float wallDist = 16.0;


int isLeftWall(){
  if(getDistance(2) < wallDist)
    return 1;
  else
    return 0;
  } 

int isRightWall(){
  if(getDistance(3) < wallDist)
    return 1;
  else
    return 0;
  }

int isFrontWall(){
  wallDist = 10.0;
  if(getDistance(1) < wallDist)
    return 1;
  else
    return 0;
  }
 
