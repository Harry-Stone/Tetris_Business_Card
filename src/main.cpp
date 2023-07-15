//#include "ledMatix.hpp"
#include "music.hpp"
#include "game.hpp"
#include <Arduino.h>
void setup() {
  pinMode(0, INPUT);
  randomSeed(analogRead(0));

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
  switch (curTet)
  {
  case 1:
    testPositionDown(tet1,comx,comy);
    break;
  case 2:
    testPositionDown(tet2,comx,comy);
    break;
  case 3:
    testPositionDown(tet3,comx,comy);
    break;
  case 4:
    testPositionDown(tet4,comx,comy);
    break;
  case 5:
    testPositionDown(tet5,comx,comy);
    break;
  default:
    testPositionDown(tet6,comx,comy);
    break;
  }
  //testPositionDown(tet2,comx,comy);
  commitToScreenBuffer();
  pushToScreen();
  delay(300);
}