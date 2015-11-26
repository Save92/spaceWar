//
//  littleEnemyShip.c
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#include "littleEnemyShip.h"
#include "movementConstant.h"

#include <jni.h>
#include <stdlib.h>
#include <math.h>
#include <android/log.h>
#include "../general/constant.h"

#define RATIO_SIZE 50
#define RATIO_SPEED 15
void drawLittleEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip)
{
    enemyShip->rectangle->x = enemyShip->posX;
    enemyShip->rectangle->y = enemyShip->posY;
    enemyShip->rectangle->w = enemyShip->width;
    enemyShip->rectangle->h = enemyShip->height;
    // SDL_SetRenderDrawColor(renderer, enemyShip->color[0], enemyShip->color[1], enemyShip->color[2], enemyShip->color[3]);
    // SDL_RenderFillRect(renderer, (enemyShip->rectangle));
    enemyShip->enemySprite = LoadSprite("littleEnemy.bmp", renderer);
    renderTexture(enemyShip->enemySprite.texture, renderer, enemyShip->rectangle->x, enemyShip->rectangle->y);
    
}


EnemyShip * initialisationLittleEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement)
{
    
    SDL_Rect  * rectangle = malloc( sizeof(SDL_Rect));
    EnemyShip  * enemyShip = malloc( sizeof(EnemyShip));
    enemyShip->rectangle = rectangle;
    enemyShip->verticalSide = side;
    enemyShip->width = 110;
    enemyShip->height = 120;
    enemyShip->speed = (float)(height/width) * RATIO_SPEED;
    enemyShip->color[0] = 106;
    enemyShip->color[1] = 98;
    enemyShip->color[2] = 81;
    enemyShip->color[3] = 255;
    enemyShip->life = 1;
    
    enemyShip->typeShip = typeShip;
    int defaultGap = enemyShip->width ;
    initialisationTypeStart(width,height,enemyShip,typeStart,side,defaultGap);

    enemyShip->posX = rectangle->x;
    enemyShip->posY = rectangle->y;
    
    
 
    
    time_t t;
    
 
    
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    
    enemyShip->bonus = t%17;
    enemyShip->shotLevel = t%2;
    enemyShip->cntFootStep = 0;
    enemyShip->type = 0;
    enemyShip->typeMovement = typeMovement;
   // __android_log_print(ANDROID_LOG_DEBUG, "littleEnemyShip", "__initialisationLittleEnemyShip__ distance : %d",distance);
    enemyShip->movementScheme = initializeMovementScheme(enemyShip->posX,enemyShip->posY,0,0,distance,verticalLine,typeMovement);

    enemyShip->changeDirection = t%3;
    
    enemyShip->repeatMovement = 0;
    enemyShip->frequencyOfShoot = 50;
    enemyShip->verticalSide = side;
    enemyShip->nextEnemyShip = NULL;
    enemyShip->visible = VISIBLE;


    

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
           //     __android_log_print(ANDROID_LOG_DEBUG, "littleEnemyShip", "TOP_EXTREME_SIDE_SCREEN____LEFT");
                
               
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


void moveLittleEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen)
{
    enemyShip->posY++;
    if(enemyShip->cntFootStep % enemyShip->changeDirection == 0)
    {
        enemyShip->posX = (int)(enemyShip->posX + (enemyShip->speed * enemyShip->verticalSide));
    }
    enemyShip->cntFootStep++;
    
    
    
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
}
    
int  LittleEnemyShipCanShoot(EnemyShip * enemyShip)
{
    
    if(enemyShip->cntFootStep % enemyShip->frequencyOfShoot == 0)
        return TRUE;
    else
        return FALSE;
        
}














