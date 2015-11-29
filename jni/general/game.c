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
#include <math.h>
#include "CustomLog.h"


#define SizeName  128
#define MaxEnemy 5
#define ApparitionTime 2000

#define quotientTemps 150
#define quotientForce 0.25

static int levelUp = 100;
int Time_app = ApparitionTime;
int maxShotLevelEnemi = 1 ;


Game *  initialisationOfTheGame(int width,int height,char * nativeName,int command,int music,int vibration,int highScore)
{
     customLog(0, "GAME" ,  __func__);
    
    Game * game = malloc(sizeof(Game));
    game->score = 0;
    game->size = 0;
    game->score = 0;
    game->level = 1;
    game->width = width;
    game->height = height;
    game->nameUser = malloc( SizeName * sizeof(char));
    strcpy(game->nameUser, nativeName);
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
    game->command = command;
    game->music = music;
    game->vibration = vibration;
    game->PreviousHighScore = highScore;
    game->saveNewHighScore = FALSE;
    
    if(TTF_Init() == -1)
    {
        game->initText = -1;
        //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Erreur d'initialisation de TTF_Init : %s",TTF_GetError());
    }
    else
    {
        game->initText = 0;
        game->police = NULL;
        game->police =  TTF_OpenFont("game_over.ttf", 65);
        if(game->police == NULL)
            game->initText = -1;
    }
    
    game->gControllerHaptic = SDL_HapticOpen( 0 );
    if (game->gControllerHaptic == NULL)
    {
        game->initRumble = -1;
        //__android_log_print(ANDROID_LOG_DEBUG, "GAME",  "Warning: Unable to initialize rumble! SDL Error: %s", SDL_GetError() );
    }
    else
    {
        if (SDL_HapticRumbleInit( game->gControllerHaptic ) != 0)
        {
            game->initRumble = -1;
            
        }
        else
        {
            game->initRumble = 1;
        }
    }
    
    initialisationSound(game);
    if(game->initAudio != -1)
        playMusic(game->mainMusic,-1,game);
    
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0, "GAME" , str);
    free(str);
    
    return game;
    
}


void initialisationSound( Game * game)
{
    
    customLog(0, "GAME" ,  __func__);
    game->initAudio = 1;
    
    
    if(SDL_Init(SDL_INIT_AUDIO)==-1)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Audio Error : Failed to init SDL_INIT_AUDIO");
        game->initAudio = -1;
    }
    else
    {
        int flags=MIX_INIT_MP3;
        int initted=Mix_Init(flags);
        if(initted&flags != flags) {
            __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Audio Error : Failed to init required suppord ");
            __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Audio Error : Mix_Init: %s\n", Mix_GetError() );
            game->initAudio = -1;
        }
        else
        {
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
            {
                __android_log_print(ANDROID_LOG_DEBUG, "GAME", "Mix_OpenAudio ERROR");
                game->initAudio = -1;
            }
            else
            {
                //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
                if(Mix_SetMusicCMD(NULL)==-1) {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME", "Mix_SetMusicCMD");
                }
                else
                {
                    // play some wav file
                    game->mainMusic=Mix_LoadMUS("rebel-theme.wav");
                    if(!game->mainMusic) {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_LoadMUS(\"rebel-theme.wav\"): %s\n", Mix_GetError());
                        game->initAudio = -1;
                    }
                    
                    game->tie_arrive = Mix_LoadWAV("TIE ARRIVE.wav");
                    if(!game->tie_arrive ) {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_LoadWAV: %s\n", Mix_GetError());
                        game->initAudio = -1;
                    }
                    else
                    {
                        Mix_VolumeChunk( game->tie_arrive , MIX_MAX_VOLUME - MIX_MAX_VOLUME/2);
                    }
                    
                    game->tie_shoot = Mix_LoadWAV("TIE SHOOT2.wav");
                    if(!game->tie_shoot )
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_LoadWAV: %s\n", Mix_GetError());
                        game->initAudio = -1;
                        
                    }
                    else
                    {
                        Mix_VolumeChunk( game->tie_shoot , MIX_MAX_VOLUME - MIX_MAX_VOLUME/3);
                    }
                    
                    
                    game->Xwing_shoot = Mix_LoadWAV("XWing-Laser.wav");
                    if(!game->Xwing_shoot)
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_LoadWAV: %s\n", Mix_GetError());
                        game->initAudio = -1;
                        
                    }
                    else
                    {
                        Mix_VolumeChunk( game->Xwing_shoot , MIX_MAX_VOLUME - MIX_MAX_VOLUME/3);
                    }
                    
                    game->Immhit = Mix_LoadWAV("R2D2a.wav");
                    if(!game->Immhit)
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_LoadWAV: %s\n", Mix_GetError());
                        game->initAudio = -1;
                        
                    }
                    else
                    {
                        Mix_VolumeChunk( game->Immhit , MIX_MAX_VOLUME - MIX_MAX_VOLUME/3);
                    }
                    
                }
            }
        }
    }
    
    if(game->initAudio == -1)
        game->music = 0;
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0, "GAME" , str);
    free(str);
    
}



