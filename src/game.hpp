#include <Arduino.h>
#include "ledMatrix.hpp"
u_int8_t score = 0;
int comx = 3;
int comy = 0;

u_int16_t gameState[13] = 
{
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b1111111111111111
};
u_int16_t tet1[4] = 
{
    0b0000000000000001,
    0b0000000000000001,
    0b0000000000000001,
    0b0000000000000001,
};
u_int16_t tet2[4] = 
{
    0b0000000000000000,
    0b0000000000000001,
    0b0000000000000001,
    0b0000000000000011,
};
u_int16_t tet3[4] = 
{
    0b0000000000000000,
    0b0000000000000010,
    0b0000000000000010,
    0b0000000000000011,
};
u_int16_t tet4[4] = 
{
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000110,
    0b0000000000000011,
};
u_int16_t tet5[4] = 
{
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000011,
    0b0000000000000110,
};
u_int16_t tet6[4] = 
{
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000011,
    0b0000000000000011,
};

void writeGameStateToCanvas(){
    Serial.println("Pushing game state to canvas");
    for (int i = 0; i < 13; i++)
    {
        canvas[i]=gameState[i];
    }
}
void addTileToCanvas(u_int16_t tet[4],int x ,int y){ //not game state modifying, purely cosmetic, no checks, will do what's asked
    Serial.println("Adding tile to canvas");
    int t = 3;
    int xtp = x;
    int ytp = y;
    while (ytp>=0&&t>=0){
        Serial.print("Adding tile to canvas line: ");
        Serial.println(ytp);
        canvas[ytp] = canvas[ytp]|(tet[t]<<xtp);
        ytp--;
        t--;
    }
}

void testPositionDown(u_int16_t tet[4], int posx, int posy){
    Serial.print("TPOSD: ");
    Serial.print(posx);
    Serial.print("   ");
    Serial.println(posy);
    Serial.println(gameState[posy+1]);
    Serial.println(tet[3]<<posx);
    Serial.println(gameState[posy+1]&(tet[3]<<posx)!=0);
    if ((gameState[posy+1]&(tet[3]<<posx))==0){ //can move down 
        Serial.println("Moving down");
        comy+=1;//Move down
    } else { //can't move down
        if (posy <= 4) { // over the top <- take rotation into account
            Serial.println("Game Over");
            //GAME OVER
            //PLAY SOUND
        } else { //place the block
            Serial.println("Placing block");
            comy = 0;
            comx = 4; //reset command positions to spawn
            gameState[posy-3] = gameState[posy-3] | (tet[0]<<posx);
            gameState[posy-2] = gameState[posy-2] | (tet[1]<<posx);
            gameState[posy-1] = gameState[posy-1] | (tet[2]<<posx);
            gameState[posy] = gameState[posy] | (tet[3]<<posx);
            for (int i = 0; i < 11; i++){//check for clear lines
                if (gameState[i]==0b0000001111111111){ // full row
                    Serial.print("Found row: ");
                    Serial.print(i);
                    Serial.print(" As full");
                    for (int j = i; j > 0; i--){
                        gameState[j] = gameState[j-1]; //shift all rows above down one
                    }
                    gameState[0] = 0; //clear top row; avoid IOR core dump
                }
            }  
        }  
    }
    writeGameStateToCanvas();
    addTileToCanvas(tet, posx, posy);
    Serial.println("Fin down Check");
}