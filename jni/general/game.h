//
//  game.h
//  
//
//  Created by thierry allard saint albin on 01/11/2015.
//
//

#ifndef game_h
#define game_h

#include <stdio.h>

#include "../enemy/squadron.h"
#include "../enemy/positionHistory.h"

typedef struct Game Game;
struct Game
{
    Squadron * nextSquadron;
    int size;
    int score;
    char * nameUser;
    int level;
    int height;
    int width;
    int history;
    
    
    
    int cntInLastSquadron;
    StackHistory * stack ;
};



Game *  initialisationOfTheGame(int width,int height);
void  moveAllGame(Game * game);
void  drawGame(SDL_Renderer* renderer ,Game * game);
void  createNextSquadron(Game * game);
void  removeNotVisibleEnemyFromGame(Game * game);
void  removeNotVisibleSquadronFromGame(Game * game);

void addNewEnemy(Game * game,Squadron * squadron);
void addEnemyFromHistory(Game * game);

Squadron * getLastSquadron(Game * game);


#endif /* game_h */
