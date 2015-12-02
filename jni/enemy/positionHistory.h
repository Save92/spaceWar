//
//  positionHistory.h
//  
//
//
//

#ifndef positionHistory_h
#define positionHistory_h

#include <stdio.h>
#include "../SDL/src/core/android/SDL_android.h"



typedef struct History History;
//Un historique est définis selon une position de départ, un coté, une distance par rapport à une ligne verticale, une ligne vertical, un type de vaisseau, un type de mouvement et un niveau de tir
// Toute histoire est liée à une prochaine histoire
struct History
{
    int  LastPosStart;
    int  LastSide;
    int  LastDistance;
    int  LastverticalLine;
    int  LastypeShip;
    int  LastTypeMovement;
    int LastShotLevel;
    History  * nextHistory;
   
};

//Pile d'historique
typedef struct StackHistory StackHistory;
struct StackHistory
{
    History  * head;
    int  size;
};


//Structure de position
typedef struct Position Position;
struct Position
{
    int position;
    int side;
    
    Position * nextPosition;
};
//Liste de position
typedef struct ListePosition ListePosition;
struct ListePosition
{
    Position * startPosition;
    int size ;
};
//Initialisation d'un histoire
History * initializeHistory(int LastPosStart,int  LastSide,int  LastDistance,int  LastverticalLine,int  LastypeShip,int  LastTypeMovement,int lastShotLevel);
//Initialisation d'une pile d'histoire
StackHistory * initializeStackHistory();
//récupération des n premiers éléments dans une pile
StackHistory * getHeads(StackHistory * stackHistory,int n);
// ajout d'un historique dans la pile
void addHistory(History * history,StackHistory * stackHistory);
// copie d'un historique
History * copyHistory(History history);
//Initialisation d'une liste de position
ListePosition * initializeListePosition();
//Récupération d'une position à un index
Position * getPositionAtIndex(int index,ListePosition * lp);
//Suprression d'une position à un index
void  removePositionAtIndex(int index, ListePosition * lp);
//Copie d'une position
Position * copyPosition(Position * p);
//Suppresion dans la liste des positions
void freeListePosition(ListePosition  * lp);
//Parcours de la liste
void  parcoursList(ListePosition * lp);




#endif /* positionHistory_h */
