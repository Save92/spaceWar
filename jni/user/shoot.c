//
//  shoot.c
//  
//
//  Created by thierry allard saint albin on 27/09/2015.
//
//
#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include "shoot.h"
#include <jni.h>
#include <android/log.h>
#include <stdlib.h>
void drawMyShoot(SDL_Renderer* renderer , Shoot * shoot)
{
    shoot->rectangle->x = shoot->posX;
    shoot->rectangle->y = shoot->posY;
    shoot->rectangle->w = 5;
    shoot->rectangle->h = 10;
    SDL_SetRenderDrawColor(renderer, shoot->color[0], shoot->color[1], shoot->color[2], shoot->color[3]);
    SDL_RenderFillRect(renderer, (shoot->rectangle));
}

void moveMyShoot(Shoot * shoot , int typeShoot,int widthScreen , int heightScreen)
{

    __android_log_print(ANDROID_LOG_DEBUG, "moveMyShoot",  "Shoot typeShoot : %d ",typeShoot);
    if(shoot != NULL)
    {
        switch(typeShoot)
        {
            case 0: moveVerticaly(shoot,widthScreen,heightScreen);
                break;
            default : moveVerticaly(shoot,widthScreen,heightScreen);
                break;
        }
    }
    
    
}

void moveVerticaly(Shoot * shoot,int widthScreen,int heightScreen)
{
    if(shoot != NULL)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "moveVerticaly",  "Shoot posX : %d posY :%d",  shoot->posX ,shoot->posY);
        shoot->posY = shoot->posY  - ( 1 * shoot->speed);
        setVisibility(shoot,widthScreen,heightScreen);
    }
}

void setVisibility(Shoot * shoot,int widthScreen,int heightScreen)
{
    if(shoot != NULL)
    {
        if(shoot->posY < 0 || shoot->posY > heightScreen || shoot->posX < 0 || shoot->posX > widthScreen)
        {
            shoot->visible = 0;
        }
    }
}


void moveAllMyShoots(ListShoot * listShoot , int typeShoot,int widthScreen , int heightScreen)
{
    int cnt = 0;
    if((*listShoot).size > 0 && (*listShoot).start)
    {
        
        Shoot * nextShoot;
        nextShoot = (*listShoot).start;
        while(nextShoot)
        {
            cnt++;
            __android_log_print(ANDROID_LOG_DEBUG, "moveVerticaly",  "Shoot adress :%d",  nextShoot);
                moveMyShoot(nextShoot,typeShoot,widthScreen,heightScreen);
                nextShoot = nextShoot->nextShoot;
            
        }
    }
    
}

void drawAllMyShoots(SDL_Renderer* renderer , ListShoot * listShoot)
{
    if(listShoot->size > 0)
    {
        Shoot * nextShoot = listShoot->start;
        while(nextShoot != NULL)
        {
            
            drawMyShoot(renderer,nextShoot);
            nextShoot = nextShoot->nextShoot;
        }
    }
}

ListShoot * filterMyShoots(ListShoot * listShoot)
{
    ListShoot * filteredShoots = malloc(sizeof(listShoot)) ;
    filteredShoots->size = 0;
    if(listShoot->size > 0)
    {
        
        Shoot * lastShootFiltered;
        Shoot * nextShoot = listShoot->start;
        while(nextShoot != NULL)
        {
            if(nextShoot->visible == 1)                 //Si Le tir est visible
            {
                if(lastShootFiltered == NULL)           //Si c'est la 1ere fois qu'on trouve un tir visible
                {
                    lastShootFiltered = nextShoot;      // Le dernier tir est le tir
                    filteredShoots->start = nextShoot;         // le 1er tir est le début de notre liste chainéé
                }
                else
                {
                    lastShootFiltered->nextShoot = nextShoot;       //On rajoute un tir suivant
                    lastShootFiltered = nextShoot;                  // on bouge notre pointeur à la valeur suivante
                }
                nextShoot = nextShoot->nextShoot;
            }
            else
            {
                Shoot * deletedShoot = nextShoot;
                nextShoot = nextShoot->nextShoot;
                FreeMyShoot(deletedShoot);
            }
        }
    }
     return filteredShoots;
}

void myShipShoot(UserShip myShip,ListShoot * listShoot)
{
    __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "myShipShoot");
    int cnt = 0;
    Shoot * nextShoot = malloc(sizeof(Shoot));
    (*nextShoot).posX = myShip.posX + ( myShip.rectangle->w/2);
    (*nextShoot).posY = myShip.posY;
    (*nextShoot).speed = 10;
    (*nextShoot).color[0] = 255;
    (*nextShoot).color[1] = 255;
    (*nextShoot).color[2] = 255;
    (*nextShoot).color[3] = 255;
    (*nextShoot).rectangle = malloc( sizeof(SDL_Rect));
    (*nextShoot).visible = 1;
   
    __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "Shoot posX : %d posY :%d",  (*nextShoot).posX ,(*nextShoot).posY);
    if(listShoot->size > 0 && (*listShoot).start != NULL)
    {
        Shoot * previousShoot;
        Shoot * lastShoot ;
        lastShoot = (*listShoot).start;
        while(lastShoot != NULL)
        {
            previousShoot = lastShoot;
            lastShoot = (*lastShoot).nextShoot;
        }
        nextShoot->nextShoot = NULL;
        previousShoot->nextShoot = nextShoot;
    }
    else
    {
        (*listShoot).start = nextShoot;
        (*listShoot).start->nextShoot = NULL;
    }
    (*listShoot).size =  (*listShoot).size +1;
}


void FreeMyShoot(Shoot * shoot)
{
    free(shoot->rectangle);
    free(shoot);
}






