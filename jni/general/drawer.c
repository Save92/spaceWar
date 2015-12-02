
#include "drawer.h"

Sprite littleEnemyImg;
Sprite littleBomberEnemyImg;
Sprite interceptorEnemyImg;
Sprite bigBomberEnemyImg;
Sprite userShipImg;

Sprite LoadSprite(const char* file, SDL_Renderer* renderer)
{
    Sprite result;
    result.texture = NULL;
    result.w = 0;
    result.h = 0;

    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);

    SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0, 0, 0));
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

Sprite loadTexture(const char* file, SDL_Renderer *renderer)
{
    //The final texture
    Sprite result;
    result.texture = NULL;
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(file);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", file, "nop");
    }
    else
    {
        //Create texture from surface pixels
        result.texture = SDL_CreateTextureFromSurface( /*gRenderer*/ renderer, loadedSurface );
        if( result.texture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return result;
}

void loadImages(SDL_Renderer* renderer) {
    littleEnemyImg = loadTexture("littleEnemy.png", renderer);
    littleBomberEnemyImg = loadTexture("littleBomberEnemy.png", renderer);
    interceptorEnemyImg = loadTexture("interceptorEnemy.png", renderer);
    bigBomberEnemyImg = loadTexture("bigBomberEnemy.png", renderer);
    userShipImg =  loadTexture("myShipGood.png", renderer);
        
}

Sprite getLittleEnemyImg() {
    return littleEnemyImg;
}

Sprite getLittleBomberImg() {
    return littleBomberEnemyImg;
}

Sprite getInterceptorImg() {
    return interceptorEnemyImg;
}

Sprite getBigBomberImg() {
    return bigBomberEnemyImg;
}


Sprite getUserShipImg() {
    return userShipImg;
}