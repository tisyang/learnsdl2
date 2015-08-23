#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
/* Load individual image as texture */
static SDL_Texture * load_texture(const char *path);

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;

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
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
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
    g_texture = load_texture("viewport.png");
    if(g_texture == NULL) {
        printf("Failed to load texture image!\n");
        return false;
    }
    return true;
}

static void
close()
{
    SDL_DestroyTexture(g_texture);
    g_texture = NULL;

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

static SDL_Texture *
load_texture(const char *path)
{
    SDL_Texture *texture = NULL;

    SDL_Surface *surface = IMG_Load(path);
    if(surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path, IMG_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(g_renderer, surface);
        if(texture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                   path, SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }

    return texture;
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

        SDL_RenderClear(g_renderer);

        SDL_Rect topleftview;
        topleftview.x = 0;
        topleftview.y = 0;
        topleftview.w = SCREEN_WIDTH / 2;
        topleftview.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport(g_renderer, &topleftview);
        SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);

        SDL_Rect toprightview;
        toprightview.x = SCREEN_WIDTH / 2;
        toprightview.y = 0;
        toprightview.w = SCREEN_WIDTH / 2;
        toprightview.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport(g_renderer, &toprightview);
        SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);

        SDL_Rect bottomview;
        bottomview.x = 0;
        bottomview.y = SCREEN_HEIGHT / 2;
        bottomview.w = SCREEN_WIDTH;
        bottomview.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport(g_renderer, &bottomview);
        SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);

        SDL_RenderPresent(g_renderer);
    }
    close();
    return 0;
}
