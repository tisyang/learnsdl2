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
/* Render Texture to render at specific position */
static bool render_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);

SDL_Window   *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture  *g_foo = NULL;
SDL_Texture  *g_background = NULL;

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
    g_foo = load_texture("../assets/images/foostick.png");
    if(g_foo == NULL) {
        printf("Failed to load texture image!\n");
        return false;
    }

    g_background = load_texture("../assets/images/greenland.png");
    if(g_background == NULL) {
        printf("Failed to load texture image!\n");
        return false;
    }

    return true;
}

static void
close()
{
    SDL_DestroyTexture(g_foo);
    g_foo = NULL;
    SDL_DestroyTexture(g_background);
    g_background = NULL;

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
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(g_renderer, surface);
        if(texture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                   path, SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }

    return texture;
}

static bool
render_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
    int w, h;
    /* Query width and height of texture */
    if(SDL_QueryTexture(texture, NULL, NULL, &w, &h) < 0) {
        /* on error */
        printf("Unable to query texture. SDL Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_Rect rect = { x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    return true;
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
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);

        /* render background */
        render_texture(g_renderer, g_background, 0, 0);
        /* render stick man foo */
        render_texture(g_renderer, g_foo, 240, 190);

        SDL_RenderPresent(g_renderer);
    }
    close();
    return 0;
}
