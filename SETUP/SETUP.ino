#include <MedianFilter.h>
#include <SharpDistSensor.h>

#define lf 2
#define lb 3
#define rf 5
#define rb 4
#define re 9
#define le 6
#define FS A0
#define RS A1
#define LS A2
SharpDistSensor frontSensor(FS, 1);
SharpDistSensor rightSensor(RS, 1);
SharpDistSensor leftSensor(LS, 1);

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
  frontSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  rightSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  leftSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  Serial.begin(9600);
  }
