#ifndef movementConstant_h
#define movementConstant_h

#include <stdio.h>

/*      
        TOP_SCREEN
        $$$ $$$ $$$ $$$ $$$ $$$ $$$
        $3   2  1    0   1b  2b 3b$
        $                         $
        $*************************$
        $                         $
        $4                      4b$
        $                         $
        ***************************
 
 */


/** Start position ***/
# define TOP_LEFT_SCREEN  1 ;
# define TOP_RIGHT_SCREEN  2;
# define LEFT_SCREEN  3;
# define RIGHT_SCREEN  4;



/** Type movement ***/
# define STRAIGHT_FORWARD 1 ;
# define ZIG_ZAG  2;
# define ZIG_ZAG_AND_STRAIGHT_FORWARD  3;
# define CIRCLE 4;




#endif