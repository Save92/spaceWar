//
//  squadron.h
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#ifndef squadron_h
#define squadron_h

#include <stdio.h>
#include "./enemy.h"
#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"
typedef struct Squadron Squadron;
struct Squadron
{
    EnemyShip * nextEnemyShip;
    int size;
    int maxSize;
    int visible;
    int appearNext;
    Squadron * nextSquadron;
    
};


Squadron * initialisationSquadron(int maxSize);
void addEnemyToSquadron(EnemyShip * enemy,Squadron * squadron);
void removeNotVisibleEnemy(Squadron * squadron);
void moveSquadron(Squadron * squadron,int width,int height);
void drawMySquadron(SDL_Renderer* renderer , Squadron * squadron);
int allVisible(Squadron * squadron);
int sendNextSquadron(Squadron * squadron,int width,int height);
void freeSquadron(Squadron * squadron);
EnemyShip * getlastEnemyShip(Squadron * squadron);


#endif /* squadron_h */