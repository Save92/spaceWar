
#include "./general/constant.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "./SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include <android/log.h>
#include <jni.h>
#include "./general/drawer.h"
#include "./user/user.h"
#include "./enemy/generalEnemy.h"
#include "./general/general.h"
#include <math.h>
#include "./enemy/squadron.h"
#include "./general/game.h"


float accelValues[3];
#define SIZEACCELVALUES 2
// typedef struct Sprite
// {
//     SDL_Texture* texture;
//     Uint16 w;
//     Uint16 h;
// } Sprite;
static const char *nativeName;
static int command;
static int music;
static int vibration;
static int highScore;







void drawCircle(SDL_Renderer* renderer,int x_centre,int y_centre,int rayon)
{
    
    int x = 0;
    int y = rayon;
    int m = 5 - 4 * rayon;
    while(x <= y)
    {
        SDL_RenderDrawPoint(renderer, x+x_centre ,y+y_centre);
        SDL_RenderDrawPoint(renderer, y+x_centre , x+y_centre);
        SDL_RenderDrawPoint(renderer, -x+x_centre, y+y_centre );
        SDL_RenderDrawPoint(renderer, -y+x_centre, x+y_centre );
        SDL_RenderDrawPoint(renderer, x+x_centre, -y+y_centre );
        SDL_RenderDrawPoint(renderer, y+x_centre, -x+y_centre );
        SDL_RenderDrawPoint(renderer, -x+x_centre, -y+y_centre );
        SDL_RenderDrawPoint(renderer, -y+x_centre, -x+y_centre );
        if( m > 0)
        {
            y--;
            m = m - 8 *y;
        }
        x = x +1;
        m = m + 8 *x +4;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
    SDL_Delay(0);
    
}




/* Adapted from SDL's testspriteminimal.c */
// Sprite LoadSprite(const char* file, SDL_Renderer* renderer)
// {
//     Sprite result;
//     result.texture = NULL;
//     result.w = 0;
//     result.h = 0;

//     SDL_Surface* temp;

//     /* Load the sprite image */
//     temp = SDL_LoadBMP(file);
//     if (temp == NULL)
//     {
//         fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
//         return result;
//     }
//     result.w = temp->w;
//     result.h = temp->h;

//     /* Create texture from the image */
//     result.texture = SDL_CreateTextureFromSurface(renderer, temp);
//     if (!result.texture) {
//         fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
//         SDL_FreeSurface(temp);
//         return result;
//     }
//     SDL_FreeSurface(temp);

//     return result;
// }

jint Java_esgi_fouriam_SDLActivity_setPref(JNIEnv * env, jobject thiz, jstring name, jint commandValue, jint musicValue, jint vibrationValue, jint score){
    
    __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "--------------------------------------------------------------------");
    
    nativeName = (*env)->GetStringUTFChars(env, name, 0);
    // use your string
    (*env)->ReleaseStringUTFChars(env, name, nativeName);
    
    command = commandValue;
    music = musicValue;
    vibration = vibrationValue;
    highScore = score;
   /* __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "RECEIVE name : %s", nativeName);
    __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "RECEIVE music : %d", music);
    __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "RECEIVE command : %d", command);
    __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "RECEIVE vibration : %d", vibration);
    __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "RECEIVE highscore : %d", highScore);
    __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "--------------------------------------------------------------------");
    */
    
}



void gameOver(Game* game) {
    //@TDOD Afficher le texte Game over
    //__android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "GAME OVER : %s", nativeName);
    // (*jni_env)->CallVoidMethod(jni_env,jni_activity,methID, score);
    if(game->saveNewHighScore == TRUE) {
        JNIEnv *jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
        jobject jni_activity = (jobject)SDL_AndroidGetActivity();
        jclass jni_class= (*jni_env)->GetObjectClass(jni_env,jni_activity);
        jmethodID methID= (*jni_env)->GetMethodID(jni_env, jni_class , "setHighScore","(I)V");
        (*jni_env)->CallVoidMethod(jni_env,jni_activity,methID, game->score);
        
    }
    
}




