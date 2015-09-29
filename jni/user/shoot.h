//
//  shoot.h
//  
//
//  Created by thierry allard saint albin on 27/09/2015.
//
//

#ifndef ____shoot__
#define ____shoot__

#include <stdio.h>
#include "userShip.h"

typedef struct Shoot Shoot;
struct Shoot
{
    int posX;
    int posY;
    int speed;
    int color[4];
    int visible;
    SDL_Rect *rectangle;
    Shoot * nextShoot ;
};



typedef struct ListShoot{
    
    Shoot * start;
    int size;
} ListShoot;


void drawMyShoot(SDL_Renderer* renderer , Shoot * listShoot);
void moveMyShoot(Shoot * shoot , int typeShoot,int widthScreen , int heightScreen);
void moveVerticaly(Shoot * shoot,int widthScreen,int heightScreen);
void setVisibility(Shoot * shoot,int widthScreen,int heightScreen);
void drawAllMyShoots(SDL_Renderer* renderer , ListShoot * shoot);
ListShoot * filterMyShoots(ListShoot * listShoot);
void FreeMyShoot(Shoot * shoot);
void myShipShoot(UserShip myShip,ListShoot * Shoot);
void moveAllMyShoots(ListShoot * listShoot,int typeShoot,int widthScreen,int heightScreen);


#endif /* defined(____shoot__) */
