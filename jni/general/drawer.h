#ifndef ____drawer__
#define ____drawer__

#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"

#include "../enemy/enemy.h"
#include "../user/userShip.h"
#include "game.h"

typedef struct Sprite
{
    SDL_Texture* texture;
    Uint16 w;
    Uint16 h;
} Sprite;

Sprite LoadSprite(const char* file, SDL_Renderer* renderer);

#endif /* ____drawer__ */