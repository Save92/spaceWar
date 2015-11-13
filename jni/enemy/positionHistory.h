//
//  positionHistory.h
//  
//
//  Created by thierry allard saint albin on 01/11/2015.
//
//

#ifndef positionHistory_h
#define positionHistory_h

#include <stdio.h>
#include "../SDL/src/core/android/SDL_android.h"



typedef struct History History;
struct History
{
    int  LastPosStart;
    int  LastSide;
    int  LastDistance;
    int  LastverticalLine;
    int  LastypeShip;
    int  LastTypeMovement;
    History  * nextHistory;
   
};


typedef struct StackHistory StackHistory;
struct StackHistory
{
    History  * head;
    int  size;
};

History * initializeHistory(int LastPosStart,int  LastSide,int  LastDistance,int  LastverticalLine,int  LastypeShip,int  LastTypeMovement);
StackHistory * initializeStackHistory();
StackHistory * getHeads(StackHistory * stackHistory,int n);
void addHistory(History * history,StackHistory * stackHistory);
History * copyHistory(History history);

#endif /* positionHistory_h */
