//
//  shoot.h
//  
//
//
//

#ifndef ____shoot__
#define ____shoot__

#include <stdio.h>
#include "../user/userShip.h"
#include "../enemy/enemy.h"
#include "../general/drawer.h"


//Structure de tir
typedef struct Shoot Shoot;
struct Shoot
{
    int posX;               //Position EN X
    int posY;               //Position en Y
    int speed;              //Vitesse du tir
    int color[4];           //Tableau de couleur
    int visible;            //Visibilité du tir
    int type ;              //Type de tir
    SDL_Rect *rectangle;    //Rectangle de rendu du tir
    Shoot * nextShoot ;     //Prochain tir
    int direction ;         //Direction du tir
    int damage ;            //Dommmage du tir
    int cmptMoov ;          //Nombre de mouvement
    signed int way;         //Tir ami  ou ennemi  -1 pour tir du vaisseau et 1 pour les tirs des énnemis

};


/*
 direction :
 0 : verticale
 1 : diagonale coin haut gauche
 2 : diagonale coin haut droit
 3 : diagonale haut gauche
 4 : diagonale haut droit
 5 : missile tête chercheuse
 */

//Liste de tir
typedef struct ListShoot{
    
    Shoot * start;
    int size;
} ListShoot;

//déssiner mon tir
void drawMyShoot(SDL_Renderer* renderer , Shoot * listShoot);
//Déssiner mes tirs
void drawAllMyShoots(SDL_Renderer* renderer , ListShoot * shoot);
//bouger mon tir
void moveMyShoot(Shoot * shoot ,int widthScreen , int heightScreen);
//bouger mon tir verticallement
void moveVerticaly(Shoot * shoot,int widthScreen,int heightScreen);
//bouger mon tir sur la diagonale gauche
void moveDiagonaleLeft(Shoot * shoot,int widthScreen,int heightScreen);
//bouger mon tir sur la diagonale droite
void moveDiagonaleRight(Shoot * shoot,int widthScreen,int heightScreen);
//bouger mon tir sur la sous diagonale droite
void moveDiagonaleSubRight(Shoot * shoot,int widthScreen,int heightScreen);
//bouger mon tir sur la sous diagonale gauche
void moveDiagonaleSubLeft(Shoot * shoot,int widthScreen,int heightScreen);
//bouger tous les tirs
void moveAllMyShoots(ListShoot * listShoot,int widthScreen,int heightScreen);



//Définir la visiblité du tir
void setVisibility(Shoot * shoot,int widthScreen,int heightScreen);
//Filtrer les tirs dans une liste
void filterMyShoots(ListShoot * listShoot);
//Libérer un tir d'un mémoire
void FreeMyShoot(Shoot * shoot);
//Le vaisseau de l'utilisateur tir
void myShipShoot(UserShip myShip,ListShoot * listShoot,int direction,int damage);
//Le vaisseau enemi tir
void EnemyShoot(EnemyShip enemy,ListShoot * listShoot,int direction,int damage);
//Fonction général de tir de l'utilisateur
void UserShipShoot(UserShip myShip,ListShoot * listShoot);
//Fonction général de tir de l'ennemie
void EnemyShipShoot(EnemyShip myShip,ListShoot * listShoot);
//Ajout d'un tir à la liste ;
void addShoot(int posX,int posY , int width , int height , ListShoot * listShoot, int direction, int damage,int way,int color1,int color2,int color3, int transparence );






#endif /* defined(____shoot__) */
