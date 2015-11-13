//
//  game.c
//  
//
//  Created by thierry allard saint albin on 01/11/2015.
//
//

#include "game.h"
#include <time.h>
#include "../enemy/positionHistory.h"
#include "../SDL/src/core/android/SDL_android.h"
#include <android/log.h>
#include "constant.h"

# define SizeName  128
# define MaxEnemy 4

Game *  initialisationOfTheGame(int width,int height)
{
    Game * game = malloc(sizeof(Game));
    game->size = 0;
    game->score = 0;
    game->level = 1;
    game->width = width;
    game->height = height;
    game->nameUser = malloc( SizeName * sizeof(char));
    strcpy(game->nameUser, "AAAA");
    game->history = 0;
    game->cntInLastSquadron = 0;
    game->stack = initializeStackHistory();
    return game;
}


void  moveAllGame(Game * game)
{
    __android_log_print(ANDROID_LOG_DEBUG, "GAME", "moveAllGame ");
    if(game->size == 0)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME", "emptyGame ");
        createNextSquadron(game);
    }
    else
    {
        Squadron *tmp = game->nextSquadron;
        int size = game->size;
        int index = 0;
        while(tmp && index < size)
        {
            if(sendNextSquadron(tmp,game->width,game->height) == 1)
            {
                createNextSquadron(game);
            }
            tmp= tmp->nextSquadron;
            index++;
        }
    }
    
    Squadron *tmp =  game->nextSquadron;
    while(tmp)
    {
        moveSquadron(tmp,game->width,game->height);
        tmp= tmp->nextSquadron;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "GAME", "END moveAllGame ");
    
}


void  drawGame(SDL_Renderer* renderer ,Game * game)
{
     __android_log_print(ANDROID_LOG_DEBUG, "GAME", "drawGame ");
    if(game->size > 0)
    {
        Squadron * squadron;
        squadron = game->nextSquadron;
        while(squadron)
        {
            drawMySquadron(renderer,squadron);
            squadron = squadron->nextSquadron;
        }
    }
    __android_log_print(ANDROID_LOG_DEBUG, "GAME", "END drawGame ");
}


void  removeNotVisibleEnemyFromGame(Game * game)
{
    if(game->size > 0)
    {
        Squadron * squadron;
        squadron = game->nextSquadron;
        while(squadron)
        {
            removeNotVisibleEnemy(squadron);
            if(squadron->size == 0)
            {
                squadron->visible = 0;
            }
            squadron = squadron->nextSquadron;
        }
    }
}


void removeNotVisibleSquadronFromGame(Game * game)
{
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "removeNotVisibleSquadronFromGame"  );
    Squadron  *tmp;
    Squadron  *previous;
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG1"  );
    if(game != NULL && game->nextSquadron != NULL)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG2"  );
        previous = game->nextSquadron;
        if(previous->nextSquadron == NULL)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG3"  );
            if(previous->visible == 0)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG4"  );
                freeSquadron(game->nextSquadron);
                game->nextSquadron = NULL;
            }
        }
        else
        {
            __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG5"  );
            tmp = previous;
            previous = NULL;
            
            while(tmp != NULL)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG6"  );
                if(tmp->visible == 0)
                {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG7"  );
                    Squadron * deletedSquadron = tmp;
                    
                    tmp = tmp->nextSquadron;
                    if(previous == NULL)
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG8"  );
                        game->nextSquadron = tmp;
                    }
                    else
                    {
                        previous->nextSquadron = tmp;
                    }
                    freeSquadron(deletedSquadron);
                    deletedSquadron = NULL;
                    game->size--;
                }
                else
                {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG9"  );
                    previous = tmp;
                    tmp= tmp->nextSquadron;
                }
            }
        }
    }
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END removeNotVisibleSquadronFromGame"  );
}

void  createNextSquadron(Game * game)
{
     __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "START createNextSquadron"  );
    
    if(game->stack->size == 0 || game->stack->size %2 == 0)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "PAIRE"  );
        int nombre_aleatoire = 0;
        nombre_aleatoire = rand();
        int nbrEnnemy =nombre_aleatoire % MaxEnemy;
        if(nbrEnnemy == 0)
            nbrEnnemy++;
       
        int n = 0;
        int side = 1;
        Squadron * squad;
        if(game->size != 0)
        {
            Squadron * tmpSquad = getLastSquadron(game);
            tmpSquad->nextSquadron = initialisationSquadron(nbrEnnemy);
            squad = tmpSquad->nextSquadron;
        }
        else
        {
            game->nextSquadron = initialisationSquadron(nbrEnnemy);
            squad = game->nextSquadron;
        }
        for(n = 0 ; n < nbrEnnemy ; n++)
        {
            addNewEnemy(game,squad);
        }
        
         game->cntInLastSquadron = nbrEnnemy;
    }
    else
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "IMPAIRE"  );
        addEnemyFromHistory(game);
    }
    game->size++;
}

void addNewEnemy(Game * game,Squadron * squadron)
{
     __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "addNewEnemy"  );
    int side = 0;
    int posStart = rand()% MaxEnemy; //A modifier pour mettre probabilité par lot (Loto)
    
    int tempDividendeDistance = rand() % MaxEnemy ;
    if(tempDividendeDistance == 0)
        tempDividendeDistance++;
    
    int distance = game->width/tempDividendeDistance ;
    int dividende = rand() % 8;
    if(dividende == 0)
        dividende++;
    int verticalLine = game->width/dividende;
    if(rand()%2 == 0)
    {
        side = 1;
        int verticalLine = game->width - verticalLine;
    }
    else
    {
        side = -1;
    }
    
    int typeShip = 0;
    int typeMovement = rand()%2;

    EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,posStart, side,distance,verticalLine,typeShip,typeMovement);
    History *history =  initializeHistory(posStart,side,distance ,verticalLine,typeShip,typeMovement);
    addHistory(history,game->stack);
    
    addEnemyToSquadron(enemy,squadron);
    
     __android_log_print(ANDROID_LOG_DEBUG, "GAME", "End addEnemy");
    game->history++;


}


void addEnemyFromHistory(Game * game)
{
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "addEnemyFromHistory"  );
    
    
    int nombre = game->cntInLastSquadron;
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "cnt in lastSquadron %d",nombre);
    StackHistory * tempStack=getHeads(game->stack,nombre);
    History * tmp = tempStack->head;
    Squadron * lastSqdr = getLastSquadron(game);
    
    lastSqdr->nextSquadron = initialisationSquadron(nombre);
    while(tmp != NULL )
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "history address %d",tmp);
        EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,tmp->LastPosStart, (-1)*tmp->LastSide,tmp->LastDistance,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement);
        
        History *history =  initializeHistory(tmp->LastPosStart,(-1)* (tmp->LastSide),tmp->LastDistance ,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement);
        
        addEnemyToSquadron(enemy,lastSqdr->nextSquadron);
        
        addHistory(history,game->stack);
        tmp = tmp->nextHistory;
        game->history++;
        
    }
      __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END addEnemyFromHistory"  );
}

Squadron * getLastSquadron(Game * game)
{
     __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "getLastSquadron"  );
    Squadron * indexSquadron = game->nextSquadron;
    if(game->size == 0)
    {
        return indexSquadron;
    }
    else
    {
        indexSquadron = game->nextSquadron;
        Squadron *tmp = indexSquadron;
        while(tmp)
        {
            indexSquadron = tmp;
            tmp = tmp->nextSquadron;
        }
    }
     __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END getLastSquadron"  );
    return indexSquadron;
}





