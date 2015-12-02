//
//  score.c
//  
//
//  Created by thierry allard saint albin on 19/11/2015.
//
//

#include "score.h"
#include "./game.h"


void renderScore(Game * game,SDL_Renderer *renderer)
{
    SDL_Color couleur= {255, 255, 255};
    char str[255];
    sprintf(str, "Score : %d", game->score);
    SDL_Surface *surf = TTF_RenderText_Blended(game->police, str, couleur);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surf);
    int iW, iH;
    SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
    int x = 0 + (game->width/10);
    int y = 0 + (game->height/10);
    renderTexture(texture, renderer, x, y);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    
}


void renderHighScore(Game * game,SDL_Renderer *renderer)
{
    SDL_Color couleur= {255, 255, 255};
    char str[255];
    if(game->PreviousHighScore > game->score)
    {
        sprintf(str, "HighScore : %d ", game->PreviousHighScore);
    
    }
    else
    {
        sprintf(str, "HighScore : %d ", game->score);
        if(game->saveNewHighScore == FALSE)
            game->saveNewHighScore = TRUE;
    }
    SDL_Surface *surf = TTF_RenderText_Blended(game->police, str, couleur);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surf);
    int iW, iH;
    SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
    int x = 0 + (game->width/2);
    int y = 0 + (game->height/10);
    renderTexture(texture, renderer, x, y);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}



void addScore(EnemyShip enemy, int * score )
{
    switch(enemy.typeShip)
    {
        case 0 :   *score += 10;
            break;
        case 1 :   *score += 20;
            break;
        case 2 :   *score += 30;
            break;
        case 3 :   *score += 40;
            break;

        default : *score += 10;
            break;
    }
}