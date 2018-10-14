
void distanceSettings() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void distance() {


  long duration, distance;

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance >= 200 || distance <= 0)
    distance = 0;

}
