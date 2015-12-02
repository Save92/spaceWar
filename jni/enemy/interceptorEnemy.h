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
EnemyShip * initialisationInterceptorEnemy(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel);





#endif /* interceptorEnemy_h */
