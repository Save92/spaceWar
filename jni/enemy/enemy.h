//
//  enemy.h
//  
//
//
//

#ifndef enemy_h
#define enemy_h

#include <stdio.h>
#include "./movementScheme.h"
#include "SDL.h"
#include "../general/drawer.h"
typedef struct EnemyShip EnemyShip;
struct EnemyShip
{
    int posX;           //Pos en X
    int posY;           //position en Y
    float speed;        //vitesse du vaisseau
    int life;           // La vie du vaisseau
    int color[4];       // couleur des ennemies
    SDL_Rect *rectangle;// lié au rectangle
    int shotLevel;      //puissance de tir
    int typeShip;       //type de vaisseau
    int bonus;          //Si le vaisseau
    int cntFootStep;    //nombre de pas
    MovementScheme * movementScheme;    //Type de mouvement
    int type;
    int typeMovement;   //type de mouvement
    int repeatMovement; //Booleen pour déterminer si le vaisseau répéte plusieur fois le même mouvement
    int visible;        //Booléen sur la visibilité de l'énnemi
    int frequencyOfShoot;   //Fréquence de tir
    int verticalSide;       //Coté vertical sur lequel est l'ennemi actuellement
    int width;              //longueur
    int height;             //largeur du vaisseau
    int changeDirection;    //Change la direction du vaisseau ennemy
    Sprite enemySprite;     //Sprite ennemy
    
    EnemyShip * nextEnemyShip;
};



//Déssiner le vaisseau ennemi
void drawEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip);
//bouger le vaisseau ennemi
int moveEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen);
//libérer le vaisseau en mémoire
void freeEnemyShip(EnemyShip * enemyShip);
//initialisation du vaisseau enemie
EnemyShip * initialisationEnemyShip(int width,int height,int typeStart,int side,int distance,int verticalLine,int typeShip,int typeMovement,int shotLevel);
//vérification de si le vaisseau de l'utilisateur peut tirer
int canShoot(EnemyShip * enemyShip);
//Définis la visiblité de l'ennemie
void setVisibilityEnemy(EnemyShip * enemyShip,int widthScreen,int heightScreen);
//Bouge le vaisseau verticallement
void moveEnemyShipVertically(EnemyShip * enemyShip,int widthScreen,int heightScreen);
//Bouger le vaisseau en ZigEag
void moveEnemyShipZigZag(EnemyShip * enemyShip,int widthScreen,int heightScreen);
//Vérifier de quel coté est le vaisseau
void verifySideFromVerticalLine(EnemyShip * enemyShip);
//Vérifie si  le vaisseau ennemy est en vie
int enemyShipIsAlive(EnemyShip * enemyShip);
//Met le vaisseau en Invisible
void setEnemyToInvisible(EnemyShip * enemy);
//Initialise la position du vaisseau selon des positions de départs
void initialisationTypeStart(int width,int height,EnemyShip * enemyShip,int typeStart,int side,int defaultGap);






#endif /* enemy_h */
