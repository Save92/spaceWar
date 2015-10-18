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


EnemyShip * initialisationLittleEnemyShip(int width,int height,int typeStart)
{
    
    SDL_Rect  * rectangle = malloc( sizeof(SDL_Rect));
    EnemyShip  * enemyShip = malloc( sizeof(EnemyShip));
    myShip->rectangle = rectangle;
    
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




EnemyShip * initialisationTypeStart(EnemyShip * enemyShip,int typeStart)
{
    switch(typeStart)
    {
        case TOP_LEFT_SCREEN :
            break;
            
        case TOP_RIGHT_SCREEN :
            break;
            
        case LEFT_SCREEN :
            
   
        
    }















}