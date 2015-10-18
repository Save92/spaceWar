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
#include "../user/userShip.h"

typedef struct Shoot Shoot;
struct Shoot
{
    int posX;
    int posY;
    int speed;
    int color[4];
    int visible;
    int type ;
    int index ;
    SDL_Rect *rectangle;
    Shoot * nextShoot ;
    int direction ;
    int damage ;
    int cmptMoov ;
    int way;

};


/*
 direction :
 0 : verticale
 1 : diagonale coin haut gauche
 2 : diagonale coin haut droit
 3 : diagonale haut gauche
 4 : diagonale haut droit
 5 : missile tête chercheuse
 */


typedef struct ListShoot{
    
    Shoot * start;
    int size;
} ListShoot;


void drawMyShoot(SDL_Renderer* renderer , Shoot * listShoot);
void drawAllMyShoots(SDL_Renderer* renderer , ListShoot * shoot);

void moveMyShoot(Shoot * shoot ,int widthScreen , int heightScreen);
void moveVerticaly(Shoot * shoot,int widthScreen,int heightScreen);
void moveDiagonaleLeft(Shoot * shoot,int widthScreen,int heightScreen);
void moveDiagonaleRight(Shoot * shoot,int widthScreen,int heightScreen);
void moveDiagonaleSubRight(Shoot * shoot,int widthScreen,int heightScreen);
void moveDiagonaleSubLeft(Shoot * shoot,int widthScreen,int heightScreen);
void moveAllMyShoots(ListShoot * listShoot,int widthScreen,int heightScreen);




void setVisibility(Shoot * shoot,int widthScreen,int heightScreen);

void filterMyShoots(ListShoot * listShoot);
void FreeMyShoot(Shoot * shoot);
void myShipShoot(UserShip myShip,ListShoot * listShoot,int direction,int damage);

void UserShipShoot(UserShip myShip,ListShoot * listShoot);




#endif /* defined(____shoot__) */
