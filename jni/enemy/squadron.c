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
       // __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG1"  );
        if(squadron != NULL && squadron->nextEnemyShip != NULL)
        {
           // __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG2"  );
            previous = squadron->nextEnemyShip;
            if(previous->nextEnemyShip == NULL)
            {
              //  __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG3"  );
                if(previous->visible == INVISIBLE)
                {
                 //   __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG4"  );
                    freeEnemyShip(squadron->nextEnemyShip);
                    squadron->nextEnemyShip = NULL;
                }
            }
            else
            {
              //  __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG5"  );
                tmp = previous;
                previous = NULL;
                
                while(tmp != NULL)
                {
               //     __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG6"  );
                    if(tmp->visible == INVISIBLE)
                    {
              //          __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG7"  );
                        EnemyShip * deletedEnemy = tmp;
                        
                        tmp = tmp->nextEnemyShip;
                        if(previous == NULL)
                        {
             //               __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG8"  );
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
            //            __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "FLAG9"  );
                        previous = tmp;
                        tmp= tmp->nextEnemyShip;
                    }
                }
                previous->nextEnemyShip = NULL;
            }
        }
    }
}


void moveSquadron(Squadron * squadron,int width,int height, ListShoot * listShootEnnemy)
{
    
    if((*squadron).size > 0 && (*squadron).nextEnemyShip)
    {
        
        EnemyShip * enemy;
        enemy = (*squadron).nextEnemyShip;
        while(enemy)
        {
      //      __android_log_print(ANDROID_LOG_DEBUG, "Squadron",  "Shoot enemy :%d",  enemy);
            moveEnemyShip(enemy,width, height);
            if(canShoot(enemy))
            {
                EnemyShipShoot(*enemy,listShootEnnemy);
            }
            enemy = enemy->nextEnemyShip;
        }
    }
    changeAppearNext(squadron,height);
   // __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "before setVisibilitySquadron"   );
    setVisibilitySquadron(squadron);
    
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
   //  __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "AllVisible"  );
    if(squadron->size > 0 && squadron->nextEnemyShip)
    {
        
        EnemyShip * enemy;
        enemy = squadron->nextEnemyShip;


        while(enemy)
        {
            if(enemy->visible == INVISIBLE)
            {
         //        __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "enemy not visible"  );
                return FALSE;
            }
            enemy = enemy->nextEnemyShip;
            //    __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "AllVisible FL3"   );
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

void setVisibilitySquadron(Squadron * squadron)
{
   // __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron FL1"   );
    if(squadron && squadron->nextEnemyShip)
    {
     //    __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron FL2"   );
        EnemyShip * tempShip = squadron->nextEnemyShip;
        int allVisible = VISIBLE;
        if(squadron->size > 0)
        {
       //      __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron FL3"   );
            while(tempShip != NULL)
            {
        //        __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron FL4"   );
                if(tempShip->visible == INVISIBLE )
                {
                    allVisible = INVISIBLE;
                }
                tempShip = tempShip->nextEnemyShip;
       //         __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron FL5"   );
        //         __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron %d",tempShip);
            }
            
            if(allVisible == INVISIBLE)
            {

                squadron->visible = INVISIBLE;
      //          __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron FL6"   );
            }
        }
        else
        {
            squadron->visible = INVISIBLE;
     //       __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "setVisibilitySquadron FL7"   );
        }
    }
}


int sendNextSquadron(Squadron * squadron,int width,int height)
{
  //   __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "sendNextSquadron"  );
  //   __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "squadron->appearNext %d" ,squadron->appearNext );
  //  __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "squadron->checkForNext %d" ,squadron->checkForNext );
    if(squadron->appearNext == TRUE && squadron->checkForNext == FALSE )
    {
        squadron->checkForNext == TRUE;
       // __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "sendNextSquadron Return True"  );
        return TRUE;
    }
   // __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "sendNextSquadron Return FALSE"  );
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
  //  __android_log_print(ANDROID_LOG_DEBUG, "Squadron",   "freeSquadron"  );
    
    EnemyShip * indexShip = squadron->nextEnemyShip;
    EnemyShip * nextEnemyShip;
    while(indexShip)
    {
        nextEnemyShip = indexShip->nextEnemyShip;
        freeEnemyShip(indexShip);
        indexShip = nextEnemyShip;
    }
    free(squadron);
}