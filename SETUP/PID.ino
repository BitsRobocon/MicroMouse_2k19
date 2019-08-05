int defaultRPM = 150;
float target = 15.0;
float gainR = 10.0;
float gainL = 10.0;

void one_sided_pid(int side){ //One-sided test algorithm
  //side == 1 (right) and -1 (left)
  
  //Writing default states
  analogWrite(re, defaultRPM);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  analogWrite(le, defaultRPM);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  
  if(side == 1){
  //declare error term
  float d = getDistance(3);
  float errorR = d - target;
  
  //right turning bot, so create correction term
  float correctionR = constrain(defaultRPM - gainR*errorR, 20,  255);
  analogWrite(re, correctionR);

  float correctionL = constrain(defaultRPM + gainL*errorR, 0, 255);
  analogWrite(le, correctionL);
  }

  if(side == -1){
  //declare error term
  float d = getDistance(2);
  float errorL = d - target;
  
  //left turning bot, so create correction term
  float correctionL = constrain(defaultRPM - gainL*errorL, 0,  255);
  analogWrite(le, correctionL);

  float correctionR = constrain(defaultRPM + gainR*errorL, 0, 255);
  analogWrite(re, correctionR);
  }
}

void pid(){ //The algorithm to be actually used
  analogWrite(re, defaultRPM);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  analogWrite(le, defaultRPM);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  
  float errorR = getDistance(3) - target;
  float turnR = constrain(defaultRPM - gainR*errorR, 100 , 255);
  analogWrite(re, turnR);

  float errorL = getDistance(2) - target;
  float turnL = constrain(defaultRPM - gainL*errorL, 100, 255);
  analogWrite(le, turnL);
}  

void brake(){ //use data from front sensor to avoid collision
  float head_on = 20.0;
  Serial.println(getDistance(1));
  if(getDistance(1) < head_on){
    digitalWrite(rf, LOW);
    digitalWrite(rb, HIGH);
    digitalWrite(lf, LOW);
    digitalWrite(lb, HIGH);
    delay(100);
  }
 }

/*void left_rotation(){
 delay(100);
 digitalWrite(re, HIGH);
 digitalWrite(le, HIGH);
 digitalWrite(rf, HIGH);
 digitalWrite(rb, LOW);
 digitalWrite(lf, LOW);
 digitalWrite(lb, HIGH);
 delay(300);
 digitalWrite(re, LOW);
 digitalWrite(le, LOW);
 delay(1000);
 }
*/