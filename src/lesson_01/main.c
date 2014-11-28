#include "SDL2/SDL.h"
#include <stdio.h>

enum {
    SCREEN_WIDTH = 640,
    SCREEN_HEIGHT = 480,
};

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;

    SDL_Surface *screensurface = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("SDL Tutorial",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            screensurface = SDL_GetWindowSurface(window);
            // Fill the surface white
            SDL_FillRect(screensurface, NULL,
                    SDL_MapRGB(screensurface->format, 0xFF, 0xFF, 0xFF));
            printf("Hello world\n");
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
