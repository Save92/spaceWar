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