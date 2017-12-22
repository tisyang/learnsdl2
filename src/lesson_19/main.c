#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "texture.h"

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
/* Load individual image as texture */
static const char * const G_WIN_CAPTION = "Lesson 19: Gamepads and Joysticks";

SDL_Window   *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture  *g_arrow = NULL;
int g_arrow_width = 0;
int g_arrow_height = 0;

const int JOYSTICK_DEAD_ZONE = 8000;
SDL_Joystick* g_gamecontroller = NULL;

static bool
init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!\n");
    }

    if (SDL_NumJoysticks() < 1) {
        printf("Warning: No joystocks connected!\n");
    } else {
        g_gamecontroller = SDL_JoystickOpen(0);
        if (g_gamecontroller == NULL) {
            printf("Warning: Unable to open game controller! SDL Error: %s\n",
                   SDL_GetError());
        }
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
    g_arrow = Texture_Load(g_renderer, "arrow.png");
    if(g_arrow == NULL) {
        printf("Failed to load texture image!\n");
        return false;
    }
    if(SDL_QueryTexture(g_arrow, NULL, NULL, &g_arrow_width, &g_arrow_height) < 0) {
        printf("Failed to get texture size!\n");
        return false;
    }

    return true;
}

static void
close()
{
    Texture_Free(g_arrow);
    g_arrow = NULL;

    SDL_JoystickClose(g_gamecontroller);
    g_gamecontroller = NULL;

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

    int xDir = 0;
    int yDir = 0;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            } else if(e.type == SDL_JOYAXISMOTION) {
                if (e.jaxis.which == 0) {
                    if (e.jaxis.axis == 0) {
                        if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                            xDir = -1;
                        } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                            xDir = 1;
                        } else {
                            xDir = 0;
                        }
                    } else if (e.jaxis.axis == 1) {
                        if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                            yDir = -1;
                        } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                            yDir = 1;
                        } else {
                            yDir = 0;
                        }
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);

        double joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);

        if (xDir == 0 && yDir == 0) {
            joystickAngle = 0;
        }

        Texture_RenderEx(g_arrow, g_renderer,
                         (SCREEN_WIDTH - g_arrow_width) / 2,
                         (SCREEN_HEIGHT - g_arrow_height) / 2,
                         NULL, joystickAngle, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(g_renderer);
    }
    close();
    return 0;
}
