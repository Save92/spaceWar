//
//  game.c
//  
//
//  Created by thierry allard saint albin on 01/11/2015.
//
//

#include "game.h"
#include <time.h>
#include "../enemy/positionHistory.h"
#include "../SDL/src/core/android/SDL_android.h"
#include <android/log.h>
#include "constant.h"
#include "../enemy/enemy.h"



#define SizeName  128
#define MaxEnemy 4
#define ApparitionTime 500

#define quotientTemps 150
#define quotientForce 0.25


Game *  initialisationOfTheGame(int width,int height)
{
    Game * game = malloc(sizeof(Game));
    game->score = 0;
    game->size = 0;
    game->score = 0;
    game->level = 1;
    game->width = width;
    game->height = height;
    game->nameUser = malloc( SizeName * sizeof(char));
    strcpy(game->nameUser, "AAAA");
    game->history = 0;
    game->cntInLastSquadron = 0;
    game->stack = initializeStackHistory();
    game->tempsActuel = SDL_GetTicks();
    game->tempsPrecedent = 0;
    game->myShip = initialisationUserShip(width,height); 
    game->listShootUser = malloc(sizeof(ListShoot));
    game->listShootUser->size = 0;
    game->listShootUser->start = NULL;
    game->listShootEnnemy = malloc(sizeof(ListShoot));
    game->listShootEnnemy->size = 0;
    game->listShootEnnemy->start = NULL;
    if(TTF_Init() == -1)
    {
        game->initText = -1;
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Erreur d'initialisation de TTF_Init : %s\n",TTF_GetError());
    }
    else
    {
        game->initText = 0;
        game->police = NULL;
        game->police =  TTF_OpenFont("game_over.ttf", 65);
        if(game->police == NULL)
             game->initText = -1;
    }
    
    //Get initialize rumble
    if( SDL_HapticRumbleInit( game->gControllerHaptic ) < 0 )
    {
        game->initRumble = -1;
       __android_log_print(ANDROID_LOG_DEBUG, "GAME",  "Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        game->initRumble = 1;
    }
    return game;

}

void eventCheckCollisionUserShipEnnemyShoot(Game * game,SDL_Renderer *renderer) {

   // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "CHECK eventCheckCollisionUserShipEnnemyShoot!!!_______________________________");
    Shoot * indexList = game->listShootEnnemy->start;

    Shoot *tmp = indexList;
    while(tmp)
    {
        indexList = tmp;

        if (checkCollision(*(game->myShip->rectangle), *(indexList->rectangle), indexList->speed) == TRUE) {
            //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "TIR ENNEMIE !!! BOOOOOOOMMMMMM!!!!!"  );
            decreaseLife( game->myShip );
            enum RumbleForce force = MEDIUM_FORCE;
            enum RumbleLength length = MEDIUM_LENGTH;
            playRumble(game,force,length);
            
            
            if(game->myShip->life == 0) {
                force = FORT;
                length = LONG;
                playRumble(game,force,length);
                onDestroy(game->myShip->posX, game->myShip->posY, renderer);
            }
            indexList->visible = INVISIBLE;
        }
        tmp = tmp->nextShoot;
    }
}

void eventCheckCollisionUserShipEnnemyShip(Game * game,SDL_Renderer *renderer) {
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "CHECK eventCheckCollisionUserShipEnnemyShip!!!_______________________________");
    
    Squadron * indexSquadron = game->nextSquadron;
    
    Squadron *tmpSquadron = indexSquadron;
    while(tmpSquadron)
    {
        
        EnemyShip * indexList = tmpSquadron->nextEnemyShip;
        
        EnemyShip *tmp = indexList;
        while(tmp)
        {
            indexList = tmp;
            
            if (checkCollision(*(game->myShip->rectangle), *(indexList->rectangle), indexList->speed) == TRUE)
            {
                //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "VAISSEAUX SE RENTRE DEDANS! BOOOOOOOMMMMMM!!!!!"  );
                indexList->life -= 1;
                if (indexList->life == 0)
                {
                    onDestroy(indexList->posX, indexList->posY, renderer);
                    indexList->visible = INVISIBLE;
                }
                
                // game->myShip->visible = INVISIBLE;
                // indexList->visible = INVISIBLE;
                decreaseLife( game->myShip );
                enum RumbleForce force = MEDIUM_FORCE;
                enum RumbleLength length = MEDIUM_LENGTH;
                playRumble(game,force,length);
            }
            tmp = tmp->nextEnemyShip;
        }
        
        indexSquadron = tmpSquadron;
        tmpSquadron = tmpSquadron->nextSquadron;
    }
    
    
}

