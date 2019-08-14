#include <PinChangeInterrupt.h>
#include <SharpDistSensor.h>
//Reserve 2 and 3 for encoders (also add 11 and 12)
#define pi 3.14159
#define lf 7
#define lb 8
#define rf 5
#define rb 4
#define re 9
#define le 6
#define FS A0
#define RS A1
#define LS A2
#define encoderRF 2
#define encoderRB 3
#define encoderLF 12
#define encoderLB 11
SharpDistSensor frontSensor(FS, 1);
SharpDistSensor rightSensor(RS, 1);
SharpDistSensor leftSensor(LS, 1);
volatile unsigned long int encoder_R = 0;
volatile unsigned long int encoder_L = 0;

/*
 * MICROMOUSE CODE!
 * Composed of the following sections: 
 * SHARP IR TEST
 * MOTOR TEST
 * (LEAVE SPACE FOR ENCODERS)
 * PID TEST
 * LOCOMOTION TEST
 * Note that each test is dependent on the test(s) above it. Construct code in this order
 */
void setup(){
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
  attachInterrupt(digitalPinToInterrupt(encoderRF), encoderR, CHANGE);                   //experiment with
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(encoderLF), encoderL, CHANGE);  //RISING, FALLING and CHANGE parameters.
  frontSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  rightSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  leftSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  Serial.begin(112500);
  }
