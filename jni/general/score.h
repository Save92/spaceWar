//
//  score.h
//  
//
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
void renderHighScore(Game * game,SDL_Renderer *renderer);



#endif /* score_h */
