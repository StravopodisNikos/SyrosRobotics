// This code communicates Ultrasonic Sensor with One DC motor
// If distance is lessORequal to 20 cm then DC motor acceleratea at 100%
// If distance larger than 20 cm DC motor works at 50%
// -Uses delay(ms); MUST BE OPTIMIZED
// -----------------------------------------------------
#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).
#define MIN_DISTANCE 20 // Miimum distance from obstacle

#define motorfwd 3 // Arduino pins for motor control
#define motorback 5

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  // pingTimer = millis(); // Start now.
  pinMode(motorfwd, OUTPUT);
  pinMode(motorback, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  //delay(500);  // Wait 500ms between pings (about 2 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int dist = DistSonar();
  Serial.print("Distance:");
  Serial.print(dist);
  Serial.println("cm");
  Serial.print("\n");
  if (dist<MIN_DISTANCE){
      //move dc motor at full speed
      Serial.println("Drives motor for 1s");
      analogWrite(motorfwd,255);
      analogWrite(motorback,0);
      delay(100);
  }
  else {
      analogWrite(motorfwd,0);
      analogWrite(motorback,0);
  }
  
}

unsigned int DistSonar() {
  unsigned int cm = sonar.ping_cm();
  return cm;
}