void playMusic(Mix_Music *mainMusic,int cntRepeat,Game * game)
{
    customLog(0, "GAME" ,  __func__);
    if(game->music == 1)
    {
        if(Mix_PlayMusic(mainMusic, cntRepeat)==-1) {
        __android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_PlayMusic: %s\n", Mix_GetError());
        // well, there's no music, but most games don't break without music...
        }
    }
    Mix_VolumeMusic(125);
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
}

void eventCheckCollisionUserShipEnnemyShoot(Game * game,SDL_Renderer *renderer) {
    
    customLog(0 , "GAME" ,  __func__);
    Shoot * indexList = game->listShootEnnemy->start;
    
    Shoot *tmp = indexList;
    while(tmp)
    {
        indexList = tmp;
        
        if (indexList->visible == VISIBLE && checkCollision(*(game->myShip->rectangle), *(indexList->rectangle), indexList->speed) == TRUE) {
            //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "TIR ENNEMIE !!! BOOOOOOOMMMMMM!!!!!"  );
            customLog(0 , "GAME" ,  "TIR ENNEMIE !!! BOOOOOOOMMMMMM!!!!!");
            decreaseLife( game->myShip );
            enum RumbleForce force = MEDIUM_FORCE;
            enum RumbleLength length = MEDIUM_LENGTH;
            playRumble(game,force,length);
            MyPlaySample(-1,game->Immhit,0,game->music);
            decreasePower(game->myShip);
            
            if(game->myShip->life == 0) {
                force = FORT;
                length = LONG;
                playRumble(game,force,length);
               // onDestroy(game->myShip->posX, game->myShip->posY, renderer);
            }
            indexList->visible = INVISIBLE;
        }
        tmp = tmp->nextShoot;
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}

void eventCheckCollisionUserShipEnnemyShip(Game * game,SDL_Renderer *renderer) {
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "CHECK eventCheckCollisionUserShipEnnemyShip!!!_______________________________");
    customLog(0 , "GAME" ,  __func__);
    Squadron * indexSquadron = game->nextSquadron;
    
    Squadron *tmpSquadron = indexSquadron;
    while(tmpSquadron)
    {
        
        EnemyShip * indexList = tmpSquadron->nextEnemyShip;
        
        EnemyShip *tmp = indexList;
        while(tmp)
        {
            indexList = tmp;
            
            if (indexList->visible == VISIBLE  && checkCollision(*(game->myShip->rectangle), *(indexList->rectangle), indexList->speed) == TRUE)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "VAISSEAUX SE RENTRE DEDANS! BOOOOOOOMMMMMM!!!!!"  );
                indexList->life -= 1;
                if (indexList->life <= 0)
                {
                   // onDestroy(indexList->posX, indexList->posY, renderer);
                    setEnemyToInvisible(indexList);
                    //tmpSquadron->size--;
                }
                decreasePower(game->myShip);
                // game->myShip->visible = INVISIBLE;
                // indexList->visible = INVISIBLE;
                decreaseLife( game->myShip );
                enum RumbleForce force = MEDIUM_FORCE;
                enum RumbleLength length = MEDIUM_LENGTH;
                playRumble(game,force,length);
                MyPlaySample(-1,game->Immhit,0,game->music);
            }
            tmp = tmp->nextEnemyShip;
        }
        
        indexSquadron = tmpSquadron;
        tmpSquadron = tmpSquadron->nextSquadron;
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
}