void eventCheckCollisionUserShipShootEnnemy(Game * game,SDL_Renderer *renderer) {

    Squadron * indexSquadron = game->nextSquadron;

    Squadron *tmpSquadron = indexSquadron;
    while(tmpSquadron)
    {

        EnemyShip * indexList = tmpSquadron->nextEnemyShip;

        EnemyShip *tmp = indexList;
        while(tmp)
        {
            indexList = tmp;
            Shoot * indexListShoot = game->listShootUser->start;

            Shoot *tmpShoot = indexListShoot;
            while(tmpShoot)
            {
                indexListShoot = tmpShoot;

                //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "TIR  !!! Pas touche"  );
                if (checkCollision(*(indexList->rectangle), *(indexListShoot->rectangle), indexListShoot->speed) == TRUE) {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "TIR !!! BOOOOOOOMMMMMM!!!!!"  );
                    indexList->life -= 1;
                    if (indexList->life == 0) {
                        onDestroy(indexList->posX, indexList->posY, renderer);
                        indexList->visible = INVISIBLE;
                        addScore(*indexList,&(game->score));
                    }
                    indexListShoot->visible = INVISIBLE;
                }
                tmpShoot = tmpShoot->nextShoot;
            }

            // if (checkCollision(*(game->myShip->rectangle), *(indexList->rectangle)) == TRUE) {
            //     __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "VAISSEAUX SE RENTRE DEDANS! BOOOOOOOMMMMMM!!!!!"  );
            // }
            tmp = tmp->nextEnemyShip;
        }

        indexSquadron = tmpSquadron;
        tmpSquadron = tmpSquadron->nextSquadron;
    }

    
}

void eventCheckCollision(Game * game, SDL_Renderer *renderer) {
    // Test pour les collisions
    if (game->size > 0) {
        // if (game->myShip->alive() == 1)
        // {
           
   
            eventCheckCollisionUserShipEnnemyShoot(game, renderer);
            eventCheckCollisionUserShipEnnemyShip(game, renderer);
            eventCheckCollisionUserShipShootEnnemy(game, renderer);
        //}

    }
}

void  moveAllGame(Game * game, SDL_Renderer *renderer)
{

    eventCheckCollision(game, renderer);
    moveAllMyShoots(game->listShootUser,game->width,game->height);
    moveAllMyShoots(game->listShootEnnemy,game->width,game->height);


    game->tempsActuel = SDL_GetTicks();
    if(game->size == 0)
    {
        createNextSquadron(game);
    }
    else
    {
        Squadron *tmp = game->nextSquadron;
        int size = game->size;
        int index = 0;
        while(tmp && index < size)
        {
            if(game->tempsActuel - game->tempsPrecedent > ApparitionTime)
            {
                createNextSquadron(game);
                game->tempsPrecedent = game->tempsActuel;
            }
            tmp= tmp->nextSquadron;
            index++;
        }
    }
    
    Squadron *tmp =  game->nextSquadron;
    while(tmp)
    {
        moveSquadron(tmp,game->width,game->height,game->listShootEnnemy);
        tmp= tmp->nextSquadron;
    }

  //  __android_log_print(ANDROID_LOG_DEBUG, "GAME", "END moveAllGame ");
    
}


void  drawGame(SDL_Renderer* renderer ,Game * game)
{
    drawAllMyShoots(renderer,game->listShootUser);
    drawAllMyShoots(renderer,game->listShootEnnemy);
    drawMyShip(renderer , game->myShip);
   //  __android_log_print(ANDROID_LOG_DEBUG, "GAME", "drawGame ");
    if(game->size > 0)
    {
        Squadron * squadron;
        squadron = game->nextSquadron;
        while(squadron && game->myShip->life > 0)
        {
            drawMySquadron(renderer,squadron);
            squadron = squadron->nextSquadron;
        }
    }
    if(game->initText != -1)
    {
        renderScore(game,renderer);
    }
    renderLife(game,renderer);
 //   __android_log_print(ANDROID_LOG_DEBUG, "GAME", "END drawGame ");
}



