//
//  squadron.h
//  
//
//
//

#ifndef squadron_h
#define squadron_h

#include <stdio.h>
#include "./enemy.h"

#include "../general/shoot.h"
#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include "SDL_mixer.h"
typedef struct Squadron Squadron;

//Une escouade est définie selon une taille, une taille maximal, une visibilité
//Elle permet d'accéder à un nouvel ennemie et à une nouvel escouade

struct Squadron
{
    EnemyShip * nextEnemyShip;
    int size;
    int maxSize;
    int visible;
    Squadron * nextSquadron;
    
};


Squadron * initialisationSquadron(int maxSize);
void addEnemyToSquadron(EnemyShip * enemy,Squadron * squadron);
void moveSquadron(Squadron * squadron,int width,int height,ListShoot * listShootEnnemy,Mix_Chunk * tie_shoot,int playMusic);
void drawMySquadron(SDL_Renderer* renderer , Squadron * squadron);
int allVisible(Squadron * squadron);

void freeSquadron(Squadron * squadron);
EnemyShip * getlastEnemyShip(Squadron * squadron);
void setVisibilitySquadron(Squadron * squadron);


#endif /* squadron_h */
