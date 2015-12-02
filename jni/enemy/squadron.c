//
//  squadron.c
//
//
//
//

#include "squadron.h"
#include <stdio.h>
#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include "enemy.h"
#include <android/log.h>
#include "../general/constant.h"
#include "../general/CustomLog.h"


Squadron * initialisationSquadron(int maxSize)
{
    
    Squadron * squadron = malloc(sizeof(Squadron));
    squadron->size = 0;
    squadron->maxSize = maxSize;
    
    squadron->visible = VISIBLE;
    
    squadron->nextEnemyShip = NULL;
    squadron->nextSquadron = NULL;
    return squadron;
}


void addEnemyToSquadron(EnemyShip * enemy,Squadron * squadron)
{
    
    
    
    if( enemy && squadron->size < squadron->maxSize)
    {
        if(squadron->size == 0)
        {
            squadron->nextEnemyShip = enemy;
        }
        else
        {
            EnemyShip * lastEnemy = getlastEnemyShip(squadron);
            lastEnemy->nextEnemyShip = enemy;
        }
        enemy->nextEnemyShip = NULL;
        squadron->size++;
    }
    
}

void removeNotVisibleEnemy(Squadron * squadron)
{
    customLog(1 , "SQUADRON" ,  __func__);
    EnemyShip  *tmp;
    EnemyShip  *previous;
    if(squadron != NULL && squadron->nextEnemyShip != NULL && squadron->size > 0 )
    {
        previous = squadron->nextEnemyShip;
        //Si il n y q'un vaisseau
        if(previous->nextEnemyShip == NULL)
        {
            if(previous->visible == INVISIBLE)
            {
                freeEnemyShip(squadron->nextEnemyShip);
                squadron->nextEnemyShip = NULL;
                squadron->size--;
            }
        }
        else
        {
            tmp = previous;
            previous = NULL;
            int cnt = 0;
            
            while(tmp != NULL )
            {
                //Si le vaisseau est Invisible
                if(tmp->visible == INVISIBLE)
                {
                    //On récupére le vaisseau a supprimer
                    EnemyShip * deletedEnemy = tmp;
                    //On change l'index du pointeur
                    tmp = tmp->nextEnemyShip;
                    if(previous == NULL)
                    {
                        //le vaisseau  est le 1er vaisseau de la liste
                        squadron->nextEnemyShip = tmp;
                    }
                    else
                    {
                        previous->nextEnemyShip = tmp;
                    }
                    //On libére le vaisseau
                    freeEnemyShip(deletedEnemy);
                    deletedEnemy = NULL;
                    squadron->size--;
                    
                }
                else
                {
                    previous = tmp;
                    tmp= tmp->nextEnemyShip;
                }
            }
            if(previous)
                previous->nextEnemyShip = NULL;
        }
    }
    
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SQUADRON" , str);
    free(str);
}

//Bouger l'escouade
void moveSquadron(Squadron * squadron,int width,int height, ListShoot * listShootEnnemy , Mix_Chunk * tie_shoot,int playMusic)
{
 
    customLog(1 , "SQUADRON" ,  __func__);
    if(squadron && (*squadron).size > 0 && (*squadron).nextEnemyShip)
    {
        
       
        EnemyShip * enemy;
        enemy = (*squadron).nextEnemyShip;
        while(enemy)
        {
                       moveEnemyShip(enemy,width, height);
            if(canShoot(enemy))
            {
                EnemyShipShoot(*enemy,listShootEnnemy);
                MyPlaySample(-1, tie_shoot, 0 ,playMusic);
            }
            enemy = enemy->nextEnemyShip;
        }
    }

    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SQUADRON" , str);
    free(str);
    
}
//Déssiner les escouades
void drawMySquadron(SDL_Renderer* renderer , Squadron * squadron)
{
    customLog(1 , "SQUADRON" ,  __func__);
    if(squadron && (*squadron).size > 0 && (*squadron).nextEnemyShip)
    {
        
        EnemyShip * enemy;
        enemy = (*squadron).nextEnemyShip;
        while(enemy)
        {
            
            drawEnemyShip(renderer , enemy);
            
            enemy = enemy->nextEnemyShip;
        }
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "SQUADRON" , str);
    free(str);
    
}


//Définis si tout les vaisseau de l'escouade sont visible
int allVisible(Squadron * squadron)
{

    if(squadron->size > 0 && squadron->nextEnemyShip)
    {
        
        EnemyShip * enemy;
        enemy = squadron->nextEnemyShip;
        while(enemy)
        {
            if(enemy->visible == INVISIBLE)
            {
                return FALSE;
            }
            enemy = enemy->nextEnemyShip;
        }
        return TRUE;
    }
    
    return FALSE;
}

//Définis la visibilité du vaisseau
void setVisibilitySquadron(Squadron * squadron)
{
    if(squadron->size <= 0)
    {
        squadron->visible = INVISIBLE;
    }
}



//Récupérer le dernier vaisseau ennemie d'une escouade
EnemyShip * getlastEnemyShip(Squadron * squadron)
{
    //  __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "getlastEnemyShip"  );
    EnemyShip * indexShip = squadron->nextEnemyShip;
    EnemyShip * tempShip = indexShip;
    if(squadron->size > 0)
    {
        while(tempShip)
        {
            indexShip = tempShip;
            tempShip = tempShip->nextEnemyShip;
        }
    }
    //  __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "END getlastEnemyShip"  );
    return indexShip;
}

//Libérer l'escouade
void freeSquadron(Squadron * squadron)
{
    
    customLog(1 , "SHOOT" , __func__);
    
    
    EnemyShip * indexShip = squadron->nextEnemyShip;
    EnemyShip * nextEnemyShip;
    while(indexShip)
    {
        nextEnemyShip = indexShip->nextEnemyShip;
        freeEnemyShip(indexShip);
        indexShip = nextEnemyShip;
    }
    free(squadron);
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(1 , "SHOOT" , str);
    free(str);
}