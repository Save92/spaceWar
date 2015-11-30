//
//  bigBomberEnemy.h
//  

#ifndef bigBomberEnemy
#define bigBomberEnemy

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "./enemy.h"
#include "../general/drawer.h"


void drawBigBomberEnemy(SDL_Renderer* renderer , EnemyShip * enemyShip);
void moveBigBomberEnemy(EnemyShip * enemyShip,int widthScreen, int heightScreen);
EnemyShip * initialisationBigBomberEnemy(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel);
int  BigBomberEnemyCanShoot(EnemyShip * enemyShip);




#endif /* bigBomberEnemy_h */
