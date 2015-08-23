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
SDL_Surface *g_helloworld = NULL;


static bool
init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",
               SDL_GetError());
        success = false;
    } else {
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
            success = false;
        } else {
            /* Get window surface */
            g_screensurface = SDL_GetWindowSurface(g_window);
        }
    }
    return success;
}

static bool
load_media()
{
    bool success = true;
    g_helloworld = SDL_LoadBMP("helloworld.bmp");
    if(g_helloworld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n",
               "helloworld.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

static void
close()
{
    SDL_FreeSurface(g_helloworld);
    g_helloworld = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    SDL_Quit();
}

int main(int argc, char *argv[])
{
    if(init() == false) {
        printf("Failed to initialize!\n");
    } else {
        if(load_media() == false) {
            printf("Failed to load media!\n");
        } else {
            SDL_BlitSurface(g_helloworld, NULL, g_screensurface, NULL);
            SDL_UpdateWindowSurface(g_window);
            SDL_Delay(2000);
        }
    }
    close();
    return 0;
}
