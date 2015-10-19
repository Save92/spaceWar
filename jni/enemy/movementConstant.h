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
# define TOP_SCREEN  0 ;
# define TOP_SIDE_SCREEN  1 ;
# define TOP_MIDDLE_SIDE_SCREEN  2;
# define TOP_EXTREME_SIDE_SCREEN  3;
# define EXTREME_SIDE_SCREEN  4;



/** Type movement ***/
# define STRAIGHT_FORWARD 1 ;
# define ZIG_ZAG  2;
# define ZIG_ZAG_AND_STRAIGHT_FORWARD  3;
# define CIRCLE 4;




#endif