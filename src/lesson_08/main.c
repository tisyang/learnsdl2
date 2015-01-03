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

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

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

    return true;
}

static bool
load_media()
{
    return true;
}

static void
close()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

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
        }

        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);
        SDL_Rect fill_rect = {
            SCREEN_WIDTH / 4,
            SCREEN_HEIGHT / 4,
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT / 2
        };
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(g_renderer, &fill_rect);

        SDL_Rect outline_rect = {
            SCREEN_WIDTH / 6,
            SCREEN_HEIGHT / 6,
            SCREEN_WIDTH * 2 / 3,
            SCREEN_HEIGHT * 2 / 3
        };
        SDL_SetRenderDrawColor(g_renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(g_renderer, &outline_rect);

        SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(g_renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < SCREEN_HEIGHT; i+=4) {
            SDL_RenderDrawPoint(g_renderer, SCREEN_WIDTH / 2, i);
        }

        SDL_RenderPresent(g_renderer);

    }
    close();
    return 0;
}
