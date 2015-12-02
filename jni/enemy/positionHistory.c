//
//  positionHistory.c
//
//
//
//

#include "positionHistory.h"
#include "../SDL/src/core/android/SDL_android.h"
#include <android/log.h>
#include "./movementConstant.h"
#include <math.h>

const  signed int side[] = { 1, -1};
const  signed int position[] = { TOP_SCREEN, TOP_SIDE_SCREEN,TOP_MIDDLE_SIDE_SCREEN,TOP_EXTREME_SIDE_SCREEN,EXTREME_SIDE_SCREEN};
//Ajout d'une historique à la pile d'histoire
void addHistory(History * history,StackHistory * stackHistory)
{
    if(stackHistory->size == 0)
    {
        stackHistory->head = history;
    }
    else
    {
        history->nextHistory = stackHistory->head;
        stackHistory->head = history;
    }
    stackHistory->size++;
}

//Récupréation des n élement dans la piles
StackHistory  * getHeads(StackHistory * stackHistory,int n)
{
    
    int i = 0 ;
    StackHistory * stackCopy = initializeStackHistory();
    stackCopy->size = 0;
    
    History * tmp;
    History * indexNewStack;
    History * previousIndexNewStack;
    
    if(stackHistory->size > 0)
    {
        
        return stackCopy;
    }
    else
    {
        tmp = stackHistory->head;
        
        indexNewStack = stackCopy->head;
        
        
        while( tmp && i<n)
        {
            indexNewStack = copyHistory(*tmp);
            tmp = tmp->nextHistory;
            previousIndexNewStack = indexNewStack;
            indexNewStack = indexNewStack->nextHistory;
            i++;
        }
        if(previousIndexNewStack)
            previousIndexNewStack->nextHistory = NULL;
    }
    return stackCopy;
}


//Copie d'un historique
History * copyHistory(History history)
{
    
    History * copyHistory = initializeHistory(history.LastPosStart,history.LastSide,history.LastDistance,history.LastverticalLine,history.LastypeShip,history.LastTypeMovement,history.LastShotLevel);
    
    return copyHistory;
}
//Initialisation d'une pile d'historique
StackHistory * initializeStackHistory()
{
    
    StackHistory * stack = malloc(sizeof(StackHistory));
    stack->size = 0;
    stack->head = NULL;
    
    return stack;
}

//Initialisation d'un historique
History * initializeHistory(int LastPosStart,int  LastSide,int  LastDistance,int  LastverticalLine,int  LastypeShip,int  LastTypeMovement,int shotLevel)
{
    //   __android_log_print(ANDROID_LOG_DEBUG, "History",   "initializeHistory"  );
    History * newHistory = malloc(sizeof(History));
    newHistory->LastPosStart = LastPosStart;
    newHistory->LastSide = LastSide;
    newHistory->LastDistance = LastDistance;
    newHistory->LastverticalLine = LastverticalLine;
    newHistory->LastypeShip = LastypeShip;
    newHistory->LastTypeMovement = LastTypeMovement;
    newHistory->LastShotLevel = shotLevel;
    newHistory->nextHistory = NULL;
    //   __android_log_print(ANDROID_LOG_DEBUG, "History",   "END initializeHistory"  );
    return newHistory;
}


//Initialisation d'une liste liste de poisition
ListePosition * initializeListePosition()
{
    
    ListePosition * liste = malloc(sizeof(ListePosition));
    liste->size = 0;
    
    //Il existe 5 positions sur 1 coté de l'écran
    int lengthPosition = 5;
    int lengthSide = 2;
    
    int indexPosition = 0;
    int indexSide = 0;
    
    Position * tmp = liste->startPosition;
    //Une position est définies selon un coté et une position
    int index = 0;
    for(indexPosition = 0; indexPosition < lengthPosition; indexPosition++)
    {
        for(indexSide = 0 ; indexSide < lengthSide ; indexSide++)
        {
            
            
            Position * p = malloc(sizeof(Position));
            p->position = position[indexPosition];
            p->side = side[indexSide];
            p->nextPosition = NULL;
            
            if(index == 0)
            {
                liste->startPosition = p;
                tmp = liste->startPosition;
            }
            else
            {
                tmp->nextPosition = p;
                tmp = tmp->nextPosition;
                tmp->nextPosition = NULL;
            }
            index++;
            liste->size++;
        }
        
    }
    
    return liste;
    
}

//Récupération d'une position à un index particulier
Position * getPositionAtIndex(int index,ListePosition * lp)
{
    //__android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "getPositionAtIndex"  );
    Position * returnPosition = NULL;
    if(index < 0)
        index *= -1;
    if(index < lp->size)
    {
        int tmpIndex = 0;
        Position * tmpPosition = lp->startPosition;
        int realIndex = tmpIndex+1;
        while(tmpIndex  != index)
        {
            realIndex = tmpIndex+1;
            if(tmpPosition->nextPosition)
                tmpPosition = tmpPosition->nextPosition;
            tmpIndex++;
        }
        returnPosition = copyPosition(tmpPosition);
    }
    // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "END getPositionAtIndex"  );
    return returnPosition;
}

//Fonction de parcours de la liste et d'affichage
void  parcoursList(ListePosition * lp)
{
    
    
    int tmpIndex = 0;
    Position * tmpPosition = lp->startPosition;
    while(tmpPosition)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "Position %d", tmpIndex  );
        tmpPosition = tmpPosition->nextPosition;
        tmpIndex++;
    }
    
}

//Supprimer un élément à un index précis
void  removePositionAtIndex(int index, ListePosition * lp)
{
    
    Position * currentIndex = NULL;
    Position * previous = NULL;
    if(index < 0)
        index *= -1;
    if(index < lp->size)
    {
        int tmpIndex = 0;
        Position * tmpPosition = lp->startPosition;
        int realIndex = tmpIndex+1;
        
        while(tmpIndex  != index)
        {
            realIndex = tmpIndex+1;
            previous = tmpPosition;
            
            tmpPosition = tmpPosition->nextPosition;
            
            tmpIndex++;
        }
        
        currentIndex = tmpPosition;
        if(tmpIndex > 0)
        {
            if(tmpIndex == (lp->size -1))
            {
                
                previous->nextPosition = NULL;
            }
            else
            {
                
                previous->nextPosition = currentIndex->nextPosition;
            }
        }
        else
        {
            lp->startPosition = currentIndex->nextPosition;
        }
        free(currentIndex);
        currentIndex = NULL;
        lp->size--;
        
    }
    
}

//Créer une Copie d'une position
Position * copyPosition(Position * p)
{
    
    Position * tmp = NULL;
    if(p != NULL)
    {
        
        tmp = malloc(sizeof(Position));
        tmp->position = p->position;
        tmp->side = p->side;
    }
    return tmp;
}
//Libérer en mémoire la liste de position
void freeListePosition(ListePosition * lp)
{
    Position *tmp = lp->startPosition;
    Position *nextTmp = NULL;
    while(tmp)
    {
        
        nextTmp = tmp->nextPosition;
        free(tmp);
        tmp = nextTmp;
        
    }
    
}