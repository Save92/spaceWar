//
//  movementScheme.h
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#ifndef movementScheme_h
#define movementScheme_h

#include <stdio.h>





typedef struct MovementScheme
{
    
    int startX;
    int startY;
    int distanceFromHorizonalLimit ;
    int distanceFromVerticalLimit ;
    int type;
    
} MovementScheme;


MovementScheme * initializeMovementScheme(int startX,int startY,int distanceHorizontalLimit,int distanceFromVerticalLimit,int typeMovementScheme);
#endif /* movementScheme_h */
