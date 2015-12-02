//
//  movementScheme.h
//  
//
//
//

#ifndef movementScheme_h
#define movementScheme_h

#include <stdio.h>




//Schéma de mouvement définis par une position de départ et une ligne verticale et horizontal
//On peut imaginer des schéma de mouvement avec des tableaux de lignes
typedef struct MovementScheme
{
    
    int startX;
    int startY;
    int distanceFromHorizonalLimit ;
    int horizontalLimit;
    int distanceFromVerticalLimit ;
    int verticalLimit;
    int type;
    
} MovementScheme;

//Fonction d'initialisation des Mouvements
MovementScheme * initializeMovementScheme(int startX,int startY,int distanceHorizontalLimit,int horizontalLimit,int distanceFromVerticalLimit,int verticalLimit,int typeMovementScheme);
#endif /* movementScheme_h */
