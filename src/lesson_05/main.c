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
/* Loads individual image */
static SDL_Surface * load_surface(const char *path);

SDL_Window *g_window = NULL;
SDL_Surface *g_screensurface = NULL;
SDL_Surface *g_stretchedsurface = NULL;

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
    g_stretchedsurface = load_surface("stretching.bmp");
    if(g_stretchedsurface == NULL) {
        printf("Failed to load image %s! SDL Error: %s\n",
               "stretching.bmp", SDL_GetError());
        return false;
    }
    return true;
}

static void
close()
{
    SDL_FreeSurface(g_stretchedsurface);
    g_stretchedsurface = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    SDL_Quit();
}

static SDL_Surface *
load_surface(const char *path)
{
    SDL_Surface *optimized_surface = NULL;

    SDL_Surface *surface = SDL_LoadBMP(path);
    if(surface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n",
               path, SDL_GetError());
    } else {
        optimized_surface = SDL_ConvertSurface(surface,
                                               g_screensurface->format,
                                               0);
        if(optimized_surface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n",
                   path, SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
    return optimized_surface;
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
        }

        SDL_Rect stretch_rect;
        stretch_rect.x = 0;
        stretch_rect.y = 0;
        stretch_rect.w = SCREEN_WIDTH;
        stretch_rect.h = SCREEN_HEIGHT;

        SDL_BlitScaled(g_stretchedsurface, NULL, g_screensurface, &stretch_rect);
        SDL_UpdateWindowSurface(g_window);
    }
    close();
    return 0;
}
