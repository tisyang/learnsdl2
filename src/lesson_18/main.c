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

#define TOTAL_BUTTONS 4


/* Start up SDL and creates window */
static bool init();
/* Loads media */
static bool load_media();
/* Frees media and shuts down SDL */
static void close();

static const char * const G_WIN_CAPTION = "Lesson 18: Key States";
static SDL_Window   *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;

static SDL_Texture *g_up_texture = NULL;
static SDL_Texture *g_down_texture = NULL;
static SDL_Texture *g_left_texture = NULL;
static SDL_Texture *g_right_texture = NULL;
static SDL_Texture *g_press_texture = NULL;


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
    g_up_texture = Texture_Load(g_renderer, "key_up.bmp");
    if (g_up_texture == NULL) {
        printf("could not load image texture 'key_up.bmp'\n");
        return false;
    }

    g_down_texture = Texture_Load(g_renderer, "key_down.bmp");
    if (g_down_texture == NULL) {
        printf("could not load image texture 'key_down.bmp'\n");
        return false;
    }

    g_left_texture = Texture_Load(g_renderer, "key_left.bmp");
    if (g_left_texture == NULL) {
        printf("could not load image texture 'key_left.bmp'\n");
        return false;
    }

    g_right_texture = Texture_Load(g_renderer, "key_right.bmp");
    if (g_right_texture == NULL) {
        printf("could not load image texture 'key_right.bmp'\n");
        return false;
    }

    g_press_texture = Texture_Load(g_renderer, "key_press.bmp");
    if (g_press_texture == NULL) {
        printf("could not load image texture 'key_press.bmp'\n");
        return false;
    }

    return true;
}

static void
close()
{
    Texture_Free(g_up_texture);
    Texture_Free(g_down_texture);
    Texture_Free(g_left_texture);
    Texture_Free(g_right_texture);
    Texture_Free(g_press_texture);

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

    SDL_Texture *currentTexture = NULL;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            currentTexture = g_up_texture;
        } else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            currentTexture = g_down_texture;
        } else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            currentTexture = g_left_texture;
        } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            currentTexture = g_right_texture;
        } else {
            currentTexture = g_press_texture;
        }

        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);

        Texture_Render(currentTexture, g_renderer, 0, 0, NULL);

        SDL_RenderPresent(g_renderer);
    }
    close();
    return 0;
}
