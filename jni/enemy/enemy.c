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
#include "../general/constant.h"

# define CHGM_DIRECTION  2

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
        case 0:
            moveEnemyShipVertically(enemyShip,widthScreen,heightScreen);
            break;
        case 1 :moveEnemyShipZigZag(enemyShip,widthScreen,heightScreen);
            break;
            
        case 2 : moveEnemyShipZigZag(enemyShip,widthScreen,heightScreen);
            break;

            
        default:
            moveEnemyShipZigZag(enemyShip,widthScreen,heightScreen);
            break;
    }
}




void freeEnemyShip(EnemyShip * enemyShip)
{
    free(enemyShip->rectangle);
    free(enemyShip->movementScheme);
    free(enemyShip);
   
}

EnemyShip * initialisationEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement)
{
   // __android_log_print(ANDROID_LOG_DEBUG, "EnemyShip",   "initialisationEnemyShip"  );

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
    if(enemyShip != NULL )
    {
        
        if((enemyShip->posY+enemyShip->height) < 0 || enemyShip->posY > heightScreen || (enemyShip->posX + enemyShip->width) < 0 || enemyShip->posX > widthScreen)
        {
            enemyShip->visible = INVISIBLE;
        }
    }
}

void moveEnemyShipVertically(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
  //  __android_log_print(ANDROID_LOG_DEBUG, "Enemy", "move vertically");
    enemyShip->posY = enemyShip->posY + (1* enemyShip->speed);
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
     enemyShip->cntFootStep++;
    
}


void moveEnemyShipZigZag(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
 //    __android_log_print(ANDROID_LOG_DEBUG, "Enemy", "move zig-zag");
    verifySideFromVerticalLine(enemyShip);
    enemyShip->posY = enemyShip->posY + (1 * enemyShip->speed);
    if(enemyShip->cntFootStep % CHGM_DIRECTION == 0)
    {
        enemyShip->posX = enemyShip->posX + ( enemyShip->speed * enemyShip->verticalSide);
    }
    enemyShip->cntFootStep++;
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
 //   __android_log_print(ANDROID_LOG_DEBUG, "Enemy", "enemyShip Positon X : %d , Position Y : %d",enemyShip->posX,enemyShip->posY);
    
}

void verifySideFromVerticalLine(EnemyShip * enemyShip)
{
    
    int distance =  enemyShip->movementScheme->distanceFromVerticalLimit;
    int verticalLine = enemyShip->movementScheme->verticalLimit;
    int actualDistance = 0;
    actualDistance = (int)fabs(enemyShip->posX - verticalLine);
    
    int maxDistance = verticalLine + distance;
    int minDistance =verticalLine - distance;
  //  __android_log_print(ANDROID_LOG_DEBUG, "sideFromVerticalLine", "move zig-zag %d %d %d %d",actualDistance,distance,enemyShip->verticalSide,verticalLine);
    if(enemyShip->posX < minDistance)
    {
        enemyShip->verticalSide = 1;
    }
    
    if(enemyShip->posX >maxDistance)
    {
        enemyShip->verticalSide = -1;
    }
  
}

int enemyShipIsAlive(EnemyShip * enemyShip)
{
    if(enemyShip->life == 0)
        return TRUE;
    else
        return FALSE;
}




