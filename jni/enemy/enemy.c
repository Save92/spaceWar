//
//  enemy.c
//
//
//
//
#include "../SDL/src/core/android/SDL_android.h"

#include <android/log.h>
#include <jni.h>
#include <stdlib.h>
#include <math.h>
#include "movementConstant.h"
#include "enemy.h"
#include "littleEnemyShip.h"
#include "interceptorEnemy.h"
#include "littleBomberEnemy.h"
#include "bigBomberEnemy.h"
#include "../general/constant.h"
#include "../general/CustomLog.h"

# define CHGM_DIRECTION  2

void drawEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip)
{
    customLog(1 , "ENEMY" ,  __func__);
    switch (enemyShip->type) {
        case 0:
            drawLittleEnemyShip(renderer , enemyShip);
            break;
        case 1:
            drawInterceptorEnemy(renderer , enemyShip);
            break;
        case 2:
            drawLittleBomberEnemy(renderer , enemyShip);
            break;
        case 3:
            drawBigBomberEnemy(renderer , enemyShip);
            break;
        default:
            drawLittleEnemyShip(renderer , enemyShip);
            break;
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SQUADRON" , str);
    free(str);
}





int moveEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen)
{
    customLog(0 , "GAME" ,  __func__);
    if(enemyShip && enemyShip->movementScheme)
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
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    if(enemyShip->visible == VISIBLE)
        return 1;
    return 0;
    
}




void freeEnemyShip(EnemyShip * enemyShip)
{
    customLog(1 , "ENEMY" ,  __func__);
    free(enemyShip->rectangle);
    free(enemyShip->movementScheme);
    enemyShip->nextEnemyShip = NULL;
    free(enemyShip);
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "ENEMY" , str);
    free(str);
    
}

EnemyShip * initialisationEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel)
{
     customLog(0 , "GAME" , __func__);
    // __android_log_print(ANDROID_LOG_DEBUG, "EnemyShip",   "initialisationEnemyShip"  );
        EnemyShip * enemyShip;
     //__android_log_print(ANDROID_LOG_DEBUG, "EnemyShip",   "initialisationEnemyShip %d",  typeShip  );
    if(typeShip < 0)
        typeShip *= -1;
    
    
    switch(typeShip)
    {
        case 0: enemyShip   = initialisationLittleEnemyShip( width, height, typeStart, side, distance, verticalLine, typeShip, typeMovement,shotLevel);
            break;
        case 1: enemyShip   = initialisationInterceptorEnemy( width, height, typeStart, side, distance, verticalLine, typeShip, typeMovement,shotLevel);
            break;
        case 2: enemyShip   = initialisationLittleBomberEnemy( width, height, typeStart, side, distance, verticalLine, typeShip, typeMovement,shotLevel);
            break;
        case 3: enemyShip   = initialisationBigBomberEnemy( width, height, typeStart, side, distance, verticalLine, typeShip, typeMovement,shotLevel);
            break;
        default :
            break;
            
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);

    return enemyShip;
}



int canShoot(EnemyShip * enemyShip)
{
    customLog(1 , "ENEMY" ,  __func__);
    int canShoot =LittleEnemyShipCanShoot(enemyShip);
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "ENEMY" , str);
    free(str);
    return canShoot;
}

void setVisibilityEnemy(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
    customLog(0 , "GAME" ,  __func__);
    if(enemyShip != NULL && enemyShip->visible == VISIBLE )
    {
        
        if((enemyShip->posY+enemyShip->height) < 0 || enemyShip->posY > heightScreen || (enemyShip->posX + enemyShip->width) < 0 || enemyShip->posX > widthScreen)
        {
            setEnemyToInvisible(enemyShip);
        }
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "ENEMY" , str);
    free(str);
    
}

void moveEnemyShipVertically(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
    customLog(0 , "GAME" ,  __func__);
    //  __android_log_print(ANDROID_LOG_DEBUG, "Enemy", "move vertically");
    enemyShip->posY = enemyShip->posY + (1* enemyShip->speed);
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
    enemyShip->cntFootStep++;
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "ENEMY" , str);
    free(str);
    
    
}


