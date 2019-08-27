#include <SharpDistSensor.h>
//Reserve 2 and 3 for encoders (also add 11 and 12)
#define pi 3.14159

#define lf 8
#define lb 7
#define rf 5
#define rb 4
#define re 9
#define le 6

#define FS A2
#define RS A0
#define LS A4

#define encoderRF 18
#define encoderRB 21
#define encoderLF 2
#define encoderLB 3

SharpDistSensor frontSensor(FS, 1);
SharpDistSensor rightSensor(RS, 1);
SharpDistSensor leftSensor(LS, 1);

volatile long int encoder_R = 0;
volatile long int encoder_L = 0;
/*
   MICROMOUSE CODE!
   Composed of the following sections:
   SHARP IR TEST
   MOTOR TEST
   (LEAVE SPACE FOR ENCODERS)
   PID TEST
   LOCOMOTION TEST
   Note that each test is dependent on the test(s) above it. Construct code in this order
*/
void setup() {
  pinMode(lf, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(rb, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(re, OUTPUT);
  pinMode(le, OUTPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(FS, INPUT);


  pinMode(encoderRF, INPUT_PULLUP);
  pinMode(encoderLF, INPUT_PULLUP);


  attachInterrupt(digitalPinToInterrupt(encoderRF), encoderR, RISING);                   //experiment with
  attachInterrupt(digitalPinToInterrupt(encoderLF), encoderL, RISING);


  frontSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  rightSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  leftSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);


  Serial.begin(9600);

  analogWrite(re, 255);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  analogWrite(le, 255);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  delay(1000);
  analogWrite(re, 0);
  digitalWrite(rf, LOW);
  digitalWrite(rb, LOW);
  analogWrite(le, 0);
  digitalWrite(lf, LOW);
  digitalWrite(lb, LOW);
  //********Check Code For IR Sensors*************
  //
  //  int t = millis();
  //
  //  while( millis() - t < 100000)
  //  {
  //    Serial.print(getDistance(2));
  //    Serial.print("  ");
  //    Serial.print(getDistance(1));
  //    Serial.print("  ");
  //    Serial.println(getDistance(3));
  //    delay(10);
  //  }
}
