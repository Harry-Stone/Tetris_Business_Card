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
}

void pulseClock(){
  digitalWrite(16,HIGH);
  delayMicroseconds(10);
  digitalWrite(16,LOW);
}

void loop() {
  u_int16_t hold = canvas[12];
  for(int j = 11; j>0; j--){
    canvas[j] = canvas[j-1];
  }
  canvas[0]=hold;
  //canvas[7] = 0b0000000000000000,
  //canvas[8] = 0b0000000011111100,
  //canvas[9] = 0b0000001000000001,
  commitToScreenBuffer();
  pushToScreen();
  delay(500);
  /*
  canvas[7] = 0b0000000001111000,
  canvas[8] = 0b0000000010000100,
  canvas[9] = 0b0000001001111001,
  commitToScreenBuffer();
  pushToScreen();
  delay(500);*/
}