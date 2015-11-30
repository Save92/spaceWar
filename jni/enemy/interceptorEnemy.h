//
//  interceptorEnemy.h
//  

#ifndef interceptorEnemy
#define interceptorEnemy

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "./enemy.h"
#include "../general/drawer.h"


void drawInterceptorEnemy(SDL_Renderer* renderer , EnemyShip * enemyShip);
void moveInterceptorEnemy(EnemyShip * enemyShip,int widthScreen, int heightScreen);
EnemyShip * initialisationInterceptorEnemy(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel);
int  InterceptorEnemyCanShoot(EnemyShip * enemyShip);




#endif /* interceptorEnemy_h */
