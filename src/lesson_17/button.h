#ifndef BUTTON_H
#define BUTTON_H

/* for SDL_Event */
#include <SDL2/SDL.h>
#include <stdbool.h>

enum {
    BUTTON_WIDTH = 300,
    BUTTON_HEIGHT = 200,
};

struct Button {
    int x;
    int y;
    int w;
    int h;
    int sprite;
};
bool Button_InitSprite(SDL_Renderer *render, const char *imgpath);
void Button_Init(struct Button *button);
void Button_SetPoisiton(struct Button *button, int x, int y);
void Button_HandleEvent(struct Button *button, SDL_Event *e);
void Button_Render(struct Button *button, SDL_Renderer *renderer);

#endif
