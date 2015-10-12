//
//  littleEnemyShip.h
//  
//
//  Created by thierry allard saint albin on 12/10/2015.
//
//

#ifndef littleEnemyShip_h
#define littleEnemyShip_h

#include <stdio.h>



void drawLittleEnemyShip(SDL_Renderer* renderer , EnemyShip * enemyShip);
void moveLittleEnemyShip(EnemyShip * enemyShip,int widthScreen, int heightScreen, double coef)
Shoot * EnemyShipShoot(EnemyShip * enemyShip);
EnemyShip * initialisationLittleEnemyShip(int width,int height,int countEnemy);



#endif /* littleEnemyShip_h */
