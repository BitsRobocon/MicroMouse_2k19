//1 = front; 2 = left; 3 = right
float getDistance(int sensor) {
  float d;
  switch (sensor) {
    case 1:
      d = frontSensor.getDist();
      break;

    case 2:
      d = leftSensor.getDist();
      break;

    case 3:
      d =rightSensor.getDist();
      break;
  }
  return d / 10.0;      //converting mm to cm
}

void motorWrite(int side, int anal, int dir){ //by default, the function needs -1 or +1 as the side and it will run at default RPM in the forward direction
  if(side == 1){ //Right
    if(dir == 1){ //Forward
      analogWrite(re, anal);
      digitalWrite(rf, HIGH);
      digitalWrite(rb, LOW);
      }
    if(dir == -1){ //Backward
      analogWrite(re, anal);
      digitalWrite(rb, HIGH);
      digitalWrite(rf, LOW);
      }
    }
  if(side == -1){ //Left
      if(dir == 1){ //Forward
    analogWrite(le, anal);
    digitalWrite(lf, HIGH);
    digitalWrite(lb, LOW);
    }
  if(dir == -1){ //Backward
    analogWrite(le, anal);
    digitalWrite(lb, HIGH);
    digitalWrite(lf, LOW);
      }
    }
  }
