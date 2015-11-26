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
#include "../enemy/enemy.h"
#include "../user/UserShip.h"
#include "./drawer.h"
#include "./shoot.h"
#include <SDL_ttf.h>
#include "SDL_mixer.h"
#include "./constant.h"


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
    int tempsActuel;
    int tempsPrecedent;
    UserShip * myShip;
    ListShoot * listShootUser;
    ListShoot * listShootEnnemy;
    TTF_Font *police;
    int initText;
    SDL_Haptic* gControllerHaptic;
    int initRumble;
    Sprite background;
    
    
    int cntInLastSquadron;
    StackHistory * stack ;
    int initAudio;
    Mix_Music *mainMusic;
    Mix_Chunk *tie_arrive;
    Mix_Chunk *tie_shoot;
    Mix_Chunk *Xwing_shoot;
    Mix_Chunk *Immhit;

};

#include "./score.h"
#include "./life.h"

typedef struct Rgb
{
    int r;
    int g;
    int b;
} Rgb;

typedef struct SpriteExplosion
{
    // x y w h sont la position de l'image sur la feuille de sprite
    // axe horizontal
   int x; 
   // axe vertical
   int y; 
   // width
   int w; 
   // height
   int h; 
   // angle du sprite 
   double angle;
   // Couleur du background du sprite
   Rgb background; 
   // LOAD_BMP du sprite
   SDL_Surface *surface; 
   // SDL_CreateTextureFromSurface(_renderer, surface);
   SDL_Texture *texture;
//
    SDL_Rect *image_location;
} SpriteExplosion;


void initialisationSound( Game * game);

enum RumbleForce {AUCUN,FAIBLE, MEDIUM_FORCE, FORT,MAXIMUM};
enum RumbleLength {INEXISTANT,COURT, MEDIUM_LENGTH, LONG};

Game *  initialisationOfTheGame(int width,int height);
void  moveAllGame(Game * game, SDL_Renderer *renderer);
void  drawGame(SDL_Renderer* renderer ,Game * game);
void  createNextSquadron(Game * game);
void  removeNotVisibleSquadronFromGame(Game * game);

void addNewEnemy(Game * game,Squadron * squadron,ListePosition * lp);
void addEnemyFromHistory(Game * game);

Squadron * getLastSquadron(Game * game);
int my_rand();

int checkCollision(SDL_Rect a, SDL_Rect b,int speed );
void eventCheckCollisionUserShipEnnemyShoot(Game * game, SDL_Renderer *renderer);
void eventCheckCollisionUserShipEnnemyShip(Game * game, SDL_Renderer *renderer);
void onDestroy(int posx, int posy, SDL_Renderer *renderer);
SpriteExplosion LoadSpriteForExplostion(int image, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void playRumble(Game * game,enum RumbleForce force,enum RumbleLength length);
//jint Java_esgi_fouriam_SDLActivity_setPref(JNIEnv * env, jobject thiz, jstring name, jint commandValue, jint musicValue, jint vibrationValue, jint highScore);
void setHighScore(JNIEnv * env, jobject thiz, int score);
void playMusic(Mix_Music *mainMusic,int cntRepeat);
void filterShootsFromGame(Game * game);



#endif /* game_h */
