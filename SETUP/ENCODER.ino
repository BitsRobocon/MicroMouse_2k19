void encoderR(){
  if(digitalRead(encoderRB) == HIGH)
    encoder_R++;
  if(digitalRead(encoderRB) == LOW)
    encoder_R--;
  }

void encoderL(){
  if(digitalRead(encoderLB) == HIGH)
    encoder_L--;
  if(digitalRead(encoderLB) == LOW)
    encoder_L++;
  }

float measureR(){
  //3 pulses per revolution (from datasheet of motor)
  //6 encoder increment mean one revolution
  float rev = encoder_R/205;
  //one revolution = 2*pi*r distance travelled, here r = 1.5 cm (approx.)
  float distR = rev*3*pi;
  return distR;
  }

float measureL(){
  //refer to the previous function
  float rev = encoder_L/205;
  float distL = rev*3*pi;
  return distL;  
  }

void resetEncoderValues(){
  encoder_R = 0;
  encoder_L = 0;
  }
