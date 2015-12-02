//
//  userShip.h
//  
//
//
//

#ifndef ____userShip__
#define ____userShip__

#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include "../general/drawer.h"

#define MAX_LIFE 99

typedef struct UserShip
{
    int posX;
    int posY;
    float speed;
    int life;
    int color[4];
    SDL_Rect *rectangle;
    int shotLevel;
    int visible ;
    Sprite myShipSprite;
    unsigned int cntMovement;
    int canShoot ;


    
} UserShip;


void drawMyShip(SDL_Renderer* renderer , UserShip * myShip);
void moveMyShip(UserShip * myShip,int TypeMove,int widthScreen, int heightScreen, double coef);


void freeShip(UserShip * myShip);
UserShip * initialisationUserShip();
void moveMyShipGeneral(float * accelValues,int SIZEACCELVALUES,UserShip * myShip,int widthScreen,int heightScreen);

void moveMyShipTouch(int posX , int posY ,UserShip * myShip,int widthScreen,int heightScreen);

int userShipIsAlive(UserShip * userShip);
void decreaseLife( UserShip * myShip);
void addLife( UserShip * myShip);
void addSpeed( UserShip * myShip );
void decreaseSpeed( UserShip * myShip );
void addShotLevel( UserShip * myShip );
void decreaseShotLevel( UserShip * myShip );
int myShipContinousShoot( UserShip * myShip );

#endif /* defined(____userShip__) */


