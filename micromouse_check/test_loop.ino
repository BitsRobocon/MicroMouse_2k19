void loop(){
////encoder test code (manually turn each motor to check polarity and side)
//Serial.print("Right: ");
//Serial.print(measureR());
//Serial.print("    Left:");
//Serial.println(measureL());
//
////Sharp IR test (check distance values, preferably using a scale)
//Serial.print("Front: ");
//Serial.print(getDistance(1));
//Serial.print("    Left:");
//Serial.print(getDistance(2));
//Serial.print("    Right:");
//Serial.println(getDistance(3));
//
////Motor test (vary enable pin values and run both the motors forward and backward)
//motorWrite(1, 255, -1);
//motorWrite(-1, 255, -1);

//90 degree turns (adjust overshoot in function according to the surface)
moveForward();
moveForward();
delay(3000);
  }
