//#include "ledMatix.hpp"
#include "music.hpp"
#include "ledMatrix.hpp"
#include <Arduino.h>
void setup() {

  Serial.begin(115200);
  Serial.println("Starting test");
  /*
  pinMode(32, OUTPUT); //ledEN
  pinMode(21, OUTPUT); //data
  pinMode(16, OUTPUT); //CLK

  pinMode(19,OUTPUT); //buzzer

  digitalWrite(21,LOW);
  digitalWrite(16,LOW);

  digitalWrite(32, HIGH);
  
  ledcSetup(1, 5000, 8);
  ledcAttachPin(19, 1);
  ledcWrite(1, 127);

  Serial.begin(115200);
  Serial.println("Starting test");

  playTune();
  */
  setupScreen();
  commitToScreenBuffer();
  pushToScreen();

  delay(100000);
}

void pulseClock(){
  digitalWrite(16,HIGH);
  delay(1);
  digitalWrite(16,LOW);
}

void loop() {
  Serial.println("pattern1");
  delay(500);
  digitalWrite(21,HIGH);
  pulseClock();
  pulseClock();
  pulseClock();
  pulseClock();
  digitalWrite(21,LOW);
  pulseClock();
  pulseClock();
  pulseClock();
  pulseClock();
  Serial.println("pattern2");
  delay(500);
  digitalWrite(21,LOW);
  pulseClock();
  pulseClock();
  pulseClock();
  pulseClock();
  digitalWrite(21,HIGH);
  pulseClock();
  pulseClock();
  pulseClock();
  pulseClock();
}