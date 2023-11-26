#include<Arduino.h>

const int pinHall_1 = 2;  
const int pinHall_2 = 3;  
const int pinHall_3 = 21;  

const int power_hall = 8; // to power sensors and reset them 

volatile unsigned long time_1 = 0;
volatile unsigned long time_2 = 0;
volatile unsigned long time_3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(power_hall, OUTPUT);

  //reset sensor hall, because that sensor has hysteresis
  digitalWrite(power_hall, LOW);
  delay(250);
  digitalWrite(power_hall, HIGH);


  pinMode(pinHall_1, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinHall_1), detection1, RISING);

  pinMode(pinHall_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinHall_2), detection2, RISING);

  pinMode(pinHall_3, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinHall_3), detection3, RISING);
}

void loop() {
 
  if (time_1 > 0 && time_2 > 0 && time_3 > 0) {

    detachInterrupt(detection1);
    detachInterrupt(detection2);
    detachInterrupt(detection3);

    unsigned long interval1_2 = time_2 - time_1;
    unsigned long interval2_3 = time_3 - time_2;

    Serial.print("time between sensor 1 and sensor 2: ");
    Serial.print(interval1_2);
    Serial.println(" ms");

    Serial.print("time between sensor 2 and sensor 3: ");
    Serial.print(interval2_3);
    Serial.println(" ms");

    // Reset the timers
    time_1 = 0;
    time_2 = 0;
    time_3 = 0;

    //reset sensor hall, because that sensor has hysteresis
    digitalWrite(power_hall, LOW);
    delay(250);
    digitalWrite(power_hall, HIGH);

    attachInterrupt(digitalPinToInterrupt(pinHall_1), detection1, RISING);
    attachInterrupt(digitalPinToInterrupt(pinHall_2), detection2, RISING);
    attachInterrupt(digitalPinToInterrupt(pinHall_3), detection3, RISING);
  }


}

void detection1() {
  time_1 = millis();
}

void detection2() {
  time_2 = millis();
}

void detection3() {
  time_3 = millis();
}

