//
//  enemy.c
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//
#include "../SDL/src/core/android/SDL_android.h"

#include <android/log.h>
#include <jni.h>
#include <stdlib.h>
#include <math.h>

#include "enemy.h"
#include "littleEnemyShip.h"


void drawEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip)
{
    switch (enemyShip->type) {
        case 0:
            drawLittleEnemyShip(renderer , enemyShip);
            break;
            
        default:
            break;
    }
}

void moveEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen, double coef)
{
    switch (enemyShip->type) {
        case 0:
            moveLittleEnemyShip(enemyShip,widthScreen,heightScreen);
            break;
            
        default:
            break;
    }
}




void freeEnemyShip(EnemyShip * enemyShip)
{
    free(enemyShip->rectangle);
    free(enemyShip->movementScheme);
    free(enemyShip->nextEnemyShip);
    free(enemyShip);
   
}

EnemyShip * initialisationEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement)
{

    EnemyShip * enemyShip;
    switch(typeShip)
    {
        case 0: enemyShip   = initialisationLittleEnemyShip( width, height, typeStart, side, distance, verticalLine, typeShip, typeMovement);
            break;
            
        default :
            break;
            
    }
    return enemyShip;
}

Shoot * EnemyShipShoot(EnemyShip * enemyShip)
{
    switch (enemyShip->type) {
        case 0: LittleEnemyShipShoot(enemyShip);
            break;
            
        default:
            break;
            
    }
}
    
int canShoot(EnemyShip * enemyShip)
{
    int canShoot;
    switch (enemyShip->type) {
        case 0: canShoot = LittleEnemyShipCanShoot(enemyShip);
            break;
            
        default:
            break;
    }
    
    return canShoot;
    
}



