#include <Servo.h>

const int trig = 10;
const int echo = 9;
long duration;
int distance;

Servo servo_bin;
bool isOpen = false;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo_bin.attach(8);
  servo_bin.write(0); 
}

int getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 20000);
  return duration * 0.034 / 2;
}

void loop() {
  distance = getDistance();
  Serial.println(distance);

  // เปิดเมื่อมีวัตถุในระยะ <= 15 ซม.
  if (distance > 0 && distance <= 15 && !isOpen) {
    for (int pos = 0; pos <= 90; pos++) {
      servo_bin.write(pos);
      delay(10);
    }
    isOpen = true;
  }


  if (isOpen) {
    distance = getDistance();  
    if (distance > 15 || distance == 0) {
      delay(700); // 
      distance = getDistance();
      if (distance > 15 || distance == 0) {
        for (int pos = 90; pos >= 0; pos--) {
          servo_bin.write(pos);
          delay(10);
        }
        isOpen = false;
      }
    }
  }
}
