//
//  enemy.c
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#include "enemy.h"
#include "littleEnemyShip.h"


void drawEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip)
{
    switch (enemyShip->type) {
        case 0:
            drawLittleEnemyShip(renderer , enemyShip);
            break;
            
        default:
            break;
    }
}

void moveEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen, double coef)
{
    switch (enemyShip->type) {
        case 0:
            moveLittleEnemyShip(enemyShip,widthScreen,heightScreen,coef);
            break
            
        default:
            break;
    return;
}




void freeEnemyShip(EnemyShip * enemyShip)
{
    free(enemyShip->rectangle);
    free(enemyShip->movementScheme);
    free(enemyShip->nextEnemyShip);
    free(enemyShip);
   
}

EnemyShip * initialisationEnemyShip(int width,int height,int side,int typeShip,int typeMovement,int side)
{
    EnemyShip * enemyShip
    switch(int typeShip)
    {
        case 0: enemyShip   = initialisationLittleEnemyShip(width,height,typeMovement,side);
            break;
            
        default :
            break;
            
    }
    
   
    
   
    
}

Shoot * EnemyShipShoot(EnemyShip * enemyShip)
{
    switch (enemyShip->type) {
        case 0: LittleEnemyShipShoot(enemyShip);
            break
            
    }
}
    
int canShoot(enemyShip * enemyShip)
{
    int canShoot;
    switch (enemyShip->type) {
        case 0: canShoot = LittleEnemyShipCanShoot(enemyShip)
            break;
            
        default:
            break;
    }
    
    return canShoot;
    
}



