//
//  squadron.h
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#ifndef squadron_h
#define squadron_h

#include <stdio.h>
#include "./enemy.h"

typedef struct Squadron
{
    EnemyShip * nextEnemy;
    int size;
    int side;
    
    
} Squadron;

#endif /* squadron_h */