void moveEnemyShipZigZag(EnemyShip * enemyShip,int widthScreen,int heightScreen)
{
    customLog(0 , "GAME" ,  __func__);
    //    __android_log_print(ANDROID_LOG_DEBUG, "Enemy", "move zig-zag");
    verifySideFromVerticalLine(enemyShip);
    enemyShip->posY = enemyShip->posY + (1 * enemyShip->speed);
    
    
    if(enemyShip->cntFootStep % CHGM_DIRECTION == 0)
    {
        //Bouge selon la densité de pixel sur l'écran
        enemyShip->posX = enemyShip->posX + (int)( (enemyShip->speed * widthScreen/heightScreen/3 ) * enemyShip->verticalSide );
    }
    enemyShip->cntFootStep++;
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
    //   __android_log_print(ANDROID_LOG_DEBUG, "Enemy", "enemyShip Positon X : %d , Position Y : %d",enemyShip->posX,enemyShip->posY);
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "ENEMY" , str);
    free(str);
    
    
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


void setEnemyToInvisible(EnemyShip * enemy)
{
    if(enemy)
    {
        //__android_log_print(ANDROID_LOG_DEBUG, "Enemy", " INVISIBLE");
        enemy->visible = INVISIBLE;
    }
}



void initialisationTypeStart(int width,int height,EnemyShip * enemyShip,int typeStart,int side,int defaultGap)
{
    int gap = 0;
    //  __android_log_print(ANDROID_LOG_DEBUG, "Start", "typeStart : %d , side : %d",typeStart,side);
    switch(typeStart)
    {
        case TOP_SCREEN :
            gap = width/8;
            if(side == 1)
            {
                
                enemyShip->rectangle->x = width/2 - gap;
                enemyShip->rectangle->y = 0;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    enemyShip->rectangle->x = width/2 + gap;
                    enemyShip->rectangle->y = 0;
                    enemyShip->verticalSide = -1;
                }
            }
            break;
            
        case TOP_SIDE_SCREEN :
            gap = width/6;
            if(side == 1)
            {
                
                enemyShip->rectangle->x = width/2 - gap;
                enemyShip->rectangle->y = 0;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    enemyShip->rectangle->x = width/2 + gap;
                    enemyShip->rectangle->y = 0;
                    enemyShip->verticalSide = -1;
                }
            }
            break;
            
        case TOP_MIDDLE_SIDE_SCREEN :
            gap = width/4;
            if(side == 1)
            {
                
                enemyShip->rectangle->x = width/2 - gap;
                enemyShip->rectangle->y = 0;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    enemyShip->rectangle->x = width/2 + gap;
                    enemyShip->rectangle->y = 0;
                    enemyShip->verticalSide = -1;
                }
            }
            break;
            
        case TOP_EXTREME_SIDE_SCREEN:
            gap = defaultGap;
            if(side == 1)
            {
                //     __android_log_print(ANDROID_LOG_DEBUG, "bigBomberEnemy", "TOP_EXTREME_SIDE_SCREEN____LEFT");
                
                
                enemyShip->rectangle->x = 0 ;
                enemyShip->rectangle->y = 0;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    
                    enemyShip->rectangle->x = width - gap ;
                    enemyShip->rectangle->y = 0;
                    enemyShip->verticalSide = -1;
                }
            }
            break;
            
        case EXTREME_SIDE_SCREEN:
            gap = defaultGap;
            if(side == 1)
            {
                
                enemyShip->rectangle->x = 0-(gap/2);
                enemyShip->rectangle->y = height/4 + gap ;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    enemyShip->rectangle->x = width -(gap/2);
                    enemyShip->rectangle->y = height/2 + gap;
                    enemyShip->verticalSide = -1;
                }
            }
            break;
            
        default :
            gap = width/8;
            if(side == 1)
            {
                
                enemyShip->rectangle->x = width/2 - gap;
                enemyShip->rectangle->y = 0;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    enemyShip->rectangle->x = width/2 + gap;
                    enemyShip->rectangle->y = 0;
                    enemyShip->verticalSide = -1;
                }
            }
            break;
    }
}





