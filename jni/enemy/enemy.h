//
//  enemy.h
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#ifndef enemy_h
#define enemy_h

#include <stdio.h>
#include "./movementScheme.h"
#include "SDL.h"
#include "../general/drawer.h"
typedef struct EnemyShip EnemyShip;
struct EnemyShip
{
    int posX;
    int posY;
    float speed;
    int life;
    int color[4];
    SDL_Rect *rectangle;
    int shotLevel;
    int typeShip;
    int bonus;
    int cntFootStep;
    MovementScheme * movementScheme;
    int type;
    int typeMovement;
    int repeatMovement;
    int visible;
    int frequencyOfShoot;
    int verticalSide;
    int width;
    int height;
    int changeDirection;
    Sprite enemySprite;
    
    EnemyShip * nextEnemyShip;
};




void drawEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip);
int moveEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen);
void freeEnemyShip(EnemyShip * enemyShip);
EnemyShip * initialisationEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel);
int canShoot(EnemyShip * enemyShip);
void setVisibilityEnemy(EnemyShip * enemyShip,int widthScreen,int heightScreen);
void moveEnemyShipVertically(EnemyShip * enemyShip,int widthScreen,int heightScreen);
void moveEnemyShipZigZag(EnemyShip * enemyShip,int widthScreen,int heightScreen);
void verifySideFromVerticalLine(EnemyShip * enemyShip);
int enemyShipIsAlive(EnemyShip * enemyShip);
void setEnemyToInvisible(EnemyShip * enemy);






#endif /* enemy_h */
