//
//  drawer.h
//  
//
//
//

#ifndef drawer_h
#define drawer_h

#include <stdio.h>
#include "../SDL/src/core/android/SDL_android.h"
#include <jni.h>
#include "SDL.h"
/**
 *Un Sprite est constitué d'une texture, d'une largeur et d'une longeur
 *
 */

typedef struct Sprite
{
    SDL_Texture* texture;
    Uint16 w;
    Uint16 h;
} Sprite;
//Fonction de chargement de sprite à partir d'un fichier png, prend en argument une variable SDL_Renderer
Sprite LoadSprite(const char* file, SDL_Renderer* renderer);
//Fonction de chargement d'une texture à partir d'un fichier png, prend en argument une variable SDL_Renderer
Sprite loadTexture(const char* file, SDL_Renderer* renderer);
//Fonction de chargement d'image
void loadImages(SDL_Renderer* renderer);
//Récupération du sprite LittleEnemy
Sprite getLittleEnemyImg();
//Récupération du sprite d'un LittleBomber
Sprite getLittleBomberImg();
//Récupération du sprite d'un intercepteur
Sprite getInterceptorImg();
//Récupération du sprite d'un Bomber
Sprite getBigBomberImg();
//Récupération du sprite du vaisseau d'un utilisateur
Sprite getUserShipImg();
#endif /* drawer_h */
