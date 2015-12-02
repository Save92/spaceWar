//
//  shoot.c
//
//
//
//



#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include "shoot.h"
#include <jni.h>
#include <android/log.h>
#include <stdlib.h>
#include "constant.h"
#include "../enemy/enemy.h"
#include "CustomLog.h"

//DIRECTION SHOOT
#define DIRECTION_VERTICAL 0
#define DIRECTION_DIAGONALE_LEFT 1
#define DIRECTION_DIAGONALE_RIGHT 2
#define DIRECTION_DIAGONALE_SUB_LEFT 3
#define DIRECTION_DIAGONALE_SUB_RIGHT 4


//DAMAGE SHOOT
#define LOW_DAMAGE 0
#define MEDIUM DAMAGE 1

//SPEED SHOOT
#define SPEED_SHOOT 20

//SIZE SHOOT
#define WIDTH 5
#define HEIGHT 15



void drawMyShoot(SDL_Renderer* renderer , Shoot * shoot)
{
    customLog(0 , "SHOOT" ,  __func__);
    shoot->rectangle->x = shoot->posX;
    shoot->rectangle->y = shoot->posY;
    shoot->rectangle->w = WIDTH;
    shoot->rectangle->h = HEIGHT;
    SDL_SetRenderDrawColor(renderer, shoot->color[0], shoot->color[1], shoot->color[2], shoot->color[3]);
    SDL_RenderFillRect(renderer, (shoot->rectangle));
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
    
}

void moveMyShoot(Shoot * shoot ,int widthScreen , int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(shoot != NULL)
    {
        
        /*
         direction
         {
         0 : verticale
         1 : diagonale coin haut gauche
         2 : diagonale coin haut droit
         3 : diagonale haut gauche
         4 : diagonale haut droit
         5 : missile tête chercheuse
         }
         */
        switch(shoot->direction)
        {
            case DIRECTION_VERTICAL: moveVerticaly(shoot,widthScreen,heightScreen);
                break;
                
            case DIRECTION_DIAGONALE_LEFT: moveDiagonaleLeft(shoot,widthScreen,heightScreen);
                break;
                
            case DIRECTION_DIAGONALE_RIGHT: moveDiagonaleRight(shoot,widthScreen,heightScreen);
                break;
                
            case DIRECTION_DIAGONALE_SUB_LEFT: moveDiagonaleSubLeft(shoot,widthScreen,heightScreen);
                break;
                
            case DIRECTION_DIAGONALE_SUB_RIGHT: moveDiagonaleSubRight(shoot,widthScreen,heightScreen);
                break;
            default : moveVerticaly(shoot,widthScreen,heightScreen);
                break;
        }
    }
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
    
}

void moveVerticaly(Shoot * shoot,int widthScreen,int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(shoot != NULL)
    {
        shoot->posY = shoot->posY  + ( shoot->way * shoot->speed);
        setVisibility(shoot,widthScreen,heightScreen);
    }
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}

void moveDiagonaleLeft(Shoot * shoot,int widthScreen,int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(shoot != NULL)
    {
        shoot->posY = shoot->posY  + ( shoot->way * shoot->speed);
        if(shoot->cmptMoov%2 == 0)
        {
            shoot->posX = shoot->posX  + ( shoot->way * shoot->speed/2);
        }
        setVisibility(shoot,widthScreen,heightScreen);
    }
    shoot->cmptMoov++;
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}


void moveDiagonaleRight(Shoot * shoot,int widthScreen,int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(shoot != NULL)
    {
        shoot->posY = shoot->posY  + ( shoot->way * shoot->speed);
        if(shoot->cmptMoov%2 == 0){
            
            shoot->posX = shoot->posX  + ( (-shoot->way) * shoot->speed/2);
        }
        setVisibility(shoot,widthScreen,heightScreen);
    }
    shoot->cmptMoov++;
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}


void moveDiagonaleSubRight(Shoot * shoot,int widthScreen,int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(shoot != NULL)
    {
        shoot->posY = shoot->posY  + ( shoot->way * shoot->speed);
        if(shoot->cmptMoov%3 == 0){
            shoot->posX = shoot->posX  + ( (-shoot->way) * shoot->speed/2);
        }
        setVisibility(shoot,widthScreen,heightScreen);
    }
    shoot->cmptMoov++;
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}