void removeNotVisibleSquadronFromGame(Game * game)
{
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "removeNotVisibleSquadronFromGame"  );
    Squadron  *tmp;
    Squadron  *previous;
    Squadron  *next;
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG1"  );
    if(game != NULL && game->nextSquadron != NULL)
    {

        if(game->nextSquadron->nextSquadron == NULL)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG3"  );
            if(game->nextSquadron == 0)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG4"  );
                freeSquadron(game->nextSquadron);
                game->nextSquadron = NULL;
            }
        }
        else
        {
            __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG5"  );
            tmp = game->nextSquadron;
            previous = NULL;
            Squadron  *next;
            while(tmp != NULL)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG6"  );
                if(tmp->visible == 0)
                {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG7"  );
                    Squadron * deletedSquadron = tmp;
                    
                    tmp = tmp->nextSquadron;
                    if(previous == NULL)
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG8"  );
                        game->nextSquadron = tmp;
                    }
                    else
                    {
                        previous->nextSquadron = tmp;
                    }
                    if(deletedSquadron)
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG9"  );
                        freeSquadron(deletedSquadron);
                    }
                    deletedSquadron = NULL;
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG10"  );
                    game->size--;
                }
                else
                {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG11"  );
                    previous = tmp;
                    tmp= tmp->nextSquadron;
                }
            }
        }
    }
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END removeNotVisibleSquadronFromGame"  );
 //   __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END removeNotVisibleSquadronFromGame"  );
}

void  createNextSquadron(Game * game)
{
  //   __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "START createNextSquadron"  );
    
    if(game->history == 0 || game->history %2 == 0)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "PAIRE"  );
        int nombre_aleatoire = 0;
        nombre_aleatoire = my_rand();
        int nbrEnnemy =nombre_aleatoire % MaxEnemy;
        if(nbrEnnemy == 0)
            nbrEnnemy++;
       
        int n = 0;
        int side = 1;
        Squadron * squad;
        if(game->size != 0)
        {
            Squadron * tmpSquad = getLastSquadron(game);
            tmpSquad->nextSquadron = initialisationSquadron(nbrEnnemy);
            squad = tmpSquad->nextSquadron;
        }
        else
        {
            game->nextSquadron = initialisationSquadron(nbrEnnemy);
            squad = game->nextSquadron;
        }
        game->history++;
        for(n = 0 ; n < nbrEnnemy ; n++)
        {
            addNewEnemy(game,squad);
        }
        
         game->cntInLastSquadron = nbrEnnemy;
    }
    else
    {
       // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "IMPAIRE"  );

      //  addEnemyFromHistory(game);
        
        
       
        int nombre_aleatoire = 0;
        nombre_aleatoire = rand();
        int nbrEnnemy =nombre_aleatoire % MaxEnemy;
        if(nbrEnnemy == 0)
            nbrEnnemy++;
        
        int n = 0;
        int side = 1;
        Squadron * squad;
        if(game->size != 0)
        {
            Squadron * tmpSquad = getLastSquadron(game);
            tmpSquad->nextSquadron = initialisationSquadron(nbrEnnemy);
            squad = tmpSquad->nextSquadron;
        }
        else
        {
            game->nextSquadron = initialisationSquadron(nbrEnnemy);
            squad = game->nextSquadron;
        }
        game->history++;
        for(n = 0 ; n < nbrEnnemy ; n++)
        {
            addNewEnemy(game,squad);
        }
        
        game->cntInLastSquadron = nbrEnnemy;
        
    }
    game->size++;
}

void addNewEnemy(Game * game,Squadron * squadron)
{
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "addNewEnemy"  );
    int side = 0;
    int posStart = my_rand()%4; //A modifier pour mettre probabilité par lot (Loto)
    
    int tempDividendeDistance = my_rand() % MaxEnemy ;
    if(tempDividendeDistance == 0)
        tempDividendeDistance++;
    
    int distance = game->width/tempDividendeDistance ;
    int dividende = my_rand() % 8;
    if(dividende == 0)
        dividende++;
    int verticalLine = game->width/2;
    if(my_rand()%2 == 0)
    {
        side = 1;
        int verticalLine = game->width - verticalLine;
    }
    else
    {
        side = -1;
    }
    int typeShip = 0;
    int typeMovement = my_rand() % 3;

    EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,posStart, side,distance,verticalLine,typeShip,typeMovement);
    History *history =  initializeHistory(posStart,side,distance ,verticalLine,typeShip,typeMovement);
    addHistory(history,game->stack);
    
    addEnemyToSquadron(enemy,squadron);
    
   //  __android_log_print(ANDROID_LOG_DEBUG, "GAME", "End addEnemy");
   


}


