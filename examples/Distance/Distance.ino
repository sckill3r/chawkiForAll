#include <chawkiForAll.h>
#define TRIG_PIN 16
#define ECHO_PIN 17

chawkiForAll all;

void setup() {
  Serial.begin(9600);
  all.initDistance(TRIG_PIN, ECHO_PIN);
}

void loop() {
  float distance = all.measureDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}
