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



typedef struct Position Position;
struct Position
{
    int position;
    int side;
    
    Position * nextPosition;
};

typedef struct ListePosition ListePosition;
struct ListePosition
{
    Position * startPosition;
    int size ;
};

History * initializeHistory(int LastPosStart,int  LastSide,int  LastDistance,int  LastverticalLine,int  LastypeShip,int  LastTypeMovement);
StackHistory * initializeStackHistory();
StackHistory * getHeads(StackHistory * stackHistory,int n);
void addHistory(History * history,StackHistory * stackHistory);
History * copyHistory(History history);
ListePosition * initializeListePosition();
Position * getPositionAtIndex(int index,ListePosition * lp);
void  removePositionAtIndex(int index, ListePosition * lp);
Position * copyPosition(Position * p);
void freeListePosition(ListePosition  * lp);
void  parcoursList(ListePosition * lp);




#endif /* positionHistory_h */
