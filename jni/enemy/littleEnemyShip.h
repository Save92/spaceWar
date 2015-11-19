//
//  littleEnemyShip.h
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#ifndef littleEnemyShip_h
#define littleEnemyShip_h

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "./enemy.h"



void drawLittleEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip);
void moveLittleEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen);
EnemyShip * initialisationLittleEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement);
int  LittleEnemyShipCanShoot(EnemyShip * enemyShip);
void initialisationTypeStart(int width,int height,EnemyShip * enemyShip,int typeStart,int side,int defaultGap);




#endif /* littleEnemyShip_h */
