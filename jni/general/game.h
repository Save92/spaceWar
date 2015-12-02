//
//  game.h
//  
//
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
    Squadron * nextSquadron;        //Liste chainée d'escouade. une Escouade contient un groupe d'ennemies
    int size;                       // Nombre d'escouades présente dans le jeu
    int score;                      // Score actuel de l'utilisateur
    char * nameUser;                // Nom de l'utilisateur
    int level;                      // niveau actuel de l'utilisateur
    int height;                     //Largeur de l'écran
    int width;                      //Longeur de l'écran
    int history;                    // Nombre d'élément présent en sauvegarde dans la partie Game
    int tempsActuel;                //Temps actuel passé dans le jeu
    int tempsPrecedent;             //Temps précédent passé depuis la dernière apparition d'escouade
    UserShip * myShip;              // Vaisseau de l'utilisateur
    ListShoot * listShootUser;      // liste chainé de tir de l'utilisateur
    ListShoot * listShootEnnemy;    // liste chainé de tir de l'énnemie
    TTF_Font *police;               // police utilisé dans le jeu
    int initText;                   // entier définissant si l'initialisation de la police s'est bien passé
                                    // si il est égale à -1, l'initialisation s'est mal passé.
    int cntInLastSquadron;          // nombre d'énnemie apparue dans la dernière escouade
    StackHistory * stack ;          // Pile d'historique d'apparition des ennemies
    int initAudio;                  // entier définissant si l'audio a bien été initialisé.
                                    // la variable est égale à -1 si l'initialisation s'est mal passé
    
    Mix_Music *mainMusic;           // pointeur sur la musique courante du jeu
    Mix_Chunk *tie_arrive;          // pointeur sur le sample audio joué lorsque un chasseur tie arrive
    Mix_Chunk *tie_shoot;           // pointeur sur le sample audio joué losque un chasseur tie tir
    Mix_Chunk *Xwing_shoot;         // pointeur sur le sample audioi joué lorsque le vaisseau de l'utilisateur
                                    // tir
    Mix_Chunk *Immhit;              // pointeur sur le sample audio joué lorsque le vaisseau de l'utilisateur
                                    // est touché
    Mix_Chunk * yoda ;              //pointeur sur le sample audio joué lorsque l'utilisateur gagne un niveau

     int command;                   // entier définissant si l'utilisateur joue avec l'accélérométre ou
                                    // la gestion du touch
     int music;                     // entier définissant les paramètres actuel définis par l'utilisateur
                                    // si la variable est égale à 0, Le son est désactivé
     int vibration;                 // entier définissant les paramètres actuel définis par l'utilisateur
                                    // si la variable est égale à 0, la vibration est désactivé
     int PreviousHighScore;         // Dernier high score enregistré
    int  saveNewHighScore;          // entier détermininant si le score doit être enregistré
                                    // Il est égale à 1 si une sauvegarde doit être faite

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

//Procédure d'initialisation du son
void initialisationSound( Game * game);

//Enumération de la force de vibration
enum RumbleForce {AUCUN,FAIBLE, MEDIUM_FORCE, FORT,MAXIMUM};
//Enumération de la longeur de la vibration
enum RumbleLength {INEXISTANT,COURT, MEDIUM_LENGTH, LONG};
//Fonction d'initialisation du jeu, prend en argument, la longueur,la largeur et les paramètres modifié par l'utilisateur
Game *  initialisationOfTheGame(int width,int height,char * nativeName,int command,int music, int vibration,int highScore);
//Procédure  s'occupant de géré les mouvements des éléments au sein du jeu
void  moveAllGame(Game * game, SDL_Renderer *renderer);

//Procédure s'occupant de déssinier les éléments au sein du jeu
void  drawGame(SDL_Renderer* renderer ,Game * game);

//Procédure permettant de créer une nouvelle escouade et de l'ajouter à la fin de la liste chainé
void  createNextSquadron(Game * game);
//Procédure permettant de retirer les escouades n'étant plus visibles
void  removeNotVisibleSquadronFromGame(Game * game);
//Procédure permettant de rajouter un énnemie à une escouade tout en évitant que plus énémies soit initialisé à la même position
void addNewEnemy(Game * game,Squadron * squadron,ListePosition * lp);
//Ajouter des énnemies selon la dernière position de ceux ci
void addEnemyFromHistory(Game * game);
//Fonction permettant d'obtenir la dernière escouade
Squadron * getLastSquadron(Game * game);
// Custom random
int my_rand();

//permettant de déterminer si  deux SDL_rectangle sont rentrée en collision
int checkCollision(SDL_Rect a, SDL_Rect b,int speed );
//   Gérer la collision entre le vaisseau de l'utilisateur et les tirs énnemies
void eventCheckCollisionUserShipEnnemyShoot(Game * game, SDL_Renderer *renderer);
// Gérer la collision entre le vaisseau de l'utilisateur et les vaisseaux énnemies
void eventCheckCollisionUserShipEnnemyShip(Game * game, SDL_Renderer *renderer);
void onDestroy(int posx, int posy, SDL_Renderer *renderer);
SpriteExplosion LoadSpriteForExplostion(int image, SDL_Renderer *renderer);


// Fonction générale de rendu de texture
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
// Fonction permettant de jouer la vibration
void playRumble(Game * game,enum RumbleForce force,enum RumbleLength length);
//jint Java_esgi_fouriam_SDLActivity_setPref(JNIEnv * env, jobject thiz, jstring name, jint commandValue, jint musicValue, jint vibrationValue, jint highScore);


//Fonction permettant d'enregistrer les highScore
void setHighScore(JNIEnv * env, jobject thiz, int score);
//Fonction permettant de jouer une musique
void playMusic(Mix_Music *mainMusic,int cntRepeat,Game * game);
//Fonction permettant de jouer un sample
void MyPlaySample(int channel,Mix_Chunk  * sample, int loop,int playMusic  );

//Procédure de filtrage de tir
void filterShootsFromGame(Game * game);
//Procédure d'incrémentation de la puissance du vaisseau de l'utilisateur
void IncrementPower(UserShip * ship );

//Procédure de décrémentation de la puissance du vaisseau de l'utilisateur
void decreasePower(UserShip * ship);



#endif /* game_h */
