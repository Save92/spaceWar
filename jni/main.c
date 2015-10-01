#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "./SDL/src/core/android/SDL_android.h"
#include "SDL.h"
#include <android/log.h>
#include <jni.h>
#include "./user/user.h"
#include <math.h>
#include <stdlib.h>


float accelValues[3];
#define SIZEACCELVALUES 2
typedef struct Sprite
{
    SDL_Texture* texture;
    Uint16 w;
    Uint16 h;
} Sprite;



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
Sprite LoadSprite(const char* file, SDL_Renderer* renderer)
{
    Sprite result;
    result.texture = NULL;
    result.w = 0;
    result.h = 0;

    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return result;
    }
    result.w = temp->w;
    result.h = temp->h;

    /* Create texture from the image */
    result.texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!result.texture) {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return result;
    }
    SDL_FreeSurface(temp);

    return result;
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
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);
/*
    Sprite sprite = LoadSprite("image.bmp", renderer);
    if(sprite.texture == NULL)
        exit(2);
*/
    
    int *widthScreen = malloc (sizeof(int));
    int *heightScreen = malloc (sizeof(int));
    SDL_GetWindowSize(window,widthScreen,heightScreen);
    __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip", "02");
    UserShip * myShip = initialisationUserShip(*widthScreen,*heightScreen);
    __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip", "01");
    drawMyShip(renderer , myShip);
    //= malloc (sizeof(Shoot)) ;
    ListShoot * listShoot = malloc(sizeof(ListShoot)) ;
    if(listShoot == NULL)
        return;
    
    
    listShoot->size = 0;
    __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip", "03");
    listShoot->start = NULL;
    /*listShoot->start = malloc(sizeof(listShoot));
    if(listShoot->start == NULL)
        return;
     */


    /* Main render loop */
    Uint8 done = 0;
    SDL_Event event;
    SDL_PumpEvents();
    
    while(!done)
    {
        SDL_RenderClear(renderer);
       

        /* Check for events */
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_FINGERDOWN)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip", "SLD_FINGERDOWN");
                myShipShoot(*myShip,listShoot);
                  __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip", "Ship position PosX : %d , PosY : %d",(*listShoot->start).posX,(*listShoot->start).posY);
                
                
            } else if (event.type == SDL_KEYDOWN) {
                done = 1;
            }
        }
        __android_log_print(ANDROID_LOG_DEBUG, "SpaceShip", "Android_JNI_GetAccelerometerValues");
        Android_JNI_GetAccelerometerValues(accelValues);
        moveAllMyShoots(listShoot,0,*widthScreen,*heightScreen);
        drawAllMyShoots(renderer,listShoot);
        moveMyShipGeneral(accelValues,SIZEACCELVALUES,myShip,*widthScreen,*heightScreen);
        __android_log_print(ANDROID_LOG_DEBUG, "moveMyShipGeneral",  "Vaisseau posX : %d posY :%d",  myShip->posX ,myShip->posY);

        drawMyShip(renderer , myShip);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
        filterMyShoots(listShoot);
        __android_log_print(ANDROID_LOG_DEBUG, "stopFilter",  "Shots filtered");
    }
    freeShip(myShip);
    exit(0);
}
