//
//  game.c
//
//
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



//Niveau actuel pour un LevelUp
int level = 0;

//Prochain Niveau pour un LevelUp
int levelUp = 80;

// Temps d'apparition d'un énemie
int Time_app = ApparitionTime;
//Le nombre de tir maximum d'un énemie
int maxShotLevelEnemi = 1 ;


/**
 *Fonction d'initialisation du jeu
 *
 ***/
Game *  initialisationOfTheGame(int width,int height,char * nativeName,int command,int music,int vibration,int highScore)
{
    /***********************************/
    customLog(0, "GAME" ,  __func__);
    /***********************************/
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
    //game->stack = initializeStackHistory();
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
    
    if(TTF_Init() == -1)        //L'initialisation de TTF à échoué
    {
        game->initText = -1;
        //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Erreur d'initialisation de TTF_Init : %s",TTF_GetError());
    }
    else
    {
        game->initText = 0;
        game->police = NULL;
        game->police =  TTF_OpenFont("game_over.ttf", 65);
        if(game->police == NULL)        //TTF_OpenFont n'a pas réussi a charger la police
            game->initText = -1;
    }
    
    //Initialisation du son
    initialisationSound(game);
    //Si le le son est initialisé
    if(game->initAudio != -1)
        playMusic(game->mainMusic,-1,game);
    
    /***************************************/
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0, "GAME" , str);
    free(str);
    /**************************************/
    return game;
    
}


