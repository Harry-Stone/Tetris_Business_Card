//#include "ledMatix.hpp"
#include "music.hpp"
#include "game.hpp"
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
}

void pulseClock(){
  digitalWrite(16,HIGH);
  delayMicroseconds(10);
  digitalWrite(16,LOW);
}

void loop() {
  Serial.print("Loop: ");
  Serial.print(comx);
  Serial.print("   ");
  Serial.println(comy);
  testPositionDown(tet6,comx,comy);
  commitToScreenBuffer();
  pushToScreen();
  delay(500);
}