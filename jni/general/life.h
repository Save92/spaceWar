//
//  life.h
//  
//
//
//

#ifndef life_h
#define life_h

#include <stdio.h>

#include "./game.h"
#include "../enemy/enemy.h"
#include "../SDL/src/core/android/SDL_android.h"




//Fonction d'écriture de la vie
void renderLife(Game * game,SDL_Renderer *renderer);
#endif /* life_h */
