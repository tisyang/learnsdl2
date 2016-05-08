#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdbool.h>
#include <stdio.h>
#include <math.h>


#include "button.h"
#include "texture.h"

enum {
    SCREEN_WIDTH = 640,
    SCREEN_HEIGHT = 480,
};

#define TOTAL_BUTTONS 4


/* Start up SDL and creates window */
static bool init();
/* Loads media */
static bool load_media();
/* Frees media and shuts down SDL */
static void close();

static const char * const G_WIN_CAPTION = "Lesson 17: Mouse Events";
SDL_Window   *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
static struct Button g_buttons[TOTAL_BUTTONS];

static bool
init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!\n");
    }
    /* Create window */
    g_window = SDL_CreateWindow(G_WIN_CAPTION,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(g_renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int img_flags = IMG_INIT_PNG;
    /* see IMG_Init doc */
    if((IMG_Init(img_flags) & img_flags) != img_flags) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        return false;
    }

    return true;
}

static bool
load_media()
{
    if(Button_InitSprite(g_renderer, "buttonsprite.png") == false) {
        printf("Could not load button sprites\n");
        return false;
    }
    for(int i = 0; i < TOTAL_BUTTONS; i++) {
        Button_Init(&g_buttons[i]);
    }
    Button_SetPoisiton(&g_buttons[0], 0, 0);
    Button_SetPoisiton(&g_buttons[1], BUTTON_WIDTH, 0);
    Button_SetPoisiton(&g_buttons[2], 0, BUTTON_HEIGHT);
    Button_SetPoisiton(&g_buttons[3], BUTTON_WIDTH, BUTTON_HEIGHT);

    return true;
}

static void
close()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[])
{
    if(init() == false) {
        printf("Failed to initialize!\n");
        return 1;
    }
    if(load_media() == false) {
        printf("Failed to load media!\n");
        return 1;
    }
    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            for(int i = 0; i < TOTAL_BUTTONS; i++) {
                Button_HandleEvent(&g_buttons[i], &e);
            }
        }
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);

        for(int i = 0; i < TOTAL_BUTTONS; i++) {
            Button_Render(&g_buttons[i], g_renderer);
        }

        SDL_RenderPresent(g_renderer);
    }
    close();
    return 0;
}
