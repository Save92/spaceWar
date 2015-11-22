//
//  drawer.h
//  
//
//  Created by thierry allard saint albin on 22/11/2015.
//
//

#ifndef drawer_h
#define drawer_h

#include <stdio.h>
#include "../SDL/src/core/android/SDL_android.h"
#include <jni.h>
#include "SDL.h"

typedef struct Sprite
{
    SDL_Texture* texture;
    Uint16 w;
    Uint16 h;
} Sprite;


#endif /* drawer_h */