void initialisationSound( Game * game)
{
    
    customLog(0, "GAME" ,  __func__);
    game->initAudio = 1;
    
    
    if(SDL_Init(SDL_INIT_AUDIO)==-1)
    {
        // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Audio Error : Failed to init SDL_INIT_AUDIO");
        game->initAudio = -1;
    }
    else
    {
        int flags=MIX_INIT_MP3;         //Permettre la lecture de mp3
        int initted=Mix_Init(flags);
        if(initted&flags != flags) {
            // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Audio Error : Failed to init required suppord ");
            // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "Audio Error : Mix_Init: %s\n", Mix_GetError() );
            game->initAudio = -1;
        }
        else
        {
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )     //Initialisatin du son avec une fréquence de 22050
            {
                __android_log_print(ANDROID_LOG_DEBUG, "GAME", "Mix_OpenAudio ERROR");
                game->initAudio = -1;
            }
            else
            {
                
                if(Mix_SetMusicCMD(NULL)==-1) {
                    __android_log_print(ANDROID_LOG_DEBUG, "GAME", "Mix_SetMusicCMD");
                }
                else
                {
                    /****************************************************/
                    //Chargement des fichiers wav
                    
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
                    
                    game->yoda = Mix_LoadWAV("swnotry.wav");
                    if(!game->yoda)
                    {
                        __android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_LoadWAV: %s\n", Mix_GetError());
                        game->initAudio = -1;
                        
                    }
                    else
                    {
                        Mix_VolumeChunk( game->yoda , MIX_MAX_VOLUME - MIX_MAX_VOLUME/3);
                    }
                    
                    /*******************************************************/
                    
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

/******
 *Procédure permettant de jouer une musique
 *
 *
 *///

void playMusic(Mix_Music *mainMusic,int cntRepeat,Game * game)
{
    customLog(0, "GAME" ,  __func__);
    if(game->music == 1)
    {
        if(Mix_PlayMusic(mainMusic, cntRepeat)==-1) {
            //__android_log_print(ANDROID_LOG_DEBUG, "GAME","Mix_PlayMusic: %s\n", Mix_GetError());
            // well, there's no music, but most games don't break without music...
        }
    }
    Mix_VolumeMusic(125);
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
}


/************
 *
 *Procédure gérant la collision entre le vaisseau de l'utilisateur et les tirs ennemies
 *
 ************/
void eventCheckCollisionUserShipEnnemyShoot(Game * game,SDL_Renderer *renderer) {
    
    customLog(0 , "GAME" ,  __func__);
    //récupération des tirs énnemies
    Shoot * indexList = game->listShootEnnemy->start;
    
    Shoot *tmp = indexList;
    while(tmp)
    {
        indexList = tmp;
        //Si le tir est visible et que la collision est effectué
        if (indexList->visible == VISIBLE && checkCollision(*(game->myShip->rectangle), *(indexList->rectangle), indexList->speed) == TRUE) {
            
            decreaseLife( game->myShip );           //Réduction de la vie du vaisseau de l'utilisateur
            
            enum RumbleForce force = MEDIUM_FORCE;
            enum RumbleLength length = MEDIUM_LENGTH;
            playRumble(game,force,length);          //Vibrer
            MyPlaySample(-1,game->Immhit,0,game->music);    //Jouer un sample
            decreasePower(game->myShip);            //réduire la puissance du vaisseau
            
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
/************
 *
 *Procédure gérant la collision entre le vaisseau de l'utilisateur et les vaisseau ennemies
 *
 ************/
void eventCheckCollisionUserShipEnnemyShip(Game * game,SDL_Renderer *renderer) {
    
    
    customLog(0 , "GAME" ,  __func__);
    
    //récupération de la liste chainées des escouades
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
                
                setEnemyToInvisible(indexList);
                decreasePower(game->myShip);
                
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
/************
 *
 *Procédure gérant la collision entre les tirs ddu vaisseau de l'utilisateur et les énnemies
 *
 ************/
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
                if (indexListShoot->visible == VISIBLE && checkCollision(*(indexList->rectangle), *(indexListShoot->rectangle), indexListShoot->speed) == TRUE) {
                    //__android_log_print(ANDROID_LOG_DEBUG, "GAME",   "TIR !!! BOOOOOOOMMMMMM!!!!!"  );
                    if(levelUp < level)
                    {
                        IncrementPower(game->myShip);
                        MyPlaySample(-1,game->yoda,0,game->music);
                    }
                    
                    indexList->life -= 1;
                    if (indexList->life <= 0) {
                        
                        // onDestroy(indexList->posX, indexList->posY, renderer);
                        setEnemyToInvisible(indexList);
                        //tmpSquadron->size--;
                        setVisibilitySquadron(tmpSquadron);
                        addScore(*indexList,&(game->score));
                        addScore(*indexList,&level);
                        
                    }
                    indexListShoot->visible = INVISIBLE;
                }
                tmpShoot = tmpShoot->nextShoot;
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
/************
 *
 *Procédure général de gestion des collisions
 *
 ************/
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
/************
 *
 *Procédure de déplacement des éléments dans le jeu
 *
 ************/
void  moveAllGame(Game * game, SDL_Renderer *renderer)
{
    customLog(0 , "GAME" ,  __func__);
    eventCheckCollision(game, renderer); //gestion des collisions
    if(myShipContinousShoot(game->myShip) == TRUE)      //Si le vaisseau tir en continue
    {
        UserShipShoot(*(game->myShip),game->listShootUser);     //Tir de l'utilisateur
        MyPlaySample(-1,game->Xwing_shoot,0,game->music);       //Jouer un sample pour les tirs
    }
    
    moveAllMyShoots(game->listShootUser,game->width,game->height);  //Bouger tout les tirs
    moveAllMyShoots(game->listShootEnnemy,game->width,game->height);    //de l'utilisateur et des énnemies
    
    
    game->tempsActuel = SDL_GetTicks();         //Récupération du nombre de ticks actuel
    if(game->size == 0)                         //Si le jeu démarre
    {
        createNextSquadron(game);               //Création d'une escouade
    }
    else
    {
        /***
         * création  d'une nouvelle escouade
         *
         */
        Squadron *tmp = game->nextSquadron;
        int size = game->size;
        int index = 0;
        
        if(game->tempsActuel - game->tempsPrecedent > Time_app)
        {
            createNextSquadron(game);
            game->tempsPrecedent = game->tempsActuel;
            
        }
        tmp= tmp->nextSquadron;
        index++;
        
    }
    //Déplacement de toutes les escouades
    Squadron *tmp =  game->nextSquadron;
    while(tmp)
    {
        moveSquadron(tmp,game->width,game->height,game->listShootEnnemy,game->tie_shoot,game->music);
        tmp= tmp->nextSquadron;
    }
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
}

/***
 *Procdéure pouer jouer les samples
 **/
void MyPlaySample(int channel,Mix_Chunk  * sample, int loop,int playMusic )
{
    if(playMusic == 1)
        Mix_PlayChannel(-1,sample,0);
}
/***
 *
 *Procédure pour déssiner les éléments du jeu
 **/
void  drawGame(SDL_Renderer* renderer ,Game * game)
{
    customLog(0 , "GAME" ,  __func__);
    //Déssiner les tirs
    drawAllMyShoots(renderer,game->listShootUser);
    drawAllMyShoots(renderer,game->listShootEnnemy);
    //Déssiner le vaisseau
    drawMyShip(renderer , game->myShip);
    
    if(game->size > 0)
    {
        Squadron * squadron;
        squadron = game->nextSquadron;
        while(squadron)
        {
            //Déssiner les escouades
            drawMySquadron(renderer,squadron);
            squadron = squadron->nextSquadron;
        }
    }
    if(game->initText != -1)
    {
        //Rendu du texte sur l'"cran
        renderScore(game,renderer);
        renderHighScore(game,renderer);
        renderLife(game,renderer);
    }
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}

/**
 *
 *Suprression des escouades dans la liste
 ***/

void removeNotVisibleSquadronFromGame(Game * game)
{
    customLog(1 , "GAME" ,  __func__);
    Squadron  *tmp;
    Squadron  *previous;
    Squadron  *next;
    
    
    if(game != NULL && game->nextSquadron != NULL)
    {
        //Si il n'existe qu'une escouade
        if(game->nextSquadron->nextSquadron == NULL)
        {
            //On supprime les énnemies non visible dans l'escouade et on décrémente la taille de la liste
            removeNotVisibleEnemy((game->nextSquadron));
            
            //Si l'escouade n'est plus visible ou si la taille de l'escouade est égale à zero
            if(game->nextSquadron->visible == INVISIBLE || game->nextSquadron->size <= 0)
            {
                //Supprime de la mémoire l'escouade
                freeSquadron(game->nextSquadron);
                game->nextSquadron = NULL;
            
                game->size--;
            }
        }
        else
        {
            //On Récupére le début de la liste chainée
            tmp = game->nextSquadron;
            previous = NULL; // index précédent
            Squadron  *next;
            //Tanque que l'index est différent de NULL
            while(tmp != NULL)
            {
                //On supprime les énnemies non visible dans l'escouade et on décrémente la taille de la liste
                removeNotVisibleEnemy(tmp);
                //Si l'escouade n'est plus visible ou si la taille de l'escouade est égale à zero
                if(tmp->visible == INVISIBLE || tmp->size <= 0)
                {
                    //On récupére l'escouade qui sera supprimé
                    Squadron * deletedSquadron = tmp;
                    //On bouge l'index
                    tmp = tmp->nextSquadron;
                    if(previous == NULL)
                    {
                        //SI on est au premier index on décale le prochain index au début de la liste
                        game->nextSquadron = tmp;
                    }
                    else
                    {
                        //Sinon on lie l'index précédent a la prochaine escouade
                        previous->nextSquadron = tmp;
                    }
                    if(deletedSquadron)
                    {
                        //On libère en mémoire l'escouade a supprimer
                        freeSquadron(deletedSquadron);
                    }
                    deletedSquadron = NULL;
                    //On décrémente la taille du jeu
                    game->size--;
                }
                else
                {
                    //Si il n'y avait aucune escouade a supprimer on passe au prochain
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


/***
 *Procédure de création d'une escouade
 *
 **/

void  createNextSquadron(Game * game)
{
    customLog(0 , "GAME" ,  __func__);
    int nombre_aleatoire = 0;
    nombre_aleatoire = my_rand();
    int nbrEnnemy =nombre_aleatoire % MaxEnemy;
    if(nbrEnnemy == 0)
        nbrEnnemy++;
    
    int n = 0;
    int side = 1;
    Squadron * squad;
    /***
     *Création d'une escouade dans la liste chainée
     **/
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
    /**
     *on incrémente l'histoire du jeu
     **/
    game->history++;
    
    /**
     *On Initialise une liste de position qui sera modifier à chaque initialisation d'un énemie afin que deux énemies ne soit jamais créer dans à la même position
     **/
    ListePosition * lps = initializeListePosition();
    for(n = 0 ; n < nbrEnnemy ; n++)
    {
        //Ajout d'un ennemie
        addNewEnemy(game,squad,lps);
        //joue d'un son
        MyPlaySample(-1,  game->tie_arrive, 0 ,game->music);
    }
    //On libère la liste de position
    freeListePosition(lps);
    //On indique le nombre d'ennemis ajouté dans la dernière escoude
    game->cntInLastSquadron = nbrEnnemy;
    //On incrémente la taille du jeu
    game->size++;
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
}
/**
 *Procédure d'ajout des ennemis dans une escouade
 ***/
void addNewEnemy(Game * game,Squadron * squadron,ListePosition * lp)
{
    customLog(0 , "GAME" ,  __func__);
   
    
    /**Définis le coté dans lequel est l'ennemie 1 pour a gauche de l'écran - 1 pour a droite de l'écran**/
    int side = 0;
    int posStart = 0;
    Position * pos  = NULL;
    unsigned int randomPosition  = 0;
    //On récupére un index au hasard dans la liste de position
    if(lp->size > 1)
        randomPosition =abs( my_rand()%lp->size);
    pos = getPositionAtIndex(randomPosition,lp);
    
    side = pos->side;
    posStart = pos->position;
    //On supprime l'élement au même index
    removePositionAtIndex(randomPosition, lp);
    
    //on définis la puissance de tir de l'ennemi
    int shotLevel = my_rand()% maxShotLevelEnemi;
    if(shotLevel == 0)
        shotLevel++;
    
    int tempDividendeDistance = my_rand() % MaxEnemy ;
    if(tempDividendeDistance == 0)
        tempDividendeDistance++;
    /**
     *
     *Distance minimum entre une ligne vertical et l'ennemi
     ***/
    int distance = game->width/tempDividendeDistance ;
    int dividende = my_rand() % 8;
    if(dividende == 0)
        dividende++;
    
    /**
     *
     *Ligne verticale
     ****/
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
    //int typeShip =  my_rand()%4;
    int typeShip =  rand()%4;
    int typeMovement = my_rand() % 3;
    //Initialisation de l'ennemie
    EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,posStart, side,distance,verticalLine,typeShip,typeMovement,shotLevel);
    // History *history =  initializeHistory(posStart,side,distance ,verticalLine,typeShip,typeMovement,shotLevel);
    //addHistory(history,game->stack);
    //Ajout d'un ennemie dans une escouade
    addEnemyToSquadron(enemy,squadron);
    
    //  __android_log_print(ANDROID_LOG_DEBUG, "GAME", "End addEnemy");
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
}
/***
 *Fonction non utilisé permettant d'ajouter un ennemi en fonction des derniers ennemis
 **/

void addEnemyFromHistory(Game * game)
{
    customLog(0 , "GAME" ,  __func__);
       int nombre = game->cntInLastSquadron;
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "cnt in lastSquadron %d",nombre);
    //StackHistory * tempStack=getHeads(game->stack,nombre);
    //History * tmp = tempStack->head;
    Squadron * lastSqdr = getLastSquadron(game);
    
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "size Stack %d",game->stack->size);
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "size tempStack %d",tempStack->size);
    // __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "stack adress %d",tempStack->head);
    lastSqdr->nextSquadron = initialisationSquadron(nombre);
    /* while(tmp != NULL )
     {
     //     __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "history address %d",tmp);
     EnemyShip * enemy = initialisationEnemyShip(game->width,game->height,tmp->LastPosStart, (-1)*tmp->LastSide,tmp->LastDistance,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement,tmp->LastShotLevel);
     
     History *history =  initializeHistory(tmp->LastPosStart,(-1)* (tmp->LastSide),tmp->LastDistance ,tmp->LastverticalLine,tmp->LastypeShip,tmp->LastTypeMovement,tmp->LastShotLevel);
     
     addEnemyToSquadron(enemy,lastSqdr->nextSquadron);
     
     // addHistory(history,game->stack);
     tmp = tmp->nextHistory;
     
     
     }
     
     game->history++;
     char * str = malloc(sizeof(char)* 255);
     sprintf(str,"end %s",__func__);
     customLog(0 , "GAME" , str);
     free(str);
     */
    //    __android_log_print(ANDROID_LOG_DEBUG, "GAME",   "END addEnemyFromHistory"  );
}

/**
 *
 *Fonction indiquant si une collection a eu lieu entre deux rectange
 ***/

int checkCollision(SDL_Rect a, SDL_Rect b, int speed )
{
    customLog(0 , "GAME" ,  __func__);
    
    //les coté d'un rectangle
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calcule des cotés du rectangle A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
     //Calcule des cotés du rectangle B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If les cotés de A sont en dehors de B
    if( bottomA <= topB)
    {
        return FALSE;
    }
    
    if( topA >= bottomB )
    {
        return FALSE;
    }
    
    if( rightA <= leftB )
    {
        
        return FALSE;
    }
    
    if( leftA >= rightB )
    {
        return FALSE;
    }
    
    //Si aucun des cotés sont en dehors de l'autre rectangle
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
    return TRUE;
}
/**
 *
 *Récupération de la dernière escouade
 **/

Squadron * getLastSquadron(Game * game)
{
    customLog(0 , "GAME" ,  __func__);
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
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
    return indexSquadron;
}
/***
 *
 *Nombre aléatoire
 ***/
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
//Fonction non utilisé
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
//Rendu de la texture
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    customLog(0 , "GAME" ,  __func__);
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    //__android_log_print(ANDROID_LOG_DEBUG, "renderTexture",   "FL1"  );
    
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    // __android_log_print(ANDROID_LOG_DEBUG, "renderTexture",   "FL2"  );
    SDL_RenderCopy(ren, tex, NULL, &dst);
    //__android_log_print(ANDROID_LOG_DEBUG, "renderTexture",   "FL3"  );
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    //SDL_DestroyTexture(tex);
}

//jouer une vibration
//a été modifier pour utiliser un callback en java
void playRumble(Game * game,enum RumbleForce force,enum RumbleLength length)
{
    customLog(0 , "GAME" ,  __func__);
    if(game->vibration == TRUE)
    {
        float frc = (float)(quotientForce * force);
        float lgth = (float)(quotientTemps * length);
        
        
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
//Filtrer les tirs dans le jeu
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

//Incrémenter la puissance du vaisseau de l'utilisateur
void IncrementPower(UserShip * ship )
{
    customLog(0 , "GAME" ,  __func__);
    
    levelUp = levelUp * 2;
    addSpeed( ship);
    addShotLevel( ship );
    if(maxShotLevelEnemi < MAX_POWER)
        maxShotLevelEnemi++;
    
    
    
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
    free(str);
    
    
}
//Décrémenter la puissance du vaisseau de l'utilisateur
void decreasePower(UserShip * ship)
{
    customLog(0 , "GAME" ,  __func__);
    
    if(levelUp > LIMIT_LEVEL_UP)
    {
        levelUp /= 2 ;
        level /= 2;
    }
    
    decreaseShotLevel(ship);
    
    decreaseSpeed(ship);
    char * str = malloc(sizeof(char)* 255);
    sprintf(str,"end %s",__func__);
    customLog(0 , "GAME" , str);
}


