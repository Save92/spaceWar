//
//  littleEnemyShip.h
//  
//
//
//

#ifndef littleEnemyShip_h
#define littleEnemyShip_h

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "./enemy.h"
#include "../general/drawer.h"


void drawLittleEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip);

EnemyShip * initialisationLittleEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel);
int  LittleEnemyShipCanShoot(EnemyShip * enemyShip);




#endif /* littleEnemyShip_h */
