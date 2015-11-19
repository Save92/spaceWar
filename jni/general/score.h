//
//  score.h
//  
//
//  Created by thierry allard saint albin on 19/11/2015.
//
//

#ifndef score_h
#define score_h

#include <stdio.h>
#include "./game.h"
#include "../enemy/enemy.h"
#include "../SDL/src/core/android/SDL_android.h"




void renderScore(Game * game,SDL_Renderer *renderer);
void addScore(EnemyShip enemy, int * score );


#endif /* score_h */
