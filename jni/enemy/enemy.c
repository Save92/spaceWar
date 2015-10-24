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

void moveEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen)
{
    switch (enemyShip->movementScheme->type) {
        case 1:
            moveEnemyShipVertically(enemyShip,widthScreen,heightScreen);
            break;
        case 2 :moveEnemyShipZigZag(enemyShip,widthScreen,heightScreen);
            break;
            
        default:
            moveEnemyShipVertically(enemyShip,widthScreen,heightScreen);
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

void setVisibilityEnemy(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
    if(enemyShip != NULL)
    {
        
        if(enemyShip->posY < 0 || enemyShip->posY > heightScreen || enemyShip->posX < 0 || enemyShip->posX > widthScreen)
        {
            enemyShip->visible = 0;
        }
    }
}

void moveEnemyShipVertically(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
    enemyShip->posY = enemyShip->posY + (1* enemyShip->speed);
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
    
}


void moveEnemyShipZigZag(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
    verifySideFromVerticalLine(enemyShip);
    enemyShip->posY = enemyShip->posY + (1 * enemyShip->speed);
    if(enemyShip->cntFootStep % 4)
    {
        enemyShip->posX = enemyShip->posX + ( enemyShip->speed * enemyShip->verticalSide);
    }
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
    
}

void verifySideFromVerticalLine(EnemyShip * enemyShip)
{
    
    int distance =  enemyShip->movementScheme->distanceFromVerticalLimit;
    int verticalLine = enemyShip->movementScheme->verticalLimit;
    

    int actualDistance = (int)fabs(enemyShip->posX - verticalLine);
    
    int maxDistance = distance + enemyShip->speed;
    int minDistance = distance - enemyShip->speed;
    
    if( maxDistance > actualDistance && actualDistance > minDistance)
        enemyShip->verticalSide = (-1) * enemyShip->verticalSide;
}




