//
//  littleBomberEnemy.h
//  

#ifndef littleBomberEnemy
#define littleBomberEnemy

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "./enemy.h"
#include "../general/drawer.h"


void drawLittleBomberEnemy(SDL_Renderer* renderer , EnemyShip * enemyShip);
EnemyShip * initialisationLittleBomberEnemy(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel);





#endif /* littleBomberEnemy_h */
