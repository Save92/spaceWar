//
//  life.c
//  
//
//
//

#include "life.h"

//Fonction d'ecriture de la vie
void renderLife(Game * game,SDL_Renderer *renderer)
{
    SDL_Color couleur= {255, 255, 255};
    char str[255];
    sprintf(str, "Life : %d", game->myShip->life);
    SDL_Surface *surf = TTF_RenderText_Blended(game->police, str, couleur);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surf);
    int iW, iH;
    SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
    int x = 0 + (game->width/10);
    int y = 0 + (game->height/15);
    renderTexture(texture, renderer, x, y);
    
}


