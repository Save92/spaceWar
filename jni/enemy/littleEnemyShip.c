//
//  littleEnemyShip.c
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#include "littleEnemyShip.h"
#include "movementConstant.h"


void drawLittleEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip)
{
    enemyShip->rectangle->x = enemyShip->posX;
    enemyShip->rectangle->y = enemyShip->posY;
    enemyShip->rectangle->w = 30;
    enemyShip->rectangle->h = 30;
    SDL_SetRenderDrawColor(renderer, myShip->color[0], myShip->color[1], myShip->color[2], myShip->color[3]);
    SDL_RenderFillRect(renderer, (myShip->rectangle));
}


EnemyShip * initialisationLittleEnemyShip(int width,int height,int typeStart,int side)
{
    
    SDL_Rect  * rectangle = malloc( sizeof(SDL_Rect));
    EnemyShip  * enemyShip = malloc( sizeof(EnemyShip));
    enemyShip->rectangle = rectangle;
    enemyShip->verticalSide = side;
    
    switch (typeStart) {
        case :
            <#statements#>
            break;
            
        default:
            break;
    }
    
    
    rectangle->x = width/2;
    rectangle->y = height/8 * 7;
    myShip->posX = rectangle->x;
    myShip->posY = rectangle->y;
    myShip->speed = 1;
    myShip->color[0] = 96;
    myShip->color[1] = 198;
    myShip->color[2] = 181;
    myShip->color[3] = 255;
    myShip->life = 5;
    myShip->shotLevel = 5;

    

}




EnemyShip * initialisationTypeStart(int width,int height,EnemyShip * enemyShip,int typeStart,int side)
{
    switch(typeStart)
    {
        case TOP_SCREEN :
            if(side = 1)
            {
                enemyShip->rectangle->x = width/2 - width/8;
                enemyShip->rectangle->y = 0;
                enemyShip->verticalSide = 1;
            }
            else
            {
                if(side == -1)
                {
                    enemyShip->rectangle->x = width/2 + width/8;
                    enemyShip->rectangle->y = 0;
                }
            }
            break;
            
        case TOP_SIDE_SCREEN :
            break;
            
        case TOP_MIDDLE_SIDE_SCREEN :
            break;
            
        case TOP_EXTREME_SIDE_SCREEN:
            break;
            
        case EXTREME_SIDE_SCREEN:
            break;
   
        
    }















}