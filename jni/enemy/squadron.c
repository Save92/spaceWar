//
//  squadron.c
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#include "squadron.h"
#include <stdio.h>
#include "../SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include "enemy.h"
#include <android/log.h>
#include "../general/constant.h"

Squadron * initialisationSquadron(int maxSize)
{
 //   __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "initialisationSquadron"  );
    Squadron * squadron = malloc(sizeof(Squadron));
    squadron->size = 0;
    squadron->maxSize = maxSize;
    squadron->appearNext = FALSE;
    squadron->visible = VISIBLE;
  //   __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "END initialisationSquadron"  );
    squadron->nextEnemyShip = NULL;
    squadron->nextSquadron = NULL;
    squadron->checkForNext = FALSE;
    return squadron;
}


void addEnemyToSquadron(EnemyShip * enemy,Squadron * squadron)
{
 //   __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "AddEnemy "  );
    if(squadron->size < squadron->maxSize)
    {
        if(squadron->size == 0)
        {
    //        __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "add in empty squadron"  );
            squadron->nextEnemyShip = enemy;
            
        }
        else
        {
            EnemyShip * lastEnemy = getlastEnemyShip(squadron);
            lastEnemy->nextEnemyShip = enemy;
            
        }
        squadron->size++;
    }
 //   __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "END AddEnemy "  );
}

void removeNotVisibleEnemy(Squadron * squadron)
{
    if(allVisible(squadron) == 0)
    {
        EnemyShip  *tmp;
        EnemyShip  *previous;
        __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG1"  );
        if(squadron != NULL && squadron->nextEnemyShip != NULL)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG2"  );
            previous = squadron->nextEnemyShip;
            if(previous->nextEnemyShip == NULL)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG3"  );
                if(previous->visible == INVISIBLE)
                {
                    __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG4"  );
                    freeEnemyShip(squadron->nextEnemyShip);
                    squadron->nextEnemyShip = NULL;
                }
            }
            else
            {
                __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG5"  );
                tmp = previous;
                previous = NULL;
                
                while(tmp != NULL)
                {
                    __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG6"  );
                    if(tmp->visible == INVISIBLE)
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG7"  );
                        EnemyShip * deletedEnemy = tmp;
                        
                        tmp = tmp->nextEnemyShip;
                        if(previous == NULL)
                        {
                            __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG8"  );
                            squadron->nextEnemyShip = tmp;
                        }
                        else
                        {
                            previous->nextEnemyShip = tmp;
                        }
                        freeEnemyShip(deletedEnemy);
                        deletedEnemy = NULL;
                        squadron->size--;
                    }
                    else
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip",   "FLAG9"  );
                        previous = tmp;
                        tmp= tmp->nextEnemyShip;
                    }
                }
            }
        }
    }

}


void moveSquadron(Squadron * squadron,int width,int height)
{
    
    if((*squadron).size > 0 && (*squadron).nextEnemyShip)
    {
        
        EnemyShip * enemy;
        enemy = (*squadron).nextEnemyShip;
        while(enemy)
        {
      //      __android_log_print(ANDROID_LOG_DEBUG, "Squadron",  "Shoot enemy :%d",  enemy);
            moveEnemyShip(enemy,width, height);      
            enemy = enemy->nextEnemyShip;
        }
    }
    changeAppearNext(squadron,height);
    
}


void drawMySquadron(SDL_Renderer* renderer , Squadron * squadron)
{
    if((*squadron).size > 0 && (*squadron).nextEnemyShip)
    {
        
        EnemyShip * enemy;
        enemy = (*squadron).nextEnemyShip;
        while(enemy)
        {
      //      __android_log_print(ANDROID_LOG_DEBUG, "Squadron",  " draw enemy adress :%d",  enemy);
            drawEnemyShip(renderer , enemy);
            
            enemy = enemy->nextEnemyShip;
        }
    }
    
    
    
}



int allVisible(Squadron * squadron)
{
     __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "AllVisible"  );
    if(squadron->size > 0 && squadron->nextEnemyShip)
    {
        
        EnemyShip * enemy;
        enemy = squadron->nextEnemyShip;


        while(enemy)
        {
            if(enemy->visible == INVISIBLE)
            {
                 __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "enemy not visible"  );
                return FALSE;
            }
            enemy = enemy->nextEnemyShip;
            __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "AllVisible FL3"   );
        }
        return TRUE;
    }

    return FALSE;
}

void changeAppearNext(Squadron * squadron,int height)
{
    if(squadron->appearNext == FALSE)
    {
        if(squadron->size > 0)
        {
            EnemyShip * enemy;
            enemy = squadron->nextEnemyShip;
            while(enemy)
            {
                if(enemy->posY > height/2)
                {
                    squadron->appearNext = TRUE;
                }
                enemy = enemy->nextEnemyShip;
            }
        }
        else
        {
            squadron->appearNext = TRUE;
        }
    }
}

int sendNextSquadron(Squadron * squadron,int width,int height)
{
     __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "sendNextSquadron"  );
     __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "squadron->appearNext %d" ,squadron->appearNext );
    __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "squadron->checkForNext %d" ,squadron->checkForNext );
    if(squadron->appearNext == TRUE && squadron->checkForNext == FALSE )
    {
        squadron->checkForNext == TRUE;
        __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "sendNextSquadron Return True"  );
        return TRUE;
    }
    __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "sendNextSquadron Return FALSE"  );
    return FALSE;

}

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


void freeSquadron(Squadron * squadron)
{
    free(squadron);
}