//
//  userShip.c
//
//
//  Created by thierry allard saint albin on 22/09/2015.
//
//

#include "../SDL/src/core/android/SDL_android.h"
#include "userShip.h"
#include <android/log.h>
#include <jni.h>
#include <stdlib.h>
#include <math.h>
#include "../general/constant.h"
#include "../general/drawer.h"
#include "../general/CustomLog.h"

#define SPEED_DIVIDENDE 4
void drawMyShip(SDL_Renderer* renderer , UserShip * myShip)
{
    myShip->cntMovement++;
    if(myShip->visible == VISIBLE)
    {
        
        myShip->rectangle->x = myShip->posX;
        myShip->rectangle->y = myShip->posY;
        myShip->rectangle->w = 200;
        myShip->rectangle->h = 174;
        //SDL_SetRenderDrawColor(renderer, myShip->color[0], myShip->color[1], myShip->color[2], myShip->color[3]);
        //SDL_RenderFillRect(renderer, (myShip->rectangle));
        //myShip->myShipSprite = LoadSprite("myShipGood.bmp", renderer);
        myShip->myShipSprite = loadTexture("myShipGood.png", renderer);
        
        renderTexture(myShip->myShipSprite.texture, renderer, myShip->rectangle->x, myShip->rectangle->y);
    }
}

void moveMyShip(UserShip * myShip,int TypeMove,int widthScreen, int heightScreen, double coef)
{
    int newValue;
    // __android_log_print(ANDROID_LOG_DEBUG, "TypeMove"," %d",TypeMove);
    int cntMovement;
    
    switch(TypeMove)
    {
        case 0:
            
            newValue = myShip->posX + (coef * myShip->speed);
            if(newValue < widthScreen - myShip->rectangle->w)
                myShip->posX = newValue;
            
            break;
            
        case 1:
            
            newValue = myShip->posY + (coef * myShip->speed);
            if(newValue < heightScreen - myShip->rectangle->h)
                myShip->posY = newValue;
            break;
            
        case 2:
            
            newValue = myShip->posX - (coef * myShip->speed);
            
            if(newValue > -1)
                myShip->posX = newValue;
            
            break;
            
        case 3:
            newValue = myShip->posY - (coef * myShip->speed);
            //  if(newValue > -1)
            myShip->posY = newValue;
            break;
            
    }
}
void moveMyShipTouch(int posX , int posY ,UserShip * myShip,int widthScreen,int heightScreen)
{
     __android_log_print(ANDROID_LOG_DEBUG, "UserShip", "moveMyShipTouch");
    
    __android_log_print(ANDROID_LOG_DEBUG, "UserShip", "[FINGER] PosX %d , PosY %d", posX, posY);
    __android_log_print(ANDROID_LOG_DEBUG, "UserShip", "[UserShip] Pos %d , PosY %d", myShip->posX, myShip->posY);
    int coef = (int)1/DIVIDENDE_SPEED;
    int ecart = coef * myShip->speed;
    int tempPosX = myShip->posX;
    int tempPosY = myShip->posY;
    if(myShip->posX < (posX - ecart) )
    {
        tempPosX += ecart;
    }
    if(myShip->posX > (posX + ecart))
    {
        tempPosX -= ecart;
    }
    if(myShip->posY < (posY - ecart))
    {
        tempPosY += ecart;
    }
    if(myShip->posY > (posY + ecart))
    {
        tempPosY -= ecart;
    }
    
    if(tempPosX > 0  && tempPosX < (widthScreen -  myShip->rectangle->w))
    {
        myShip->posX = tempPosX;
    }
    
    if(tempPosY > 0  && tempPosY < (heightScreen -  myShip->rectangle->h))
    {
        myShip->posY = tempPosY;
    }
    
}

void moveMyShipGeneral(float * accelValues,int sizeAccelValues ,UserShip * myShip,int widthScreen, int heightScreen){

    char values[30];
    int index = 0;
    for(index = 0 ; index < sizeAccelValues ; index++)
    {
        switch(index)
        {
            case 0:
                if(accelValues[index] > 0.15)
                {
                    moveMyShip(myShip,0,widthScreen,heightScreen, fabs(floor(accelValues[index]/DIVIDENDE_SPEED)));
                }
                
                if(accelValues[index] < -0.15)
                {
                    moveMyShip(myShip,2,widthScreen,heightScreen, fabs(floor(accelValues[index]/DIVIDENDE_SPEED)));
                }
                break;
            case 1:
                if(accelValues[index] > 0.15)
                {
                    moveMyShip(myShip,1,widthScreen,heightScreen, fabs(floor(accelValues[index]/DIVIDENDE_SPEED)));
                }
                if(accelValues[index] < -0.15)
                {
                    moveMyShip(myShip,3,widthScreen,heightScreen, fabs(floor(accelValues[index]/DIVIDENDE_SPEED)));
                }
                break;
        }
    }
}



void freeShip(UserShip * myShip)
{
    free(myShip->rectangle);
    free(myShip);
}

UserShip * initialisationUserShip(int width,int height)
{
    SDL_Rect  * rectangle = malloc( sizeof(SDL_Rect));
    UserShip  * myShip = malloc( sizeof(UserShip));
    myShip->rectangle = rectangle;
    
    rectangle->x = width/2;
    rectangle->y = height/8 * 7;
    myShip->posX = rectangle->x;
    myShip->posY = rectangle->y;
    myShip->speed = 1;
    myShip->color[0] = 96;
    myShip->color[1] = 198;
    myShip->color[2] = 181;
    myShip->color[3] = 255;
    myShip->life = STARTING_LIFE;
    myShip->shotLevel = 1;
    myShip->visible = VISIBLE;
    myShip->cntMovement = 0;
    myShip->canShoot = FALSE;
    //myShip->myShipSprite = NULL;
    return myShip;
}

int userShipIsAlive(UserShip * userShip)
{
    if(userShip->life == 0)
        return FALSE;
    return TRUE;
}

void decreaseLife( UserShip * myShip )
{
    if(myShip->life >0)
    {
        (myShip->life)--;
    }
    if(myShip->life == 0)
    {
        myShip->visible = INVISIBLE;
    }
}
void addLife( UserShip * myShip )
{
    if(myShip->life < MAX_LIFE && myShip->visible == VISIBLE)
        (myShip->life)++;
}

void addSpeed( UserShip * myShip )
{
    if(myShip->speed < MAX_SPEED)
    {
        myShip->speed = myShip->speed + myShip->speed/SPEED_DIVIDENDE;
    }
}
void decreaseSpeed( UserShip * myShip )
{
    if(myShip->speed > 1)
    {
        myShip->speed = myShip->speed - myShip->speed/SPEED_DIVIDENDE;
    }
}


void addShotLevel( UserShip * myShip )
{
    if(myShip->shotLevel < MAX_POWER)
    {
        myShip->shotLevel++;
    }
}
void decreaseShotLevel( UserShip * myShip )
{
    if(myShip->shotLevel > 1)
    {
        myShip->shotLevel--;
    }
}

int myShipContinousShoot( UserShip * myShip )
{
    if(myShip->cntMovement >= RATE_IMAGE_SHOOT && myShip->canShoot == TRUE && myShip->life > 0 )
    {
        myShip->cntMovement = 0;
        return TRUE;
    }
    return FALSE;
}

    
    
