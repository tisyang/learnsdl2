#include "SDL2/SDL.h"
#include <stdbool.h>
#include <stdio.h>

enum {
    SCREEN_WIDTH = 640,
    SCREEN_HEIGHT = 480,
};

/* Start up SDL and creates window */
static bool init();
/* Loads media */
static bool load_media();
/* Frees media and shuts down SDL */
static void close();

SDL_Window *g_window = NULL;
SDL_Surface *g_screensurface = NULL;
SDL_Surface *g_xout = NULL;


static bool
init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }
    /* Create window */
    g_window = SDL_CreateWindow("SDL Tutorial",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL) {
        printf("Window could not be created! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }
    /* Get window surface */
    g_screensurface = SDL_GetWindowSurface(g_window);
    return true;
}

static bool
load_media()
{
    g_xout = SDL_LoadBMP("xout.bmp");
    if(g_xout == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n",
               "xout.bmp", SDL_GetError());
        return false;
    }
    return true;
}

static void
close()
{
    SDL_FreeSurface(g_xout);
    g_xout = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

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
            SDL_BlitSurface(g_xout, NULL, g_screensurface, NULL);
            SDL_UpdateWindowSurface(g_window);
        }
    }
    close();
    return 0;
}