void print_gameOver(Game * game,SDL_Renderer * renderer)
{
    SDL_Color couleur= {255, 255, 255};
    char str[255];
    sprintf(str, "Game Over");
    SDL_Surface *surf = TTF_RenderText_Blended(game->police, str, couleur);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surf);
    int iW, iH;
    SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
    int x = 0 + (game->width/2);
    int y = 0 + (game->height/2);
    renderTexture(texture, renderer, x, y);
}

void draw(SDL_Window* window, SDL_Renderer* renderer, const Sprite sprite)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect destRect = {w/2 - sprite.w/2, h/2 - sprite.h/2, sprite.w, sprite.h};
    /* Blit the sprite onto the screen */
    SDL_RenderCopy(renderer, sprite.texture, NULL, &destRect);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    Sprite background;
    int posX = 0;
    int posY = 0;
    
    int SCREEN_FPS = 60;
    int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    
    if(SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);
    
    
    
    
    int *widthScreen = malloc (sizeof(int));
    int *heightScreen = malloc (sizeof(int));
    SDL_GetWindowSize(window,widthScreen,heightScreen);
    // load our image
    background = loadTexture("background.png", renderer);
    
    
    
    Game * game = initialisationOfTheGame( *widthScreen,*heightScreen,nativeName,command,music,vibration,highScore);
    loadImages(renderer);
    
    /* Main render loop */
    Uint8 done = 0;
    SDL_Event event;
    SDL_PumpEvents();
    
    
    
    //Start counting frames per second
    //int countedFrames = 0;
    int frameTicksAtStart;
    int frameTicksAtEnd;
    
    int startMoving = FALSE;
    if(command == TOUCH_GESTION)
    {
        game->myShip->canShoot = TRUE;
    }

    while(!done)
    {
      
        frameTicksAtStart  = SDL_GetTicks();
        SDL_RenderClear(renderer);

        
        if (game->myShip->life <= 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "MAIN",   "IN_GAMEOVER");
            gameOver(game);
            //renderTexture(background.texture, renderer, 0, 0);
            print_gameOver(game,renderer);
            while(SDL_PollEvent(&event))
            {
                if(event.type ==  SDL_KEYDOWN)
                    done = 1;
            }
        }
        else
        {
            renderTexture(background.texture, renderer, 0, 0);
            /* Check for events */
            while(SDL_PollEvent(&event))
            {
                if(event.type ==  SDL_KEYDOWN)
                    done = 1;
                if(command == ACCEL_GESTION )
                {
                    if(event.type ==  SDL_FINGERDOWN)
                        game->myShip->canShoot = TRUE;
                    if(event.type ==  SDL_FINGERUP)
                        game->myShip->canShoot = FALSE;
                }
                else
                {
                    if(command == TOUCH_GESTION )
                    {
                        if( event.type == SDL_MOUSEMOTION )
                        {
                            startMoving = TRUE;
                            posX = event.motion.x ;
                            posY = event.motion.y;
                        }
                        if(event.type ==  SDL_FINGERUP)
                            startMoving = FALSE;
                    }
                }
            }

            Android_JNI_GetAccelerometerValues(accelValues);
            moveAllGame(game, renderer);
            if(command == ACCEL_GESTION)
                moveMyShipGeneral(accelValues,SIZEACCELVALUES,game->myShip,*widthScreen,*heightScreen);
            else
            {
                if(command == TOUCH_GESTION && startMoving == TRUE)
                {
                    moveMyShipTouch(posX, posY,game->myShip, *widthScreen,*heightScreen);
                }
            }
            
            drawGame(renderer,game);
            SDL_RenderPresent(renderer);
            removeNotVisibleSquadronFromGame(game);
            filterShootsFromGame( game);
            //countedFrames++;
            frameTicksAtEnd = SDL_GetTicks();
            int frameTicks = frameTicksAtEnd - frameTicksAtStart;
            if( frameTicks < SCREEN_TICKS_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
                //SDL_Delay(10);
            }
        }
        
        //  __android_log_print(ANDROID_LOG_DEBUG, "stopFilter",  "Shots filtered");
        
    }
    freeShip(game->myShip);
    exit(0);
}
