#define ROWPREAMBLE 0b000000

#include <Arduino.h>

u_int8_t shiftBuffer[15] = {
0b11111111,
0b00100010,
0b10101010,
0b00100010,
0b00100010,
0b00100010,
0b00100010,
0b11111111,
0b00100010,
0b01000100,
0b01000100,
0b01000100,
0b01000100,
0b01000100,
0b01000100
};

u_int16_t canvas[12] = 
{
    0b0000000011111100,
    0b0000001111111111,
    0b0000000000000000,
    0b0000000001001000,
    0b0000000001001000,
    0b0000000001001000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000011111100,
    0b0000001000000001,
    0b0000001100000011,
    0b0000001111001111
};

void commitToScreenBuffer(){
    shiftBuffer[0]=canvas[0]>>2;
    shiftBuffer[1]=canvas[0]<<6 | (canvas[1]>>4);
    shiftBuffer[2]=canvas[1]<<4 | (canvas[2]>>6);
    shiftBuffer[3]=canvas[2]<<2 | (canvas[3]>>8);
    shiftBuffer[4]=canvas[3];
    shiftBuffer[5]=canvas[4]>>2;
    shiftBuffer[6]=canvas[4]<<6 | (canvas[5]>>4);
    shiftBuffer[7]=canvas[5]<<4 | (canvas[6]>>6);
    shiftBuffer[8]=canvas[6]<<2 | (canvas[7]>>8);
    shiftBuffer[9]=canvas[7];
    shiftBuffer[10]=canvas[8]>>2;
    shiftBuffer[11]=canvas[8]<<6 | (canvas[9]>>4);
    shiftBuffer[12]=canvas[9]<<4 | (canvas[10]>>6);
    shiftBuffer[13]=canvas[10]<<2 | (canvas[11]>>8);
    shiftBuffer[14]=canvas[11];
}


void pulseClock1(){
    Serial.println("CLK1");
    digitalWrite(16,HIGH);
    delayMicroseconds(5);
    digitalWrite(16,LOW);
}

void pulseClock2(){
    Serial.println("CLK2");
    digitalWrite(17,HIGH);
    delayMicroseconds(5);
    digitalWrite(17,LOW);
}

void pulseClock3(){
    Serial.println("CLK3");
    digitalWrite(18,HIGH);
    delayMicroseconds(5);
    digitalWrite(18,LOW);
}

void setupScreen(){
    pinMode(32, OUTPUT); //ledEN
    
    pinMode(16, OUTPUT); //CLK1
    pinMode(17, OUTPUT); //CLK2
    pinMode(18, OUTPUT); //CLK3
    
    pinMode(21, OUTPUT); //data1
    pinMode(22, OUTPUT); //data2
    pinMode(23, OUTPUT); //data3
    pinMode(25, OUTPUT); //data4
    pinMode(26, OUTPUT); //data5

    //set clocks LOW
    digitalWrite(16,LOW);
    digitalWrite(17,LOW);
    digitalWrite(18,LOW);


    //set data lines low
    digitalWrite(21,LOW);
    digitalWrite(22,LOW);
    digitalWrite(23,LOW);
    digitalWrite(25,LOW);
    digitalWrite(26,LOW);

    //enable the system
    digitalWrite(32, HIGH);

    //purge any garbage from shift registers
    for(int i = 0; i <= 10; i++){
        pulseClock1();
        pulseClock2();
        pulseClock3();
    }
}

void pushToScreen(){
    for(int i = 0; i < 8; i++){
        digitalWrite(21,shiftBuffer[0]&(1<<i));
        digitalWrite(22,shiftBuffer[1]&(1<<i));
        digitalWrite(23,shiftBuffer[3]&(1<<i));
        digitalWrite(25,shiftBuffer[2]&(1<<i));
        digitalWrite(26,shiftBuffer[4]&(1<<i));
        pulseClock1();

        digitalWrite(21,shiftBuffer[6]&(1<<i));
        digitalWrite(22,shiftBuffer[5]&(1<<i));
        digitalWrite(23,shiftBuffer[8]&(1<<i));
        digitalWrite(25,shiftBuffer[7]&(1<<i));
        digitalWrite(26,shiftBuffer[9]&(1<<i));
        pulseClock2();

        digitalWrite(21,shiftBuffer[11]&(1<<i));
        digitalWrite(22,shiftBuffer[10]&(1<<i));
        digitalWrite(23,shiftBuffer[13]&(1<<i));
        digitalWrite(25,shiftBuffer[12]&(1<<i));
        digitalWrite(26,shiftBuffer[14]&(1<<i));
        pulseClock3();
    }
}