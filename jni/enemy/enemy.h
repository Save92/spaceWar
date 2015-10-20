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
#include "../general/shoot.h"
#include "./movementScheme.h"
#include "SDL.h"
typedef struct EnemyShip EnemyShip;
struct EnemyShip
{
    int posX;
    int posY;
    int speed;
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
    int frequencyOfShoot;
    int verticalSide;
    EnemyShip * nextEnemyShip;
};


void drawEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip);
void moveEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen, double coef);
void freeEnemyShip(EnemyShip * enemyShip);
Shoot * EnemyShipShoot(EnemyShip * enemyShip);
EnemyShip * initialisationEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement);
int canShoot(EnemyShip * enemyShip);





#endif /* enemy_h */
