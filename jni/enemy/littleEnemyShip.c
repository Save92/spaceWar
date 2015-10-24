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




void drawLittleEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip)
{
    enemyShip->rectangle->x = enemyShip->posX;
    enemyShip->rectangle->y = enemyShip->posY;
    enemyShip->rectangle->w = 30;
    enemyShip->rectangle->h = 30;
    SDL_SetRenderDrawColor(renderer, enemyShip->color[0], enemyShip->color[1], enemyShip->color[2], enemyShip->color[3]);
    SDL_RenderFillRect(renderer, (enemyShip->rectangle));
}


EnemyShip * initialisationLittleEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement)
{
    
    SDL_Rect  * rectangle = malloc( sizeof(SDL_Rect));
    EnemyShip  * enemyShip = malloc( sizeof(EnemyShip));
    enemyShip->rectangle = rectangle;
    enemyShip->verticalSide = side;
    
    initialisationTypeStart(width,height,enemyShip,typeStart,side);

    enemyShip->posX = rectangle->x;
    enemyShip->posY = rectangle->y;
    enemyShip->speed = 10;
    enemyShip->color[0] = 106;
    enemyShip->color[1] = 98;
    enemyShip->color[2] = 81;
    enemyShip->color[3] = 255;
    enemyShip->life = 1;
    enemyShip->shotLevel = 1;
    enemyShip->typeShip = typeShip;
    
    time_t t;
    
 
    
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    
    enemyShip->bonus = t%17;
    enemyShip->cntFootStep = 0;
    enemyShip->type = 0;
    enemyShip->typeMovement = typeMovement;
    enemyShip->cntFootStep = 0;
    enemyShip->movementScheme = initializeMovementScheme(enemyShip->posX,enemyShip->posY,0,0,distance,verticalLine,typeMovement);

    enemyShip->repeatMovement = 0;
    enemyShip->frequencyOfShoot = 15;
    enemyShip->verticalSide = side;
    

}




void initialisationTypeStart(int width,int height,EnemyShip * enemyShip,int typeStart,int side)
{
    int gap = 0;
    switch(typeStart)
    {
        case TOP_SCREEN :
            gap = width/8;
            if(side = 1)
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
            if(side = 1)
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
            if(side = 1)
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
            gap = width/2 - 30;
            if(side = 1)
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
            
        case EXTREME_SIDE_SCREEN:
            gap = 30;
            if(side = 1)
            {
                
                enemyShip->rectangle->x = 0;
                enemyShip->rectangle->y = height/8 + gap ;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    enemyShip->rectangle->x = width - gap;
                    enemyShip->rectangle->y = height/8 + gap;
                    enemyShip->verticalSide = -1;
                }
            }
            break;
    }
}


void moveLittleEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen)
{
    enemyShip->posY++;
    if(enemyShip->cntFootStep %4 == 0)
    {
        enemyShip->posX = enemyShip->posX + (enemyShip->speed * enemyShip->verticalSide);
    }
    enemyShip->cntFootStep++;
    
    
    
    setVisibilityEnemy(enemyShip,widthScreen,heightScreen);
}
    
int  LittleEnemyShipCanShoot(EnemyShip * enemyShip)
{
    
    if(enemyShip->cntFootStep % enemyShip->frequencyOfShoot == 0)
        return 1;
    else
        return 0;
        
}

Shoot * LittleEnemyShipShoot(EnemyShip * enemyShip)
{
    Shoot * shoot;
    return shoot;
}












