#include "texture.h"

#include <SDL2/SDL_image.h>

#include <stdio.h>

/* Load individual image as texture */
SDL_Texture*
Texture_Load(SDL_Renderer *renderer, const char *path)
{
    SDL_Texture *texture = NULL;

    SDL_Surface *surface = IMG_Load(path);
    if(surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path, IMG_GetError());
    } else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(texture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                   path, SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }

    return texture;
}

#ifdef _SDL_TF_H
SDL_Texture*
Texture_FromText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if(surface == NULL) {
        printf("Unable to reander text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    } else {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(texture == NULL) {
            printf("Unable to create texture from render text! SDL Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(surface);
        return texture;
    }
}
#endif


bool
Texture_RenderEx(SDL_Texture *texture,
                 SDL_Renderer *renderer,
                 int x, int y,
                 SDL_Rect *clip,
                 double angle,
                 SDL_Point *center,
                 SDL_RendererFlip flip)
{
    int w, h;
    /* Query width and height of texture */
    if(SDL_QueryTexture(texture, NULL, NULL, &w, &h) < 0) {
        /* on error */
        printf("Unable to query texture. SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Rect rect = { x, y, w, h};
    if(clip) {
        rect.w = clip->w;
        rect.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip);
    return true;
}

bool
Texture_Render(SDL_Texture *texture,
               SDL_Renderer *renderer,
               int x, int y,
               SDL_Rect *clip)
{
    return Texture_RenderEx(texture, renderer, x, y, clip, 0.0, NULL, SDL_FLIP_NONE);
}

void Texture_Free(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
}