void eventCheckCollisionUserShipShootEnnemy(Game * game,SDL_Renderer *renderer) {
    customLog(0 , "GAME" ,  __func__);
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
                if (indexListShoot->visible == VISIBLE && checkCollision(*(indexList->rectangle), *(indexListShoot->rectangle), indexListShoot->speed) == TRUE) {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "TIR !!! BOOOOOOOMMMMMM!!!!!"  );
                    if(game->score%levelUp == 0 && levelUp <=  game->score)
                    {
                        IncrementPower(game->myShip);
                    }

                    indexList->life -= 1;
                    if (indexList->life <= 0) {
                        
                       // onDestroy(indexList->posX, indexList->posY, renderer);
                        setEnemyToInvisible(indexList);
                        //tmpSquadron->size--;
                        setVisibilitySquadron(tmpSquadron);
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
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
}

void eventCheckCollision(Game * game, SDL_Renderer *renderer) {
    customLog(0 , "GAME" ,  __func__);
    // Test pour les collisions
    if (game->size > 0) {
        // if (game->myShip->alive() == 1)
        // {
        
        
        eventCheckCollisionUserShipEnnemyShoot(game, renderer);
        eventCheckCollisionUserShipEnnemyShip(game, renderer);
        eventCheckCollisionUserShipShootEnnemy(game, renderer);
        //}
        
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}

void  moveAllGame(Game * game, SDL_Renderer *renderer)
{
    customLog(0 , "GAME" ,  __func__);
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
            if(game->tempsActuel - game->tempsPrecedent > Time_app)
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
        moveSquadron(tmp,game->width,game->height,game->listShootEnnemy,game->tie_shoot,game->music);
        tmp= tmp->nextSquadron;
    }
    
    //  __android_log_print(ANDROID_LOG_DEBUG, "GAME", "END moveAllGame ");
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
}


void MyPlaySample(int channel,Mix_Chunk  * sample, int loop,int playMusic )
{
    if(playMusic == 1)
        Mix_PlayChannel(-1,sample,0);
}

void  drawGame(SDL_Renderer* renderer ,Game * game)
{
    customLog(0 , "GAME" ,  __func__);
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
        renderHighScore(game,renderer);
    }
    renderLife(game,renderer);
    //   __android_log_print(ANDROID_LOG_DEBUG, "GAME", "END drawGame ");
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}



void removeNotVisibleSquadronFromGame(Game * game)
{
    customLog(1 , "GAME" ,  __func__);
   // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "game size %d" ,game->size );
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "removeNotVisibleSquadronFromGame"  );
    Squadron  *tmp;
    Squadron  *previous;
    Squadron  *next;
    
    
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG1"  );
    if(game != NULL && game->nextSquadron != NULL)
    {
      //  __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG2"  );
        if(game->nextSquadron->nextSquadron == NULL)
        {
            removeNotVisibleEnemy((game->nextSquadron));
         //   __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG3"  );
            if(game->nextSquadron->visible == INVISIBLE || game->nextSquadron->size <= 0)
            {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG4"  );
                
                freeSquadron(game->nextSquadron);
                game->nextSquadron = NULL;
                game->size--;
            }
        }
        else
        {
            //  __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG5"  );
            tmp = game->nextSquadron;
            previous = NULL;
            Squadron  *next;
            
            while(tmp != NULL)
            {
                    removeNotVisibleEnemy(tmp);
                 __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG6"  );
             //    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "VISIBLE %d",tmp->visible  );
                 __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "size Squadron %d",tmp->size  );
                if(tmp->visible == INVISIBLE || tmp->size <= 0)
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
                    
                 //    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "FLAG11"  );
                    previous = tmp;
                    tmp= tmp->nextSquadron;
                }
            }
        }
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    //  __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END removeNotVisibleSquadronFromGame"  );
    //   __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END removeNotVisibleSquadronFromGame"  );
}

void  createNextSquadron(Game * game)
{
    customLog(0 , "GAME" ,  __func__);
    //   __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "START createNextSquadron"  );

       // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "PAIRE"  );
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
        ListePosition * lps = initializeListePosition();
        for(n = 0 ; n < nbrEnnemy ; n++)
        {
            addNewEnemy(game,squad,lps);
            MyPlaySample(-1,  game->tie_arrive, 0 ,game->music);
        }
    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "newSquadron size %d" ,squad->size );
        freeListePosition(lps);
        
        game->cntInLastSquadron = nbrEnnemy;
    
    game->size++;
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}

void addNewEnemy(Game * game,Squadron * squadron,ListePosition * lp)
{
    customLog(0 , "GAME" ,  __func__);
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "addNewEnemy"  );
    int side = 0;
    int posStart = 0;
    Position * pos  = NULL;
    unsigned int randomPosition  = 0;
    if(lp->size > 1)
        randomPosition =abs( my_rand()%lp->size);
    pos = getPositionAtIndex(randomPosition,lp);
    
    side = pos->side;
    posStart = pos->position;
    removePositionAtIndex(randomPosition, lp);
    int shotLevel = my_rand()% maxShotLevelEnemi;
    if(shotLevel == 0)
        shotLevel++;
    
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
    
    EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,posStart, side,distance,verticalLine,typeShip,typeMovement,shotLevel);
    History *history =  initializeHistory(posStart,side,distance ,verticalLine,typeShip,typeMovement,shotLevel);
    addHistory(history,game->stack);
    
    addEnemyToSquadron(enemy,squadron);
    
    //  __android_log_print(ANDROID_LOG_DEBUG, "GAME", "End addEnemy");
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
}


