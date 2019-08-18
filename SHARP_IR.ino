//1 = front; 2 = left; 3 = right
float getDistance(int sensor) {
  float d;
  switch (sensor) {
    case 1:
      {
        d = frontSensor.getDist();
      } break;

    case 2:
      {
        d = leftSensor.getDist();
      } break;

    case 3:
      {
        d = rightSensor.getDist();
      } break;
  }
  return d / 10;      //converting mm to cm
}
