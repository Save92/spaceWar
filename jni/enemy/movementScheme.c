//
//  movementScheme.c
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#include "movementScheme.h"
#include <stdlib.h>




 
 
MovementScheme * initializeMovementScheme(int startX,int startY,int distanceHorizontalLimit,int horizontalLimit,int distanceFromVerticalLimit,int verticalLimit,int typeMovementScheme)
{
    MovementScheme * movementScheme = malloc(sizeof(MovementScheme));
    movementScheme->startX = startX;
    movementScheme->startY = startY;
    movementScheme->distanceFromHorizonalLimit = distanceHorizontalLimit;
    movementScheme->distanceFromVerticalLimit = distanceFromVerticalLimit;
    movementScheme->horizontalLimit = horizontalLimit;
    movementScheme->verticalLimit = verticalLimit;
    movementScheme->type = typeMovementScheme;
    return movementScheme;
}
