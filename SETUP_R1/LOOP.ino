void loop() {
  Serial.print(getDistance(2));
  Serial.print("   ");
  Serial.println(getDistance(3));
  while (getDistance(2) < 25)
  {
    pid();
  }
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);
  analogWrite(re, 100);
  analogWrite(le, 100);
  delay(250);
  digitalWrite(rf, LOW);
  digitalWrite(rb, LOW);
  digitalWrite(lf, LOW);
  digitalWrite(lb, LOW);
  analogWrite(re, 0);
  analogWrite(le, 0);
  delay(1000000);
}
