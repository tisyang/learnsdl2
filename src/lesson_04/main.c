#include "SDL2/SDL.h"
#include <stdbool.h>
#include <stdio.h>

enum {
    SCREEN_WIDTH = 640,
    SCREEN_HEIGHT = 480,
};

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
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
/* The image that correspond to a keypree */
SDL_Surface *g_keypresssurface[KEY_PRESS_SURFACE_TOTAL];
/* Current displayed image */
SDL_Surface *g_currentsurface = NULL;


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
    g_keypresssurface[KEY_PRESS_SURFACE_DEFAULT] = load_surface("key_press.bmp");
    if(g_keypresssurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Failed to load default image!\n");
        return false;
    }

    g_keypresssurface[KEY_PRESS_SURFACE_UP] = load_surface("key_up.bmp");
    if(g_keypresssurface[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load up image!\n");
        return false;
    }

    g_keypresssurface[KEY_PRESS_SURFACE_DOWN] = load_surface("key_down.bmp");
    if(g_keypresssurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load down image!\n");
        return false;
    }

    g_keypresssurface[KEY_PRESS_SURFACE_LEFT] = load_surface("key_left.bmp");
    if(g_keypresssurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load left image!\n");
        return false;
    }

    g_keypresssurface[KEY_PRESS_SURFACE_RIGHT] = load_surface("key_right.bmp");
    if(g_keypresssurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load right image!\n");
        return false;
    }
    return true;
}

static void
close()
{
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        SDL_FreeSurface(g_keypresssurface[i]);
        g_keypresssurface[i] = NULL;
    }
    g_currentsurface = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    SDL_Quit();
}

static SDL_Surface *
load_surface(const char *path)
{
    SDL_Surface *surface = SDL_LoadBMP(path);
    if(surface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n",
               path, SDL_GetError());
    }
    return surface;
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

    g_currentsurface = g_keypresssurface[KEY_PRESS_SURFACE_DEFAULT];

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            } else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                case SDLK_UP:
                    g_currentsurface = g_keypresssurface[KEY_PRESS_SURFACE_UP];
                    break;
                case SDLK_DOWN:
                    g_currentsurface = g_keypresssurface[KEY_PRESS_SURFACE_DOWN];
                    break;
                case SDLK_LEFT:
                    g_currentsurface = g_keypresssurface[KEY_PRESS_SURFACE_LEFT];
                    break;
                case SDLK_RIGHT:
                    g_currentsurface = g_keypresssurface[KEY_PRESS_SURFACE_RIGHT];
                    break;
                default:
                    g_currentsurface = g_keypresssurface[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }

        SDL_BlitSurface(g_currentsurface, NULL, g_screensurface, NULL);
        SDL_UpdateWindowSurface(g_window);
    }
    close();
    return 0;
}
