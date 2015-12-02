//
//  interceptorEnemy.c
//  
//
//  Created by Nicolas Journaud
//
//

#include "interceptorEnemy.h"
#include "movementConstant.h"

#include <jni.h>
#include <stdlib.h>
#include <math.h>
#include <android/log.h>
#include "../general/constant.h"


void drawInterceptorEnemy(SDL_Renderer* renderer , EnemyShip * enemyShip)
{
    customLog(1 , "ENEMY" ,  __func__);
    enemyShip->rectangle->x = enemyShip->posX;
    enemyShip->rectangle->y = enemyShip->posY;
    enemyShip->rectangle->w = enemyShip->width;
    enemyShip->rectangle->h = enemyShip->height;
    // SDL_SetRenderDrawColor(renderer, enemyShip->color[0], enemyShip->color[1], enemyShip->color[2], enemyShip->color[3]);
    // SDL_RenderFillRect(renderer, (enemyShip->rectangle));
    //enemyShip->enemySprite = LoadSprite("littleEnemy.bmp", renderer);

    //enemyShip->enemySprite = loadTexture("interceptorEnemy.png", renderer);
    enemyShip->enemySprite = getInterceptorImg();
    renderTexture(enemyShip->enemySprite.texture, renderer, enemyShip->rectangle->x, enemyShip->rectangle->y);
    
}


EnemyShip * initialisationInterceptorEnemy(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel)
{
    customLog(0 , "GAME" , __func__);
    
    SDL_Rect  * rectangle = malloc( sizeof(SDL_Rect));
    EnemyShip  * enemyShip = malloc( sizeof(EnemyShip));
    enemyShip->rectangle = rectangle;
    enemyShip->verticalSide = side;
    enemyShip->width = WIDTH_INTERCEPTOR;
    enemyShip->height = HEIGHT_INTERCEPTOR;
    enemyShip->speed = (float)(height/width) * RATIO_SPEED;
    enemyShip->color[0] = 106;
    enemyShip->color[1] = 98;
    enemyShip->color[2] = 81;
    enemyShip->color[3] = 255;
    enemyShip->life = 2;
    
    enemyShip->typeShip = typeShip;
    int defaultGap = enemyShip->width ;
    initialisationTypeStart(width,height,enemyShip,typeStart,side,defaultGap);

    enemyShip->posX = rectangle->x;
    enemyShip->posY = rectangle->y;
    
    
 
    
    time_t t;
    
 
    
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    
    enemyShip->bonus = t%17;
    enemyShip->shotLevel = shotLevel;
    enemyShip->cntFootStep = 0;
    enemyShip->type = typeShip;
    enemyShip->typeMovement = typeMovement;
   // __android_log_print(ANDROID_LOG_DEBUG, "interceptorEnemy", "__initialisationinterceptorEnemy__ distance : %d",distance);
    enemyShip->movementScheme = initializeMovementScheme(enemyShip->posX,enemyShip->posY,0,0,distance,verticalLine,typeMovement);

    enemyShip->changeDirection = t%3;
    
    enemyShip->repeatMovement = 0;
    enemyShip->frequencyOfShoot = 30;
    enemyShip->verticalSide = side;
    enemyShip->nextEnemyShip = NULL;
    enemyShip->visible = VISIBLE;


    return enemyShip;

}

