void addEnemyFromHistory(Game * game)
{
    customLog(0 , "GAME" ,  __func__);
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
        EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,tmp->LastPosStart, (-1)*tmp->LastSide,tmp->LastDistance,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement,tmp->LastShotLevel);
        
        History *history =  initializeHistory(tmp->LastPosStart,(-1)* (tmp->LastSide),tmp->LastDistance ,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement,tmp->LastShotLevel);
        
        addEnemyToSquadron(enemy,lastSqdr->nextSquadron);
        
        addHistory(history,game->stack);
        tmp = tmp->nextHistory;
        
        
    }
    
    game->history++;
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    //    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END addEnemyFromHistory"  );
}

int checkCollision(SDL_Rect a, SDL_Rect b, int speed )
{
    customLog(0 , "GAME" ,  __func__);
    
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
    if( bottomA <= topB)
    {
        // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "botA : %d <= topB : %d", bottomA,  topB);
        return FALSE;
    }
    
    if( topA >= bottomB )
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
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
    return TRUE;
}

Squadron * getLastSquadron(Game * game)
{
    customLog(0 , "GAME" ,  __func__);
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
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
    return indexSquadron;
}

int my_rand()
{
    customLog(0 , "GAME" ,  __func__);
    time_t t;
    int tick = SDL_GetTicks();
    srand((unsigned) time(&t));
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
    return rand() * tick * 7;
}

void onDestroy(int posx, int posy, SDL_Renderer *renderer) {
    customLog(0 , "GAME" ,  __func__);
    //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "onDestroy avant sprite"  );
    SpriteExplosion explosion = LoadSpriteForExplostion(2, renderer);
    SDL_Rect test = {  posx, posy, 100 , 100  };
    
    //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "onDestroy avant renderer"  );
    SDL_RenderCopyEx(renderer, explosion.texture, &(explosion.image_location), &test, explosion.angle, NULL, SDL_FLIP_NONE);
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}

// Fonction d'affichage du sprite pour l'explosion (Pas au point...)
SpriteExplosion LoadSpriteForExplostion(int image, SDL_Renderer *renderer)
{
    customLog(0 , "GAME" ,  __func__);
    
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
    result->surface = SDL_LoadBMP("../assets/explosion.bmp");
    if (result->surface == NULL)
    {
        return (*result);
    }
    /* Create texture from the image */
    result->texture = SDL_CreateTextureFromSurface(renderer, result->surface);
    if (!result->texture) {
        
        
        SDL_FreeSurface(result->surface);
        return (*result);
    }
    
    
    SDL_FreeSurface(result->surface);
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
    return (*result);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    customLog(0 , "GAME" ,  __func__);
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}


void playRumble(Game * game,enum RumbleForce force,enum RumbleLength length)
{
    customLog(0 , "GAME" ,  __func__);
    if(game->vibration == TRUE)
    {
        float frc = (float)(quotientForce * force);
        float lgth = (float)(quotientTemps * length);
        
        /*  if( SDL_HapticRumblePlay( game->gControllerHaptic, frc, lgth ) != 0 && game->initRumble == 1)
         {
         __android_log_print(ANDROID_LOG_DEBUG, "GAME", "Warning: Unable to play rumble! %s\n", SDL_GetError() );
         }
         */
        
        JNIEnv *jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
        
        jobject jni_activity = (jobject)SDL_AndroidGetActivity();
        
        jclass jni_class= (*jni_env)->GetObjectClass(jni_env,jni_activity);
        
        jmethodID methID= (*jni_env)->GetMethodID(jni_env, jni_class , "Rumble","()V");
        
        (*jni_env)->CallVoidMethod(jni_env,jni_activity,methID);
    }
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);

}

void filterShootsFromGame(Game * game)
{
    customLog(0 , "GAME" ,  __func__);
    
    filterMyShoots(game->listShootUser);
    filterMyShoots(game->listShootEnnemy);
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}


void IncrementPower(UserShip * ship )
{
     customLog(0 , "GAME" ,  __func__);
    
    levelUp = levelUp * levelUp;
    addSpeed( ship);
    Time_app -= 50;
    addShotLevel( ship );
    if(maxShotLevelEnemi < MAX_POWER)
        maxShotLevelEnemi++;
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    

}

void decreasePower(UserShip * ship)
{
    customLog(0 , "GAME" ,  __func__);
    if(levelUp > LIMIT_LEVEL_UP)
        levelUp /= levelUp ;
    decreaseShotLevel(ship);

    decreaseSpeed(ship);
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
}


