//
//  positionHistory.c
//  
//
//  Created by thierry allard saint albin on 01/11/2015.
//
//

#include "positionHistory.h"
#include "../SDL/src/core/android/SDL_android.h"
#include <android/log.h>
#include "./movementConstant.h"
#include <math.h>

const  signed int side[] = { 1, -1};
const  signed int position[] = { TOP_SCREEN, TOP_SIDE_SCREEN,TOP_MIDDLE_SIDE_SCREEN,TOP_EXTREME_SIDE_SCREEN,EXTREME_SIDE_SCREEN};

void addHistory(History * history,StackHistory * stackHistory)
{
   // __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "addHistory"  );
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
   // __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "End addHistory"  );
}


 StackHistory  * getHeads(StackHistory * stackHistory,int n)
{
    // __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "getHeads"  );
    int i = 0 ;
    StackHistory * stackCopy = initializeStackHistory();
    stackCopy->size = 0;
    
    History * tmp;
    History * indexNewStack;
    History * previousIndexNewStack;
   
  //  __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "size %d",  stackHistory->size );
    if(stackHistory->size > 0)
    {
   //     __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "Empty stack");
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
   // __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "END getHeads"  );
        return stackCopy;
}

History * copyHistory(History history)
{
   //  __android_log_print(ANDROID_LOG_DEBUG, "History",   "copyHistory"  );
    History * copyHistory = initializeHistory(history.LastPosStart,history.LastSide,history.LastDistance,history.LastverticalLine,history.LastypeShip,history.LastTypeMovement);
  //  __android_log_print(ANDROID_LOG_DEBUG, "History",   "END copyHistory"  );
    return copyHistory;
}

StackHistory * initializeStackHistory()
{
  //  __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "InitializeStackHistory"  );
    StackHistory * stack = malloc(sizeof(StackHistory));
    stack->size = 0;
    stack->head = NULL;
   // __android_log_print(ANDROID_LOG_DEBUG, "StackHistory",   "END InitializeStackHistory"  );
    return stack;
}


History * initializeHistory(int LastPosStart,int  LastSide,int  LastDistance,int  LastverticalLine,int  LastypeShip,int  LastTypeMovement)
{
  //   __android_log_print(ANDROID_LOG_DEBUG, "History",   "initializeHistory"  );
    History * newHistory = malloc(sizeof(History));
    newHistory->LastPosStart = LastPosStart;
    newHistory->LastSide = LastSide;
    newHistory->LastDistance = LastDistance;
    newHistory->LastverticalLine = LastverticalLine;
    newHistory->LastypeShip = LastypeShip;
    newHistory->LastTypeMovement = LastTypeMovement;
    newHistory->nextHistory = NULL;
   //   __android_log_print(ANDROID_LOG_DEBUG, "History",   "END initializeHistory"  );
    return newHistory;
}



ListePosition * initializeListePosition()
{
    //__android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "initializeListePosition"  );
    ListePosition * liste = malloc(sizeof(ListePosition));
    liste->size = 0;
    int lengthPosition = 5;
    int lengthSide = 2;
    
    int indexPosition = 0;
    int indexSide = 0;
    //__android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "get StartIndex"  );
    Position * tmp = liste->startPosition;
    int index = 0;
    for(indexPosition = 0; indexPosition < lengthPosition; indexPosition++)
    {
        for(indexSide = 0 ; indexSide < lengthSide ; indexSide++)
        {
          

            Position * p = malloc(sizeof(Position));
            p->position = position[indexPosition];
            p->side = side[indexSide];
            p->nextPosition = NULL;
           // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "add Position Position: %d , side:%d , adress :%d  index %d" ,p->position,p->side,p,index );
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
    //__android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "END initializeListePosition"  );
    return liste;
    
}
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


void  parcoursList(ListePosition * lp)
{
    // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "parcoursList"  );

        int tmpIndex = 0;
        Position * tmpPosition = lp->startPosition;
        while(tmpPosition)
        {
           //  __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "Position %d", tmpIndex  );
            tmpPosition = tmpPosition->nextPosition;
            tmpIndex++;
        }
     //__android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "END parcoursList"  );
}

void  removePositionAtIndex(int index, ListePosition * lp)
{
   // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "removePositionAtIndex"  );
    Position * currentIndex = NULL;
    Position * previous = NULL;
    if(index < 0)
        index *= -1;
    if(index < lp->size)
    {
        int tmpIndex = 0;
        Position * tmpPosition = lp->startPosition;
        int realIndex = tmpIndex+1;
       // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   " removePositionAtIndex IF"  );
        while(tmpIndex  != index)
        {
            realIndex = tmpIndex+1;
            previous = tmpPosition;
          //  __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "tmpPosition = tmpPosition->nextPosition;"  );
            tmpPosition = tmpPosition->nextPosition;

            tmpIndex++;
        }
        
        currentIndex = tmpPosition;
        // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   " tmpIndex %d, size %d",tmpIndex,lp->size  );
       // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   " currentIndex->nextPosition"  );
        if(tmpIndex > 0)
        {
            if(tmpIndex == (lp->size -1))
            {
        //        __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   " FL1"  );
                previous->nextPosition = NULL;
            }
            else
            {
          //      __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   " FL2"  );
                previous->nextPosition = currentIndex->nextPosition;
            }
        }
        else
        {
         //   __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   " FL3"  );
            lp->startPosition = currentIndex->nextPosition;
        }
        free(currentIndex);
        currentIndex = NULL;
        lp->size--;
        
    }
     //  __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "END removePositionAtIndex"  );
}

Position * copyPosition(Position * p)
{
  //  __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "copyPosition "  );
    Position * tmp = NULL;
  //    __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "copyPosition adresse %d",p  );
    if(p != NULL)
    {
   //      __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "IF copyPosition "  );
        tmp = malloc(sizeof(Position));
        tmp->position = p->position;
        tmp->side = p->side;
    }
  //  __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "END copyPosition "  );
    return tmp;
}

void freeListePosition(ListePosition * lp)
{
   //   __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "freeListePosition"   );
    Position *tmp = lp->startPosition;
    Position *nextTmp = NULL;
    while(tmp)
    {
     //     __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "Free Position %d",tmp   );
        nextTmp = tmp->nextPosition;
        free(tmp);
        tmp = nextTmp;
        
    }
   // __android_log_print(ANDROID_LOG_DEBUG, "PositionHistory",   "freeListePosition"   );
}