void addEnemyFromHistory(Game * game)
{
   // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "addEnemyFromHistory"  );
    
    
    int nombre = game->cntInLastSquadron;
   // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "cnt in lastSquadron %d",nombre);
    StackHistory * tempStack=getHeads(game->stack,nombre);
    History * tmp = tempStack->head;
    Squadron * lastSqdr = getLastSquadron(game);
    
   // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "size Stack %d",game->stack->size);
   // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "size tempStack %d",tempStack->size);
   // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "stack adress %d",tempStack->head);
    lastSqdr->nextSquadron = initialisationSquadron(nombre);
    while(tmp != NULL )
    {
   //     __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "history address %d",tmp);
        EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,tmp->LastPosStart, (-1)*tmp->LastSide,tmp->LastDistance,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement);
        
        History *history =  initializeHistory(tmp->LastPosStart,(-1)* (tmp->LastSide),tmp->LastDistance ,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement);
        
        addEnemyToSquadron(enemy,lastSqdr->nextSquadron);
        
        addHistory(history,game->stack);
        tmp = tmp->nextHistory;
        
        
    }
    
    game->history++;
  //    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END addEnemyFromHistory"  );
}

int checkCollision(SDL_Rect a, SDL_Rect b, int speed )
{

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
 //If any of the sides from A are outside of B
    if( bottomA <= topB+speed)
    {
       // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "botA : %d <= topB : %d", bottomA,  topB);
        return FALSE;
    }

    if( topA + speed>= bottomB )
    {

        //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "totA : %d <= bptB : %d", topA,  bottomB);
        return FALSE;
    }

    if( rightA <= leftB )
    {

        //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "rightA : %d <= leftB : %d", rightA,  leftB);
        return FALSE;
    }

    if( leftA >= rightB )
    {
        //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "leftA >= rightB"  );

        //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "leftA : %d <= rightB : %d", leftA,  rightB);
        return FALSE;
    }

    //If none of the sides from A are outside B
    return TRUE;
}

Squadron * getLastSquadron(Game * game)
{
 //    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "getLastSquadron"  );
    Squadron * indexSquadron = game->nextSquadron;
    if(game->size == 0)
    {
        return indexSquadron;
    }
    else
    {
        indexSquadron = game->nextSquadron;
        Squadron *tmp = indexSquadron;
        while(tmp)
        {
            indexSquadron = tmp;
            tmp = tmp->nextSquadron;
        }
    }
 //    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END getLastSquadron"  );
    return indexSquadron;
}

int my_rand()
{
    time_t t;
    int tick = SDL_GetTicks();
    srand((unsigned) time(&t));
    return rand() * tick * 7;
}

void onDestroy(int posx, int posy, SDL_Renderer *renderer) {
  
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "onDestroy avant sprite"  );
    SpriteExplosion explosion = LoadSpriteForExplostion(2, renderer);
    SDL_Rect test = {  posx, posy, 100 , 100  };

        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "onDestroy avant renderer"  ); 
    SDL_RenderCopyEx(renderer, explosion.texture, &(explosion.image_location), &test, explosion.angle, NULL, SDL_FLIP_NONE);
   
   
}

// Fonction d'affichage du sprite pour l'explosion (Pas au point...)
SpriteExplosion LoadSpriteForExplostion(int image, SDL_Renderer *renderer)
{
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "LoadSpriteForExplostion_____SpriteExplosion"  );

    SpriteExplosion * result = malloc(sizeof(SpriteExplosion));
    result->background.r = 255;
    result->background.g = 255;
    result->background.b = 255;
    result->image_location =  malloc( sizeof(SDL_Rect));
    result->image_location->x = 0;
    result->image_location->y = 200;
    result->image_location->h = 100;
    result->image_location->w = 100;
    result->texture = NULL;
    if (image == 2) {
        result->x = 0;
        result->y = 200;
    }
    result->w = 100;
    result->h = 100;
    result->angle = 0.0;

    /* Load the sprite image */
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "LoadSpriteForExplostion_____LOAD_BMP"  );
    result->surface = SDL_LoadBMP("../assets/explosion.bmp");
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "LoadSpriteForExplostion_____AFTER_LOAD_BMP"  );
    if (result->surface == NULL)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "LoadSpriteForExplostion surface = null"  );   
        return (*result);
    }
__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "LoadSpriteForExplostion surface OK"  ); 
    /* Create texture from the image */
    result->texture = SDL_CreateTextureFromSurface(renderer, result->surface);
    if (!result->texture) {

        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "LoadSpriteForExplostion texture = null"  ); 
        SDL_FreeSurface(result->surface);
        return (*result);
    }

        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "LoadSpriteForExplostion texture OK"  ); 
    SDL_FreeSurface(result->surface);

    return (*result);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}


void playRumble(Game * game,enum RumbleForce force,enum RumbleLength length)
{
    float frc = (float)(quotientForce * force);
    float lgth = (float)(quotientTemps * length);
    
    if( SDL_HapticRumblePlay( game->gControllerHaptic, frc, lgth ) != 0 )
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME", "Warning: Unable to play rumble! %s\n", SDL_GetError() );
    }
}


