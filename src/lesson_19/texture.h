#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

/* Load individual image as texture */
SDL_Texture * Texture_Load(SDL_Renderer *renderer, const char *path);

#ifdef _SDL_TF_H
/* Load a text rendered texture */
SDL_Texture * Texture_FromText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color);
#endif

/* Render Texture to render at specific position */
bool Texture_Render(SDL_Texture *texture,
                    SDL_Renderer *renderer,
                    int x, int y,
                    SDL_Rect *clip);
bool Texture_RenderEx(SDL_Texture *texture,
                      SDL_Renderer *renderer,
                      int x, int y,
                      SDL_Rect *clip,
                      double angle,
                      SDL_Point *center,
                      SDL_RendererFlip flip);

void Texture_Free(SDL_Texture *texture);


#endif