void moveDiagonaleSubLeft(Shoot * shoot,int widthScreen,int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(shoot != NULL)
    {
        shoot->posY = shoot->posY  + ( shoot->way * shoot->speed);
        if(shoot->cmptMoov%3 == 0) {
            shoot->posX = shoot->posX  + ( shoot->way * shoot->speed);
        }
        setVisibility(shoot,widthScreen,heightScreen);
    }
    shoot->cmptMoov++;
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}



void setVisibility(Shoot * shoot,int widthScreen,int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(shoot != NULL)
    {
        //Si le tir sort de l'ecran
        if(shoot->posY < 0 || shoot->posY > heightScreen || shoot->posX < 0 || shoot->posX > widthScreen)
        {
            shoot->visible = INVISIBLE;
        }
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}

//Bouger toute une liste chainée
void moveAllMyShoots(ListShoot * listShoot ,int widthScreen , int heightScreen)
{
    customLog(0 , "SHOOT" ,  __func__);
    if((*listShoot).size > 0 && (*listShoot).start)
    {
        
        Shoot * nextShoot;
        nextShoot = (*listShoot).start;
        while(nextShoot)
        {
            //      __android_log_print(ANDROID_LOG_DEBUG, "moveVerticaly",  "Shoot adress :%d",  nextShoot);
            moveMyShoot(nextShoot,widthScreen,heightScreen);
            nextShoot = nextShoot->nextShoot;
            
        }
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
    
}
//Déssiner tout mes tirs
void drawAllMyShoots(SDL_Renderer* renderer , ListShoot * listShoot)
{
    customLog(0 , "SHOOT" ,  __func__);
    if(listShoot->size > 0)
    {
        Shoot * nextShoot = listShoot->start;
        while(nextShoot != NULL)
        {
            
            drawMyShoot(renderer,nextShoot);
            nextShoot = nextShoot->nextShoot;
        }
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}
//Filtrer les tirs
void filterMyShoots(ListShoot * listShoot)
{
    customLog(0 , "shoot" ,  __func__);
    Shoot  *tmp;
    Shoot  *previous;
    if(listShoot != NULL && listShoot->start != NULL)
    {
        previous = listShoot->start;
        //Si il n'existe qu'un seul tir
        if(previous->nextShoot == NULL)
        {
            if(previous->visible == INVISIBLE)
            {

                FreeMyShoot(listShoot->start);
                listShoot->start = NULL;
            }
        }
        else
        {
            tmp = previous;
            previous = NULL;
            //Parcours de la liste de tirs
            while(tmp != NULL)
            {
                //Si le tir est invisible
                if(tmp->visible == INVISIBLE)
                {
                    //selection du tir supprimé
                    Shoot * deletedShoot = tmp;
                    //On change l'index dans la liste
                    tmp = tmp->nextShoot;
                    if(previous == NULL)
                    {
                        //si on est au premier index, on relie prochaine élement à la suite de la liste
                        listShoot->start = tmp;
                    }
                    else
                    {
                        //sinon on relie le dernier élément au prochain tir
                        previous->nextShoot = tmp;
                    }
                    //libération du tir
                    FreeMyShoot(deletedShoot);
                    deletedShoot = NULL;
                    listShoot->size--;
                }
                else
                {
                    previous = tmp;
                    tmp= tmp->nextShoot;
                }
            }
        }
    }
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}

void myShipShoot(UserShip myShip,ListShoot * listShoot,int direction,int damage)
{
    customLog(0 , "shoot" ,  __func__);
    Shoot  *tmp;
    Shoot  *previous;
    addShoot(myShip.posX,myShip.posY,myShip.rectangle->w,myShip.rectangle->h,listShoot,direction,damage,-1,0,255,51, 255);
}


void EnemyShoot(EnemyShip enemy,ListShoot * listShoot,int direction,int damage)
{
    /***
     *
     *Couleur différente en fonction du type de l'ennemi
     ***/
    switch (enemy.type) {
        case 0 :
        
            addShoot(enemy.posX,enemy.posY,enemy.rectangle->w,enemy.rectangle->h,listShoot,direction,damage,1,255,51,0, 255);
            break;
        case 1 :
     
            addShoot(enemy.posX,enemy.posY,enemy.rectangle->w,enemy.rectangle->h,listShoot,direction,damage,1,51,51,255, 255);
            break;
        case 2 :
          
            addShoot(enemy.posX,enemy.posY,enemy.rectangle->w,enemy.rectangle->h,listShoot,direction,damage,1,153,0,255, 255);
            break;
        case 3 :
     
            addShoot(enemy.posX,enemy.posY,enemy.rectangle->w,enemy.rectangle->h,listShoot,direction,damage,1,255,255,0, 255);
            break;
    }
}

//Ajout d'un tir dans une liste
void addShoot(int posX,int posY , int width , int height , ListShoot * listShoot, int direction, int damage,signed int way,int color1,int color2,int color3, int transparence )
{
    customLog(0 , "shoot" ,  __func__);
    //__android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "EnemyShipShoot");
    int cnt = 0;
    Shoot * nextShoot = malloc(sizeof(Shoot));
    (*nextShoot).posX = posX + (width/2);
    //TIR ENEMIE
    if(way == -1 )
        (*nextShoot).posY = posY  ;
    else
        (*nextShoot).posY = posY + height;
    (*nextShoot).speed = SPEED_SHOOT;
    //Tableau de couleur
    (*nextShoot).color[0] = color1%256;
    (*nextShoot).color[1] = color2%256;
    (*nextShoot).color[2] = color3%256;
    (*nextShoot).color[3] = transparence%256;
    (*nextShoot).rectangle = malloc( sizeof(SDL_Rect));
    (*nextShoot).visible = 1;
    (*nextShoot).direction = direction;
    (*nextShoot).damage = damage;
    (*nextShoot).cmptMoov = 0;
    (*nextShoot).way = way;
    
    //on met le tir a la fin de la liste
    if(listShoot->size > 0 && (*listShoot).start != NULL)
    {
        Shoot * previousShoot;
        Shoot * lastShoot ;
        lastShoot = (*listShoot).start;
        while(lastShoot != NULL)
        {
            previousShoot = lastShoot;
            lastShoot = (*lastShoot).nextShoot;
        }
        nextShoot->nextShoot = NULL;
        previousShoot->nextShoot = nextShoot;
        
    }
    else
    {
        (*listShoot).start = nextShoot;
        (*listShoot).start->nextShoot = NULL;
    }
    (*listShoot).size =  (*listShoot).size +1;
    char * str = malloc(sizeof(char)* 255) ;
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}




//Libération de la mémoire lié au tir
void FreeMyShoot(Shoot * shoot)
{
    customLog(0 , "shoot" ,  __func__);
    free(shoot->rectangle);
    // __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "Free1"  );
    free(shoot);
    char * str = malloc(sizeof(char)* 255) ;
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
}


//Si le vaisseau de l'utilisateur tir
void UserShipShoot(UserShip myShip,ListShoot * listShoot)
{
    customLog(0 , "shoot" ,  __func__);
    switch (myShip.shotLevel)
    {
        case 1: myShipShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            break;
        case 2: myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            break;
            
        case 3: myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            
            break;
            
        case 4 :
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_LEFT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_RIGHT,LOW_DAMAGE);
            break;
            
        case 5 :
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_LEFT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_RIGHT,LOW_DAMAGE);
            myShipShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            
        default: myShipShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            break;
    }
    char * str = malloc(sizeof(char)* 255) ;
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}

//Si le vaisseau ennemi tir
void EnemyShipShoot(EnemyShip myShip,ListShoot * listShoot)
{
    customLog(0 , "shoot" ,  __func__);
    switch (myShip.shotLevel)
    {
        case 1: EnemyShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            break;
        case 2: EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            break;
            
        case 3: EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            
            break;
            
        case 4 :
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_LEFT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_RIGHT,LOW_DAMAGE);
            break;
            
        case 5 :
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_LEFT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_RIGHT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_LEFT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_DIAGONALE_SUB_RIGHT,LOW_DAMAGE);
            EnemyShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            
        default: EnemyShoot(myShip,listShoot,DIRECTION_VERTICAL,LOW_DAMAGE);
            break;
    }
    char * str = malloc(sizeof(char)* 255) ;
    sprintf(str,"end %s",__func__);
    customLog(0 , "SHOOT" , str);
    free(str);
}







