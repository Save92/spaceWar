#ifndef movementConstant_h
#define movementConstant_h

#include <stdio.h>

/*      
        TOP_SCREEN
        $$$ $$$ $$$ $$$ $$$ $$$ $$$
        $5     3  1      2    4  6$
        $                         $
        $*************************$
        $                         $
        $7                       8$
        $                         $
        ***************************
 
 */


/** Start position ***/
# define TOP_LEFT_SCREEN  1 ;
# define TOP_RIGHT_SCREEN  2;
# define LEFT_SCREEN  3;
# define RIGHT_SCREEN  4;
# define EXTREME_LEFT_SCREEN  5;
# define EXTREME_RIGHT_SCREEN  6;
# define TOP_MIDDLE_EXTREME_LEFT_SCREEN  7;
# define TOP_MIDDLE_EXTREME_RIGHT_SCREEN  8;



/** Type movement ***/
# define STRAIGHT_FORWARD 1 ;
# define ZIG_ZAG  2;
# define ZIG_ZAG_AND_STRAIGHT_FORWARD  3;
# define CIRCLE 4;




#endif